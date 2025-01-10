#include <IRremote.hpp>

#include <SR04.h>
#include <Servo.h>
#define TRIG_PIN 4
#define ECHO_PIN 3
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
Servo myservo;  // create servo object to control a servo

int receiver = 11;

IRrecv irrecv(receiver);    // create instance of 'irrecv'
uint32_t last_decodedRawData = 0;//vairable uses to store the last decodedRawData

long a;
int pos = 0;    // variable to store the servo position

bool automatic_mode = true;

void setup()
{
  myservo.attach(9);
  automatic_mode = true;
  irrecv.enableIRIn();
  Serial.begin(9600);

  // myservo.writeMicroseconds(1500);
  delay(1000);
}

void loop() {
  // perform rotation based on remote buttons
  if (irrecv.decode()) // have we received an IR signal?
  { 
    // Check if it is a repeat IR code
    if (irrecv.decodedIRData.flags)
    {
      //set the current decodedRawData to the last decodedRawData
      irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    }

    
      switch (irrecv.decodedIRData.decodedRawData)
      {
        
        case 0xE916FF00: // "0" button is pressed -> Turn off the automatic mode
          // Serial.println("I run");
          pos = 0;
          myservo.write(pos);
          automatic_mode = false;
          break;
        
        case 0xF30CFF00: // "1" button is pressed -> Turn on the automatic mode
          automatic_mode = true;
          break;
          
        case 0xB946FF00: // VOL+ button pressed -> Rotate the servo by 5 clockwise
          pos += 5;
          if(pos >= 180) pos = 180;
          myservo.write(pos);
          delay(15);
          break;
        case 0xEA15FF00: // VOL- button pressed -> -> Rotate the servo by 5 counterclockwise
          pos -= 5;
          if(pos <= 0) pos = 0;
          myservo.write(pos);
          delay(15);
          break;

        case 0xE718FF00: // "2" button is pressed -> Rotate the servo to 0 degree position
          pos = 0;

          myservo.write(pos);
          delay(15);
          break;
        case 0xA55AFF00: // "6" button is pressed -> Rotate the servo to 45 degree position
          pos = 45;
          myservo.write(pos);
          delay(15);
          break;

        case 0xAD52FF00: // "68 button is pressed -> Rotate the servo to 90 degree position
          pos = 90;
          myservo.write(pos);
          delay(15);
          break;
        case 0xF708FF00: // "4" button is pressed -> Rotate the servo to 135 degree position
          pos = 135;
          myservo.write(pos);
          delay(15);
          break;
        
        case 0xE31CFF00:
          pos = 180;
          myservo.write(pos);
          delay(15);
          break;
      
      

        default: break;
        
        

      }
    
    
    //store the last decodedRawData
    last_decodedRawData = irrecv.decodedIRData.decodedRawData;
    irrecv.resume(); // receive the next value
  }


  // perform automatic rotation
  if (automatic_mode == true) {
    // myservo.write(0);
    // delay(1000);
    // myservo.write(90);
    // delay(1000);
    // myservo.write(180);
    // delay(1000);
    pos = 0;
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

    
  }

  // Serial.println(" cm");
  
  // a = sr04.Distance();
  // Serial.print(a);
  // delay(1000);
  
}