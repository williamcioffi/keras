/* 
 * SPI bus as follows:
 * MOSI - pin 11
 * MISO - pin 12
 * CLK - pin 13
 * CS - pin 10
 */

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"

const int gCHIPSELECT = 10;
const long gMAXWRITESPERFILE = 1000000;
const int gLIGHTPIN = 0;

const String gFILEPREFIX = "d";
const String gFILESUFFIX = ".csv";

//86400

int gFILENUM = 0;
int gNUMWRITES = 0;

long gPREVTIME = 0;
long gINTERVAL = 1000;

Adafruit_MCP9808 gTEMPSENSOR = Adafruit_MCP9808();


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(gCHIPSELECT)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }

  if (!gTEMPSENSOR.begin()) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  
  Serial.println("card initialized.");


  String fname = String(gFILEPREFIX);
  fname += gFILENUM;
  fname += gFILESUFFIX;
      
  File datafile = SD.open(fname, FILE_WRITE);
  datafile.println("light,temp");
  datafile.close();
}

void loop() {

  unsigned long curtime = millis();

  if(curtime - gPREVTIME > gINTERVAL) { 
    gPREVTIME = curtime;
    String datastring = "";
    
    int light = analogRead(gLIGHTPIN);
    float tempc = gTEMPSENSOR.readTempC();
    datastring += String(light);
    datastring += ",";
    datastring += tempc;
    
    if(gNUMWRITES == gMAXWRITESPERFILE) {
Serial.println(gFILENUM);
      gNUMWRITES = 0;
      gFILENUM++;

      String fname = String(gFILEPREFIX);
      fname += gFILENUM;
      fname += gFILESUFFIX;

      File datafile = SD.open(fname, FILE_WRITE);
      datafile.println("light,temp");
      datafile.close();
    }
    
    String fname = String(gFILEPREFIX);
    fname += gFILENUM;
    fname += gFILESUFFIX;
    
    File datafile = SD.open(fname, FILE_WRITE);

    if (datafile) {
Serial.println(datastring);
      datafile.println(datastring);
      datafile.close();
      gNUMWRITES++;
    } 
    else {
      Serial.println("error opening datalog");
    }
  }
}









