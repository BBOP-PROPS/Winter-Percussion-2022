    

//#define __DEBUG__
#ifdef __DEBUG__
   #define print(...)   Serial.print(__VA_ARGS__)
   #define println(...) Serial.println(__VA_ARGS__)
#else
   #define print(...)
   #define println(...)
#endif


#include <AccelStepper.h>


/* 
 *  
 * Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when 
 * using a driver:
 * DIR- && PUL- to GND
 * 
*/

#define dirPin 5        // DIR+
#define stepPin 7       // PUL+
#define downOverride 6
#define upOverride 8
#define motorInterfaceType 1



// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed and acceleration:
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(downOverride, INPUT_PULLUP); 
  pinMode(upOverride, INPUT_PULLUP);
  #ifdef __DEBUG__
     Serial.begin(115200);
  #endif
  println("Setting Max Speed to 7500");
  stepper.setMaxSpeed(7500);
  stepper.setSpeed(1000);

}

void loop() {
    if (digitalRead(downOverride) == 0 ) 
      { 
        println("Rolldown pressed");
        digitalWrite(LED_BUILTIN, HIGH);
        println("Waiting 3 seconds to enter manual mode...");
        delay(3000);
              if (digitalRead(downOverride) == 0 )     
              {      
                   while (digitalRead(downOverride) == 0) 
                   {
                      println(" Entering Manual Rolldown Mode");
                      digitalWrite(LED_BUILTIN, LOW);     
                     stepper.setSpeed(-1000);
                     stepper.runSpeed();  
                   }
              } 
              else 
              { 
                    println("Bypassed manual mode...");
                    println ("Waiting 52 more Seconds");
                    delay (52000);
                    println ("Roll Down Fabric");
                    stepper.setAcceleration(10000);
                    stepper.moveTo(-42000); 
                    stepper.runToPosition();
                    println("Waiting 38 seconds to roll back up.  Show's over...");
                    delay(38000);
                    println("Moving motor home");
                    stepper.moveTo(0);
                    stepper.runToPosition();
              }
      } 
 
  if (digitalRead(upOverride) == 0 ) 
      { 
        println ("Roll-up Fabric pressed");
        stepper.setSpeed(2000);
        stepper.runSpeed();  
        stepper.setCurrentPosition(0);
      } 
      
  //stepper.runToPosition();
  digitalWrite(LED_BUILTIN, LOW);

}
