
/*
  2FP UV spectral measurment tool
  UVA (320-400nm), UVB (280-320nm), and UVC (200-280nm) 
  High Dynamic Range: Up to 3.43E+10 (resolution multiplied by gain range)
  accuracy of up to 24-bit signal resolution
  irradiance responsivity per count down to 2.38 nW/cm² at 64 ms integration time.
*/

/*
  Example-01_Hello.ino

  This demo shows the basic setup of the OLED library, generating simple graphics and displaying
  the results on the target device.

   Micro OLED             https://www.sparkfun.com/products/14532
   Transparent OLED       https://www.sparkfun.com/products/15173
   "Narrow" OLED          https://www.sparkfun.com/products/24606
   Qwiic OLED 1.3in       https://www.sparkfun.com/products/23453

  Written by Kirk Benell @ SparkFun Electronics, March 2022

  Repository:
     https://github.com/sparkfun/SparkFun_Qwiic_OLED_Arduino_Library

  Documentation:
     https://sparkfun.github.io/SparkFun_Qwiic_OLED_Arduino_Library/

  SparkFun code, firmware, and software is released under the MIT License(http://opensource.org/licenses/MIT).
*/

/*
  Using the AMS AS7331 Spectral UV Sensor in Command/One Shot (CMD) Mode.

  This example shows how operate the AS7331 in the default CMD mode. The start
  command is sent, then delays until the conversion time has passed before
  reading out the UV values.

  By: Alex Brudner
  SparkFun Electronics
  Date: 2023/11/17
  SparkFun code, firmware, and software is released under the MIT License.
    Please see LICENSE.md for further details.

  Hardware Connections:
  IoT RedBoard --> AS7331
  QWIIC --> QWIIC

  Serial.print it out at 115200 baud to serial monitor.

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/23517 - Qwiic 1x1
  https://www.sparkfun.com/products/23518 - Qwiic Mini
*/

#include <Arduino.h>
#include <Wire.h>

#include <SparkFun_Qwiic_OLED.h> //http://librarymanager/All#SparkFun_Qwiic_OLED
// The Library supports four different types of SparkFun boards. The demo uses the following
// defines to determine which device is being used. Uncomment the device being used for this demo.

//QwiicMicroOLED myOLED;
//QwiicTransparentOLED myOLED;
//QwiicNarrowOLED myOLED;
Qwiic1in3OLED myOLED;

#include <SparkFun_AS7331.h>
SfeAS7331ArdI2C myUVSensor;

void setup()
{
    Serial.begin(115200);
    Serial.println("Running OLED startup");

    Wire.begin();

    // Initalize the OLED device and related graphics system
    if (myOLED.begin() == false)
    {
        Serial.println("Device begin failed. Freezing...");
        while (true)
            ;
    }
    Serial.println("Begin success");

    String hello = "2FP UV v1"; // our message
    // Center our message on the screen. Get the screen size of the "hello" string,
    // calling the getStringWidth() and getStringHeight() methods on the oled
    // starting x position - screen width minus string width  / 2
    int x0 = (myOLED.getWidth() - myOLED.getStringWidth(hello)) / 2;
    // starting y position - screen height minus string height / 2 
    int y0 = (myOLED.getHeight() - myOLED.getStringHeight(hello)) / 2;
    // Draw the text - color of white
    myOLED.text(x0, y0, hello, 1);
    // There's nothing on the screen yet - Now send the graphics to the device
    myOLED.display();

    // Initialize sensor and run default setup.
    if (myUVSensor.begin() == false)
    {
        Serial.println("Sensor failed to begin. Please check your wiring!");
        Serial.println("Halting...");
        while (1)
            ;
    }

    Serial.println("Sensor began.");

    // Set measurement mode and change device operating mode to measure.
    if (myUVSensor.prepareMeasurement(MEAS_MODE_CMD) == false)
    {
        Serial.println("Sensor did not get set properly.");
        Serial.println("Halting...");
        while (1)
            ;
    }

    Serial.println("Set mode to command.");

}

