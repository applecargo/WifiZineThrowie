---
layout: default
---

# H&D Walking signal / WIFI hotspot zine workshop.

## Technical guides.

### What is a hot-spot zine?

- A standalone WIFI signal broadcaster
- A standalone captive portal webserver which serves a webpage instead of regular login page
- This webpage plus this electronic device itself is a zine platform
- A standalone networking device which can be used to communicate with others
- A network that ‘you’ have the complete (relatively) control over it (than.. For example, the Internet)
- A ‘walking’ network or a signal that you can carry/accompany with your physical presence
- [more info](http://pilote.byus.net/wpdiana/?page_id=1064)
- Consist of… : ESP32 module + powering device + your content + your ‘context’

### How to make one?

#### What is needed.

- A computer
- A ESP32 breakout board
- microUSB cable (so called, android data cable)
- A battery or powerbank
- A webpage (html/css/js + media files)
- (optional) Magnets : you attach or install the module at some specific place / location, to give more context/happening
- (optional) A case / a hull : you shape/materialize it to give it more context/happening.
- (optional) Sensory peripherals or actuators (incl. speakers etc) : to give it more context/happening.
- (optional) A concept / a idea

#### Limitations

- Storage 2MB (or less)
- A bit slower than normal web servers
- Maybe a bit unstable from time to time : you can re-start the module whenever needed.

#### How to upload your code to the device

- Installing USB driver which enables us to communicate to the chip (i.e. the module: ESP32)
  - For Windows users
    - Windows 7
    - Windows 8
    - Windows 10
  - For Mac OSX users
    - Yosemite (10.10)
    - El capitan (10.11)
    - Sierra (10.12)
    - High Sierra (10.13)
    - Mojave (10.14)
  - For Linux
    - Debian derived
    - Archlinux derived

  - Testing USB communication
    - Enabling verbose/detailed output of the procedure that arduino takes for compilation and uploading steps
    - Try compile & upload and see if it works with the simplest example: Blink example
    - How to listen to the device with Serial comm. Example

  - Preparing hotspot-zine code and installing additional components that is needed by the code (libraries)
    - How to use arduino’s Library Manager to install a new library
    - What we need to install
      - ESP32AsyncWebServer
      - AsyncTCP
      - …
    - Where is the code?
      - USB drive
      - Or github, using git.
  - Choose your SSID and modify the default one
  - Try compile & upload and see what happens.

#### Uploading the zine content

- Installing additional tools for extending arduino functionality to support ESP data uploading (for the website data)
- Let’s try again the most simplest one: ‘Hello, world!’ example page

#### Working with your zine contents

- Template #1 : Text-oriented single page: ‘Hello, world!’
- Template #2 : Image-oriented single page: ‘Imaginary, world.’
- Template #3 : Sound-oriented single page: ‘Sound world!’
- Template #4 : Multiple-pages: ‘Looooong story!’
- Template #5 : Paper.js
- Template #6 : P5.js
- Template #7 : http://molleindustria.github.io/p5.play/
- Template #8 : Tone.js
- Template #9 (advanced) : WebSocket - socket.io + server-side programming @ arduino

#### Working with the shape and materialization

- Adding sensors : example (buttons)
- Adding actuators : example (motor)

#### Working with the location

- Magnets and installing at public space

### Contribution to the project

- Sharing your zine content & construction + your concept/context
- Approvements on the wifi-zine code: send PR @ github
  - And plz be patient, i have never used PR system.. Need to learn :)
- Or simply e-mail your idea and stuff : <mailto:pilotedeguerre@gmail.com>

### Thank you!
