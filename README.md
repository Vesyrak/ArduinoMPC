# ArduinoMPC

Simple Arduino sketch & Python script for controlling your MPD server over Bluetooth.

## HW Requirements
* Arduino
* LCD shield with buttons (or seperate ones if you wire it yourself)
* Arduino Compatible bluetooth module

## Installation
* Upload your arduino sketch (make sure you connect the bluetooth tx/rx after uploading)
* Pair and trust the arduino bluetooth module on the computer (bluetoothctl works fine for this)
* Start the script

## TODO
* Cron job for auto starting the script
* Safety measure for reconnecting if disconnected
