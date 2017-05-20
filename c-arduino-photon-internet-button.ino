// Importing libraries
#include "HttpClient/HttpClient.h"
#include "InternetButton/InternetButton.h"
#include "math.h"

// Preparing HttpClient
HttpClient http;
http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

// Declaring variables
http_request_t request;
http_response_t response;
InternetButton b = InternetButton();
int i;
int prevxValue;
String ledState;
const long timeoutAmount = 10000;
unsigned long nextUpdate;      // Next led light timeout

void setup() {
    Serial.begin(9600);
    b.begin();
    b.allLedsOff();
    RGB.control(true);
    RGB.color(0, 0, 0);
    nextUpdate = millis() + timeoutAmount; 
}

void loop() {

  int xValue = b.readX();

    if (ledState == "off") {
        if (abs(prevxValue) > abs(xValue) + 5 ) {
        b.ledOn(1, 15, 15, 15);
        b.ledOn(11, 15, 15, 15);
        b.ledOn(3, 15, 15, 15);
        b.ledOn(6, 15, 15, 15);
        b.ledOn(9, 15, 15, 15);
        ledState = "on";
        nextUpdate = millis() + timeoutAmount; // set up the next timeout period
        };
    };

    if (millis() >= nextUpdate){
        b.allLedsOff();
        ledState = "off";
    };

    if(b.buttonOn(1)){
        b.allLedsOff();
        b.ledOn(1, 15, 0, 0);
        b.ledOn(11, 15, 0, 0);
        restCall(1);
    };

    if(b.buttonOn(2)){
        b.allLedsOff();
        b.ledOn(3, 15, 0, 0);
        restCall(2);
    };

    if(b.buttonOn(3)){
        b.allLedsOff();
        b.ledOn(6, 15, 0, 0);
        restCall(3);
    };

    if(b.buttonOn(4)){
        b.allLedsOff();
        b.ledOn(9, 15, 0, 0);
        restCall(4);
    };

    prevxValue = xValue;

};

void okLed(int led){

    if (led == 1) {
            b.ledOn(1, 0, 15, 0);
            b.ledOn(11, 0, 15, 0);
            delay(1000);
            b.ledOff(1);
            b.ledOff(11);
    }
    else {
        b.ledOn(led, 0, 15, 0);
        delay(1000);
        b.ledOff(led);
    }
    //b.playSong("C4,4,E4,4,G4,4,C5,2");
}

void koLed(){
    for (i = 0; i < 3; i++) {
        b.allLedsOn(15, 0, 0);
        delay(500);
        b.allLedsOff();
        delay(500);
    }
    b.playSong("C2,4,C2,4,C2,4");
}

void restCall(int button) {

    request.hostname = "INSERT_YOUR_IP";
    request.port = INSERT_YOUR_PORT;

    if (button == 1){
        request.path = "/internet_button_1/1";
    }
    if (button == 2){
        request.path = "/internet_button_1/2";
    }
    if (button == 3){
        request.path = "/internet_button_1/3";
    }
    if (button == 4){
        request.path = "/internet_button_1/4";
    }

    // Get request
    http.get(request, response, headers);

    // If request went well blink led to inform user
    if (response.status==200 and response.body=="done") {

        if (button==1){
            okLed(1);
        }

        if (button==2){
            okLed(3);
        }


        if (button==3){
            okLed(6);
        }

        if (button==4){
            okLed(9);
        }

    } else {
        
        if (response.status=-1 and button==1){
    
            okLed(1);
    
        }
    
        if (response.status=-1 and button==2){
    
            okLed(3);
    
        }
    
        if (response.status=-1 and button==4){
    
            okLed(9);
    
        }
        
    }

}
