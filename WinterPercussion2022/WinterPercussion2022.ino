/*

   Abstract:
 Change Log:  20-jan-2022 Created.
              01-feb-2022 Changed pins for DIR && PUL to be closer for connectors
              31-mar-2022 Mark changed direction and speed.


*/

#define __DEBUG__
#ifdef __DEBUG__
   #define print(...)   Serial.print(__VA_ARGS__)
   #define println(...) Serial.println(__VA_ARGS__)
#else
   #define print(...)
   #define println(...)
#endif


//#include <LowPower.h>
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
#define recD0 9        // From wireless receiver1 -- Xmtr Pin = 4
#define recD1 10        // From wireless receiver2 -- Xmtr Pin = 3
#define recD2 11        // From wireless receiver3 -- Xmtr Pin = 1
#define recD3 12        // From wireless receiver4 -- Xmtr Pin = 2
#define downOverride 6
#define upOverride 8
#define returnPin 11  
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed and acceleration:
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(downOverride, INPUT_PULLUP); 
  pinMode(upOverride, INPUT_PULLUP);
  #ifdef __DEBUG__
     Serial.begin(9600);
  #endif

}

void loop() {
  

 // Different props may need different distances based on thickness of the cloth
   //LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
  // Run to target position with set speed and acceleration/deceleration:
  if (digitalRead(downOverride) == 0 ) {   //|| digitalRead(recD2) == HIGH) { 
        digitalWrite(LED_BUILTIN, HIGH);
        println ("Waiting 55 Seconds");
        delay(55000);
        println ("Roll Down Fabric");
        stepper.setMaxSpeed(7500); // 600 = 12s ;  800 = 10 sec; 1000= 8 sec
        stepper.setAcceleration(10000);
        stepper.moveTo(-42000); 
      } 

  if (digitalRead(upOverride) == 0 ) { // || digitalRead(recD3) == HIGH) {  //
        println ("Roll-up Fabric");
        stepper.setAcceleration(300);
        stepper.setMaxSpeed(2000); // 600 = 12s ;  800 = 10 sec; 1000= 8 sec
        stepper.moveTo(0); 
      } 
      
  println("Execute.");    
  stepper.runToPosition();
  digitalWrite(LED_BUILTIN, LOW);

}
