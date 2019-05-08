//
// a modified version of "ESP_AsyncFSBrowser.ino" example
//     in "ESPAsyncWebServer" library of Hristo Gochkov (me-no-dev @ github)
//
// licensed under "LPGL-3.0"
//

//
// at first, set of modifications suggested by the gist, https://gist.github.com/dsteinman/f792f0af25ce6d7d1db4b62d29dd4d9e, applied.
//
// --> Hristo Gochkov's original code only supports "esp8266" at the time of this writing.
//     Suggested patched version makes the same ex. code runnable on "esp32"
//
// --> refer to the issue @ https://github.com/me-no-dev/ESPAsyncWebServer/issues/327#issuecomment-382811459
//

//
// afterwards, more changes applied for
//    (1) re-activate SPIFFSEditor
//    (2) use a captive portal
//

/***************************************/
/*  CONFIGURATIONS                     */
/***************************************/

// identifications & credentials
String hostName = "WIFI-ZINE";
const char* http_username = "admin";
const char* http_password = "admin";

/***************************************/
/*  ALL HEADERS and GLOBAL VARIABLES   */
/***************************************/

//over-the-air firmware updater
#include <ArduinoOTA.h>

//file system
#include <FS.h>
#include <SPIFFS.h>

//wifi / tcp
#include <WiFi.h>
#include <AsyncTCP.h>

//dns server
#include <DNSServer.h>
DNSServer dnsServer;

// captive portal -> a self-assigned ip
IPAddress apIP(192, 168, 4, 1);

//web server
#include <ESPAsyncWebServer.h> // <-- this includes, also, "AsyncWebSocket.h" and "AsyncEventSource.h"
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

//a web-based file-editor (upload/create/modify/delete files)
#include <SPIFFSEditor.h>

//a generic(monitoring) websocket events' handler (==template)
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT) {
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->printf("Hello Client %u :)", client->id());
    client->ping();
  } else if(type == WS_EVT_DISCONNECT) {
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } else if(type == WS_EVT_ERROR) {
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if(type == WS_EVT_PONG) {
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char*)data : "");
  } else if(type == WS_EVT_DATA) {
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    String msg = "";
    if(info->final && info->index == 0 && info->len == len) {
      //the whole message is in a single frame and we got all of it's data
      Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);

      if(info->opcode == WS_TEXT) {
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff;
        }
      }
      Serial.printf("%s\n",msg.c_str());

      if(info->opcode == WS_TEXT)
        client->text("I got your text message");
      else
        client->binary("I got your binary message");
    } else {
      //message is comprised of multiple frames or the frame is split into multiple packets
      if(info->index == 0) {
        if(info->num == 0)
          Serial.printf("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
        Serial.printf("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
      }

      Serial.printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT) ? "text" : "binary", info->index, info->index + len);

      if(info->opcode == WS_TEXT) {
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff;
        }
      }
      Serial.printf("%s\n",msg.c_str());

      if((info->index + len) == info->len) {
        Serial.printf("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
        if(info->final) {
          Serial.printf("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
          if(info->message_opcode == WS_TEXT)
            client->text("I got your text message");
          else
            client->binary("I got your binary message");
        }
      }
    }
  }
}

