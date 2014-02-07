MinimOSD firmware using FrSky SPort telemetry as source
=======================================================

This code allows you to use a MinimOSD to overlay FrSky SPort telemetry data on your FPV video feed.

It uses the following libraries:
* my FrSky SPort library for Arduino at https://github.com/zendes/SPort
* a max7456 library from theboredengineers.com/2012/12/a-max7456-library-for-arduino/

To connect this to your Arduino, you'll need an inverter cable such as http://www.hobbyking.com/hobbyking/store/__24523__ZYX_S_S_BUS_Connection_Cable.html, or you can build your own using a TTL inverter or the schematic in the included SBUS_inverter.png file.

Basic Installation
------------------
```
$ cd <arduino-sketchbook>
$ git clone https://github.com/zendes/SPort_OSD.git
$ cd libraries
$ git clone https://github.com/zendes/SPort.git
```

Then restart your Arduino IDE and open SPort_OSD.ino