void loop()
{
  //for boot screen
  delay(1000);
  myOLED.erase();
  myOLED.display();

  //set up once
  int x0 = 0; 
  int y0 = 0; 
  String measurementstr = "A";
  int lineH = myOLED.getStringHeight(measurementstr );
  String spacerstr = "";
  int lineW = 0;

  String UVA = "";
  String UVB = "";
  String UVC = "";

  //first 0 reading to be discarded
  // Send a start measurement command.
  if (ksfTkErrOk != myUVSensor.setStartState(true))
      Serial.println("Error starting reading!");
  // Wait for a bit longer than the conversion time.
  delay(2 + myUVSensor.getConversionTimeMillis());
  // Read UV values.
  if (ksfTkErrOk != myUVSensor.readAllUV())
      Serial.println("Error reading UV.");
  UVA = String(myUVSensor.getUVA());
  UVB = String(myUVSensor.getUVB());
  UVC = String(myUVSensor.getUVC());

  //set costant part of display
  measurementstr = "UVA (320-400nm): ";
  myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
  y0 += lineH*2;
  measurementstr = "UVB (280-320nm): ";
  myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
  y0 += lineH*2;
  measurementstr = "UVC (200-280nm): ";
  myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
  // There's nothing on the screen yet - Now send the graphics to the device
  myOLED.display();

  while( true ) {
    
    // Send a start measurement command.
    if (ksfTkErrOk != myUVSensor.setStartState(true))
        Serial.println("Error starting reading!");
    // Wait for a bit longer than the conversion time.
    delay(2 + myUVSensor.getConversionTimeMillis());
    // Read UV values.
    if (ksfTkErrOk != myUVSensor.readAllUV())
        Serial.println("Error reading UV.");

    UVA = String(myUVSensor.getUVA());
    UVB = String(myUVSensor.getUVB());
    UVC = String(myUVSensor.getUVC());

    Serial.print("UVA:");
    Serial.print(UVA);
    Serial.print(" UVB:");
    Serial.print(UVB);
    Serial.print(" UVC:");
    Serial.println(UVC);    
    Serial.print(" TMP:");
    Serial.println(myUVSensor.getTemp());    



    //indicate a reading is taking place
    myOLED.erase();
    spacerstr = "     -.-- uW/cm^2";
    lineW = myOLED.getStringHeight(spacerstr);
    x0 = 0; 
    y0 = 0; 
    //myOLED.rectangleFill(x0, y0+lineH*1, lineW, lineH, 1);
    //myOLED.rectangleFill(x0, y0+lineH*2, lineW, lineH, 1);
    //myOLED.rectangleFill(x0, y0+lineH*3, lineW, lineH, 1);
    
    measurementstr = "UVA (320-400nm): ";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
    y0 += lineH;
    //measurementstr = "     " + UVA + " uW/cm^2";
    myOLED.text(x0, y0, spacerstr, 1); // Draw the text - color of white
    y0 += lineH;

    measurementstr = "UVB (280-320nm): ";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
    y0 += lineH;
    //measurementstr = "     " + UVB + " uW/cm^2";
    myOLED.text(x0, y0, spacerstr, 1); // Draw the text - color of white
    y0 += lineH;
    
    measurementstr = "UVC (200-280nm): ";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
    y0 += lineH;
    measurementstr = "     " + UVC + " uW/cm^2";
    myOLED.text(x0, y0, spacerstr, 1); // Draw the text - color of white

    // There's nothing on the screen yet - Now send the graphics to the device
    myOLED.display();
    //delay(1000);//testing only



    //now the actual measurments
    myOLED.erase();
    x0 = 0; 
    y0 = 0; 

    measurementstr = "UVA (320-400nm): ";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
    y0 += lineH;
    measurementstr = "     " + UVA + " uW/cm^2";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
    y0 += lineH;

    measurementstr = "UVB (280-320nm): ";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
    y0 += lineH;
    measurementstr = "     " + UVB + " uW/cm^2";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
    y0 += lineH;
    
    measurementstr = "UVC (200-280nm): ";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white
    y0 += lineH;
    measurementstr = "     " + UVC + " uW/cm^2";
    myOLED.text(x0, y0, measurementstr, 1); // Draw the text - color of white

    // There's nothing on the screen yet - Now send the graphics to the device
    myOLED.display();

    delay(5000); //measure every X seconds

  }  
}
