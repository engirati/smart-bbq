#include "SmartProbe.h"
#include "SmartBbq.h"
#include "Adafruit_LEDBackpack.h"
#include "SimpleButton.h"
#include "ThermistorProbe.h"
#include "SimpleLed.h"

#define PROBE1 A7
#define PROBE2 A6
#define PROBE3 A5
#define PROBE4 A4

#define PROBEINDICATOR1 D4
#define PROBEINDICATOR2 D5
#define PROBEINDICATOR3 D6
#define PROBEINDICATOR4 D7

#define BUTTON_LEFT D3
#define BUTTON_CENTER A2
#define BUTTON_RIGHT D2

// Define display
Adafruit_7segment display = Adafruit_7segment();

// Define buttons
SimpleButton buttonLeft(BUTTON_LEFT);
SimpleButton buttonCenter(BUTTON_CENTER);
SimpleButton buttonRight(BUTTON_RIGHT);

// Define SmartBbq
SmartBbq bbq(PROBE1,PROBE2,PROBE3,PROBE4,PROBEINDICATOR1,PROBEINDICATOR2,PROBEINDICATOR3,PROBEINDICATOR4);

void setup() {
    Serial.begin(9600);
    
    display.begin(0x70);
}

void loop() {
    // check if a button was pressed
    checkButtons();
    
    // update display
    printDisplay(bbq.getActiveTemp());
    
    // delay for short period just makes things work nicely
    delay(5);
}

void checkButtons() {
    if(buttonLeft.isPressed()) {
        bbq.down();
    } else if(buttonCenter.isPressed()) {
        bbq.select();
    } else if(buttonRight.isPressed()) {
        bbq.up();
    }
}

void printDisplay(float mydub) {
    display.printFloat(mydub);
    display.writeDisplay();
}
