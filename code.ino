#include<NewPing.h>  //including ultra sonic library 
#include <SoftwareSerial.h> // including bluetooth ibrary 

// For L298n driver:
#define enA 10 // Set motor A enable pin 10 
#define in1 12 // set motor A  in1 pin 
#define in2 13 // set motor A  in2 pin
#define in3 7  // set motor B  in3 pin 
#define in4 8  // set motor B  in4 pin 
#define enB 9  // Set motor B enable pin  

// For bluetooth:
// define the bluetooth serial as my serial
SoftwareSerial myserial (2,3); //tx at 3

#define R_S A0 // set right ir sensor to A0 pin 
#define L_S A1 // set Left ir sensor to A1 pin 

//For ultraSoinc:
#define TRIG A2 // set trig to A2
#define ECHO A3 // set echo to A3

#define MAX_DISTANCE 100 // Define ultrasonic range  

// define the ultrasonic Lib. as sonar
NewPing sonar(TRIG, ECHO, MAX_DISTANCE); 


void setup(){ // put your setup code here, to run once
// Set the arduino and bluetooth data rate in 9600 bits per second for serial data transmission
myserial.begin(9600);
Serial.begin(9600);

// declare ir sensors as input  
pinMode(R_S, INPUT); 
pinMode(L_S, INPUT); 

 // declare driver pins as output
pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT); 
pinMode(in4, OUTPUT); 
pinMode(enB, OUTPUT);


// set motors speed to 150/255 duty cycle 
analogWrite(enA, 150); 
analogWrite(enB, 150); 
delay(100);
}
void loop(){
  delay(10); // stabilty delays ;)
  
  if(myserial.available()) // if the bluetooth connection is True
   {
    int switch_A_M = myserial.read(); // assign bluetooth reading into var: switch_A_M , every button had a speacific number. 
    int distance = sonar.ping_cm(); // assign the ultrasonic destance reading into var: distance

 //Bulid a switch to switch between the manual and automatic case depinding on the bluetooth value
    switch (switch_A_M) {
    case 99: // if the automatic button (99) pressed >> go to automatic infinty loop:
   while(true)
   {
    delay(10);
    automatic: // Automatic label to get back here once it called from anywhere
    
  // reading the serial and distance again
    int distance = sonar.ping_cm();
    
       // making a new switches for only one selection ;)
       int switch_B;
    int Switch; 
    
    // if ultra sonic sees an obescale, avodid it throuing by its right
if(distance <=15) {  
   Stop();
  delay(100);
    if  (myserial.read() == 101){goto manual;} //if manual button bressed break every thing and go to manual label
  turnRight();
    if  (myserial.read() == 101){goto manual;}
  delay(350);
    if  (myserial.read() == 101){goto manual;}
  forword();
    if  (myserial.read() == 101){goto manual;}
  delay(500);
    if  (myserial.read() == 101){goto manual;}
  turnLeft();
    if  (myserial.read() == 101){goto manual;}
  delay(350);
    if  (myserial.read() == 101){goto manual;}
  forword();
    if  (myserial.read() == 101){goto manual;}
  delay(700);
    if  (myserial.read() == 101){goto manual;}
  turnLeft();
    if  (myserial.read() == 101){goto manual;}
  delay(300);
    if  (myserial.read() == 101){goto manual;}
  forword();
    if  (myserial.read() == 101){goto manual;}
  delay(400);
    if  (myserial.read() == 101){goto manual;}
  turnRight();
    if  (myserial.read() == 101){goto manual;}
  delay(400);
    if  (myserial.read() == 101){goto manual;}
}else {
  
/* 
since you're here, you pass by one of 2 situation:
1) there wasn't obstacle so the distance var. was > 15 and you skipped the obstacle avodiance code ↑ and started the line following one ↓
2) there was an obstacle so the distance var. was <= 15 and you started the obstacle avodiance code ↑ and skipped the line following one ↓
in case 1) you're going in the liner follwer 
in case 2) you're goning to the end of the endless loop and the distance will be > 15 then you're going to the line follwer too :)
 */


// if the digital reding of both left and right sensor is 0 (white) assign in Switch value: 20
if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){ Switch = 20;} 

// if the digital reding of left sensor is 0 and right sensor is 1 (black) assign in Switch value: 25

if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){Switch = 25;}

// if the digital reding of left sensor is 1 and right sensor is 0 assign in Switch value: 30  
if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){Switch = 30;}

// if the digital reding of left sensor is 1 and right sensor is 1 assign in Switch value: 35 
if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){Switch = 35;}

// switch reduces the action may taken into the only possible cases, it make a safe loop for code
    switch(Switch){
          switch_B = myserial.read(); // if the manual button pressed assign switch_B var. to 120
              if (switch_B == 101){
      Switch = 120; }
      
 case 20 : // forword case 
 
  forword(); // call the function that make the robot move forward
  
  delay(70); // hold on in this case a bit
    
  break; // break the switch and stuck in the automtaic loop over again and again 

 
 case 25 : // rotate right casae
   turnRight();
  delay(70);
   break;
 case 30 : // rotate left casae
   turnLeft();
    delay(70);
   break; 
 case 35 : // stop case 
   Stop();
    delay(70);
   break;
 case 120: // the manual loop case
  goto manual;
  break;
      }
   } // the bracket else of the distance condition 
   } // the bracket of automatic infity loop 
   
 break; // useless break of automatic case you'll never reach 
  
 case 101: // if the manual button (99) pressed >> go to manual infinty loop:
       while(true){
        manual: // label manual ;)
        Stop(); // stop in case you come running from automatic loop
        
        while(true){ // another infinty loop to not stop every time you break the manual switch 
      int switch_B = myserial.read();
      switch (switch_B){ // manual selection switch 

// HINT: the app. was programmed to send the button number as long as you hold it and send 0 when you relase 
        
      case 50: // forward case,
      
      forword();
      
   break; // break the forward case and stuk in the switch infinty loop
   // if no button of our case is pressed, nothing happen but you still in the loop
   
      case 52: //  backword case
           backword(); 
    break;
      case 49: //  turn left case
           turnLeft();
   break;
     case 51: //  turn right case
           turnRight();
      break;
    case 99: // if automatic button pressed go to stuck in automatic loop ;)
         goto automatic;
       break;
         
      }
      }
     delay(10);
} break;
    }}}

    
void forword(){  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void backword(){  //borword
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, HIGH);  //Right Motor backword Pin 
digitalWrite(in3, HIGH);  //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
}

void turnRight(){ //turnRight
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW); //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
}

