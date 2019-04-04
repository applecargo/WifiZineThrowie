//make the noise and connect it to the output
var noise = new Tone.Noise({
  "volume": -20,
  "type": "brown"
}).toMaster();

noise.start();

function Btn(elem, coloron, coloroff, blinktime, callback) {
  this.elem = elem;
  this.coloron = coloron;
  this.coloroff = coloroff;
  this.blinktime = blinktime;
  this.callback = callback;
  $(this.elem).addClass(coloroff);

  $(elem).click(function() {
    $(this).removeClass(coloroff).addClass(coloron);
    if (callback !== null) callback();
    setTimeout(function() {
      $(this).removeClass(coloron).addClass(coloroff);
    }.bind(this), blinktime);
  });

  this.click = function() {
    $(this.elem).click();
  }
}

function Flasher(elem, flashtime) {
  this.elem = elem;
  this.flashtime = flashtime;
  this.color = 'bg-white';
  $(this.elem).addClass(this.color);
  this.colors = ['bg-white', 'bg-red', 'bg-yellow', 'bg-green', 'bg-blue', 'bg-hot-pink', 'bg-light-purple', 'bg-lime'];

  this.flash = function() {
    $(this.elem).stop(true, true);
    $(this.elem).hide();
    $(this.elem).removeClass(this.color);
    this.color = this.colors[Math.floor(Math.random() * this.colors.length)];
    $(this.elem).addClass(this.color);
    $(this.elem).show();
    $(this.elem).fadeOut(this.flashtime);
  };
}

$(document).ready(function() {

  //overlay-ed flasher
  var flasher = new Flasher($('.flasher')[0], 2000);

  //cricket
  var cricket = new Tone.Player("audio/cricket.mp3").toMaster();

  //sound enabler (especially for iOS users/devices)
  var touch = new Btn($(".touch")[0], 'bg-white', 'bg-near-black', 300, function() {
    noise.stop();
    cricket.start();
    flasher.flash();
  });
});
