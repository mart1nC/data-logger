#include <SPI.h>
#include <mySD.h>
//#include "mySD.h"
File myFile;

const int chipSelect = 4;

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card..."); 
  pinMode(SS, OUTPUT);
  pinMode(chipSelect, OUTPUT); 
  if (!SD.begin(chipSelect, 23, 19, 18)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("logger.csv", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to logger.csv ...");
    myFile.println("Parametros ,");
    myFile.print("Parametros");myFile.print("hora");myFile.print("fecha");
    myFile.println("fecha; hora; dato1;dato2;dato3;dato4;");
  // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening logger.csv");
  }
  
  // re-open the file for reading:
  myFile = SD.open("logger.csv",FILE_READ);
  if (myFile) {
    Serial.println("logger.csv read");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening logger.csv");
  }
}

void loop(){  // nothing happens after setup
}