void setup(){
  //serial monitoring
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(10);
  Serial.printf("START\n");

  //file system
  SPIFFS.begin();

  //update SSID from file-system
  File root = SPIFFS.open( "/" );
  File file = root.openNextFile();
  while (file) {
    String n = file.name();
    Serial.println(n);
    int dot = n.lastIndexOf(".");
    String ext = n.substring( dot );
    if ( ext == ".ssid" ) {
      hostName = n.substring( 1, dot ); // first index is 1 to skip the "/"
    }
    file = root.openNextFile();
  }

  //wifi
  WiFi.mode(WIFI_AP);
  WiFi.setHostname(hostName.c_str());

  //start ap
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(hostName.c_str(), NULL, 6); //channel selection : 6 (choose one among 6-13 for world-wide accessibility)

  //my ip
  delay(500);
  Serial.print("IP address:"); Serial.println(WiFi.softAPIP());

  //arduino-ota <-> browser
  ArduinoOTA.onStart([]() {
    events.send("Update Start", "ota");
  });
  ArduinoOTA.onEnd([]() {
    events.send("Update End", "ota");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    char p[32];
    sprintf(p, "Progress: %u%%\n", (progress/(total/100)));
    events.send(p, "ota");
  });
  ArduinoOTA.onError([](ota_error_t error) {
    if(error == OTA_AUTH_ERROR) events.send("Auth Failed", "ota");
    else if(error == OTA_BEGIN_ERROR) events.send("Begin Failed", "ota");
    else if(error == OTA_CONNECT_ERROR) events.send("Connect Failed", "ota");
    else if(error == OTA_RECEIVE_ERROR) events.send("Recieve Failed", "ota");
    else if(error == OTA_END_ERROR) events.send("End Failed", "ota");
  });
  ArduinoOTA.setHostname(hostName.c_str());
  ArduinoOTA.begin();

  //dns service (captive portal)
  dnsServer.start(53, "*", apIP); // reply with provided IP(apIP) to all("*") DNS request

  //websocket (a generic websocket events handler)
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  //event source (an example 'hello')
  events.onConnect([](AsyncEventSourceClient *client){
    client->send("hello!",NULL,millis(),1000);
  });
  server.addHandler(&events);

  //web-based file-editor handler
  server.addHandler(new SPIFFSEditor(SPIFFS, http_username, http_password));

  //route "/heap" -> reports amount of free heap.
  server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(ESP.getFreeHeap()));
  });

  //serve-root
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  //404 handler
  server.onNotFound([](AsyncWebServerRequest *request){
    Serial.printf("NOT_FOUND: ");
    if(request->method() == HTTP_GET)
      Serial.printf("GET");
    else if(request->method() == HTTP_POST)
      Serial.printf("POST");
    else if(request->method() == HTTP_DELETE)
      Serial.printf("DELETE");
    else if(request->method() == HTTP_PUT)
      Serial.printf("PUT");
    else if(request->method() == HTTP_PATCH)
      Serial.printf("PATCH");
    else if(request->method() == HTTP_HEAD)
      Serial.printf("HEAD");
    else if(request->method() == HTTP_OPTIONS)
      Serial.printf("OPTIONS");
    else
      Serial.printf("UNKNOWN");
    Serial.printf(" http://%s%s\n", request->host().c_str(), request->url().c_str());

    if(request->contentLength()) {
      Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
      Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
    }

    int headers = request->headers();
    int i;
    for(i=0; i<headers; i++) {
      AsyncWebHeader* h = request->getHeader(i);
      Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
    }

    int params = request->params();
    for(i=0; i<params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      if(p->isFile()) {
        Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
      } else if(p->isPost()) {
        Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      } else {
        Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }

    // if(request->method() == HTTP_GET)
    // {
    request->redirect(String("http://") + apIP.toString() + "/");
    // instead of giving 404 to clients, redirect them to 'apIP'.
    //     --> https://pastebin.com/gBHU34Z9 (communication log..)

    // AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
    // response->addHeader("Location", String("http://") + apIP.toString() + "/");
    // request->send(response);
    // }
    // else
    // {
    //   request->send(404);
    // }
  });

  //file upload monitoring
  server.onFileUpload([](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final){
    if(!index)
      Serial.printf("UploadStart: %s\n", filename.c_str());
    Serial.printf("%s", (const char*)data);
    if(final)
      Serial.printf("UploadEnd: %s (%u)\n", filename.c_str(), index+len);
  });

  //request body monitoring
  server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
    if(!index)
      Serial.printf("BodyStart: %u\n", total);
    Serial.printf("%s", (const char*)data);
    if(index + len == total)
      Serial.printf("BodyEnd: %u\n", total);
  });

  //start the web service
  server.begin();
}

// handle OTA && DNS
void loop(){
  ArduinoOTA.handle();
  dnsServer.processNextRequest();
}
