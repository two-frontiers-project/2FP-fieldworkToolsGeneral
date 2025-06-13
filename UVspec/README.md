# 2FP UV measurment

Simple data display measuing 3 spectral UV channels

UVA (320-400nm), UVB (280-320nm), and UVC (200-280nm) 

High Dynamic Range: Up to 3.43E+10 (resolution multiplied by gain range)

accuracy of up to 24-bit signal resolution

irradiance responsivity per count down to 2.38 nW/cm² at 64 ms integration time.

displayed in μW/cm²

## HARDWARE

Sparkfun parts:

DEV-16885 
https://www.sparkfun.com/sparkfun-micromod-atp-carrier-board.html

WRL-16781
https://www.sparkfun.com/sparkfun-micromod-esp32-processor.html

SEN-23517
https://www.sparkfun.com/sparkfun-spectral-uv-sensor-as7331-qwiic.html
https://github.com/sparkfun/SparkFun_AS7331_Arduino_Library

LCD-22495
https://www.sparkfun.com/sparkfun-micro-oled-breakout-qwiic-lcd-22495.html
https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library

plus 2 QWIIC cables

## INSTALL

install arduino

Install the board with board manager "ESP32", select "Sparkfun ESP32 micrimod"

Install the library through the Arduino Library Manager tool by searching for "SparkFun AS7331" and "Qwiic OLED" 


## NOTES on values

Function in library: https://github.com/sparkfun/SparkFun_AS7331_Arduino_Library/blob/main/src/sfTk/sfDevAS7331.cpp

References datasheet section 7.4 Equation 4 https://cdn.sparkfun.com/assets/b/8/6/d/2/AS7331_DS001047_4-00.pdf

Which converts to FSR in μW/cm² 


