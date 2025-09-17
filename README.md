
# Triaxial clock driver

This is a ESP32 driver for the triaxial Numechron clock found at <https://www.instructables.com/Triaxial-Numechron-Clock/>

## Features

- Uses a ESP32. I'm running mine in an old DOIT Devkit-v1. Adjust platformio.ini for your model
- Connects to a WiFi hostspot and update time from NTP
- Uses accelstepper for smooth step motor drive
- OTA firmware update at ip/update using ElegantOTA

## TODO

- Save the last minute so in case of a power failure, the clock can fast forwared to the current time by itself

## Authors

- [Luiz Cressoni](luiz@cressoni.com.br)

## Code documentation

Install Doxygen with:

    sudo apt-get install doxygen

Then, on the project main folder, run it:

    doxygen

Doxygen will run and generate the full code documentation on the docs/html folder.
The start file is index.html.
Note: This folder is ignored by git.

## Deployment

Clone the repository to your local machine and open the project using VSCode with PlatformIO
Edit platformio.ini file to set your WiFi credentials and the number of pulses to spin one minute
Note: An easy way to fine tune is to set the value for a full spin (10 minutes), adjust the value, then divide it by 10
