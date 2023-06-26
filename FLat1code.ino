// Define stepper motor connections and steps per revolution:
#define dirPin 49
#define stepPin 48



// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define motorInterfaceType 1


// Initialize the proximity sensors for each floor
const int floor1Sensor = 39;
const int floor2Sensor = 40;
const int floor3Sensor = 41;
const int floor4Sensor = 42;

// Initialize the push buttons for selecting going up and going down for floors 2 and 3
const int floor2UpButton = 2;
const int floor2DownButton = 3;
const int floor3UpButton = 4;
const int floor3DownButton = 5;

// Initialize the up button for floor 1 and down button for floor 4
const int floor1UpButton = 6;
const int floor4DownButton = 10;

// Initialize the separate push buttons to select the desired floor to go to 
const int floor1Button = 14;
const int floor2Button = 15;
const int floor3Button = 16;
const int floor4Button = 17;

// Initialize the stepper motor with L298 motor driver for the elevator pulley system





// Initialize the LCD with I2C for the display
#include <Stepper.h>
#include <Wire.h>

#include <LCD_I2C.h>
#include <AccelStepper.h>

LCD_I2C lcd(0x27, 16, 2);


// Initialize the variables for the elevator system
int currentFloor;
int desiredFloor = 0;
int floorAction = 0;
int action = 0;
int selection = 0;
int Direction = 0;
int a;
int halt=0;

// Motor A connections
int EN_A  = 9;
int IN1 = 8;
int IN2 = 7;

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);


// Initialize the functions for the elevator system







void setup() 
{
  // Set up the proximity sensors for each floor
  pinMode(floor1Sensor, INPUT);
  pinMode(floor2Sensor, INPUT);
  pinMode(floor3Sensor, INPUT);
  pinMode(floor4Sensor, INPUT);
  
  // Set up the push buttons for selecting going up and going down for floors 2 and 3
  pinMode(floor2UpButton, INPUT);
  pinMode(floor2DownButton, INPUT);
  pinMode(floor3UpButton, INPUT);
  pinMode(floor3DownButton, INPUT);
  
  // Set up the up button for floor 1 and down button for floor 4
  pinMode(floor1UpButton, INPUT);
  pinMode(floor4DownButton, INPUT);
  
  // Set up the separate push buttons to select the desired floor to go to
  pinMode(floor1Button, INPUT);
  pinMode(floor2Button, INPUT);
  pinMode(floor3Button, INPUT);
  pinMode(floor4Button, INPUT);

  
  
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(500);

  
   // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

   //To Set the control pins of the motor as an outputs
  pinMode(EN_A, OUTPUT);
 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
 
digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
 
 
  

  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
   
  }


void loop() {

   
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Initializing...");
   delay(500);
   lcd.setCursor(0,1);
   lcd.print("Please Wait");
   delay(500);
   action = 0;
   


 while(action == 0)
   {
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Idle...");
    lcd.setCursor(0,1);
    lcd.print("waiting pasahero");
    delay(500);
    
    
  // Check if the elevator has Arrived at a floor
  if (digitalRead(floor1Sensor) == LOW ) {
    currentFloor = 1;
    Display();
    delay(500);
    //openDoor();
    action = 1;
    //action = 1;
    
    
    } 
  else if (digitalRead(floor2Sensor) == LOW ) {
    currentFloor = 2;
    Display();
    delay(500);
    //openDoor();
    action = 1;
    //action = 1;
    
    } 
  else if (digitalRead(floor3Sensor) == LOW ) {
    currentFloor = 3;
    Display();
    delay(500);
    //openDoor();
    action = 1;
    //action = 1;
    
    } 
  else if (digitalRead(floor4Sensor) == LOW ) {
    currentFloor = 4;
    Display();
    delay(500);
    //openDoor();
    action = 1;
    //action = 1;
    
    }
   else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ERROR..ERROR");
    lcd.setCursor(0,1);
    lcd.print("ADJUST CAR!!");
    delay(600);
   }
  } 

 
    
 while (action == 1)
  {
   a=0;
   //lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Click your Floor...");
   //delay(2000);
   lcd.setCursor(0,1);
   lcd.print("button now");
   //delay(1000);
   
   
     // Check if a button for going up or going down has been pressed
   if (digitalRead(floor1UpButton) == HIGH) 
    {
      Direction = 1;
      floorAction = 1;
        if (currentFloor == 4)
        {
          a = 3;
          goDown();
           
      
          Arrived();
        }
        else if (currentFloor == 3)
        {
          a = 2;
          goDown();
           
      
          Arrived();
        }
        else if (currentFloor == 2)
        {
          a = 1;
          goDown();
           
      
          Arrived();
        }
        else if (currentFloor == floorAction)
        {
           
      
          Arrived();
        }
        
      }
      
  else if (digitalRead(floor2UpButton) == HIGH) 
  {
    floorAction = 2;
    Direction = 1;
   
      if (currentFloor < floorAction)
      {
          a = 1;
          goUp();
           
         
        
         
          Arrived();
      }
    
    
    else if (currentFloor > floorAction)
      {
        
        if (currentFloor == 3)
        {
          a = 1;
          goDown();
           
         
        
         
          Arrived();
        }
        else if (currentFloor == 4)
        {
          a = 2;
          goDown();
           
         
        
         
          Arrived();
        }
        
      }
      else if (currentFloor == 2)
      {
         
         
        
         
        Arrived();
      }
    }
  

   else if (digitalRead(floor2DownButton) == HIGH) 
  {
    floorAction = 2;
    Direction = 2;
   
      if (currentFloor < floorAction)
      {
          a = 1;
          goUp();
           
         
        
         
          Arrived();
      }
    
    
    else if (currentFloor > floorAction)
      {
        
        if (currentFloor == 3)
        {
          a = 1;
          goDown();
           
         
        
         
          Arrived();
        }
        else if (currentFloor == 4)
        {
          a = 2;
          goDown();
           
         
        
         
          Arrived();
        }
        
      }
      else if (currentFloor == 2);
      {
         
         
        
         
        Arrived();
      }
    }
      
   
    //floor 3
   else if (digitalRead(floor3UpButton) == HIGH) 
  {
    floorAction = 3;
    Direction = 1;
   
      if (currentFloor > floorAction)
      {
          a = 1;
          goDown();
           
         
        
         
          Arrived();
      }
    
    
    else if (currentFloor < floorAction)
      {
        
        if (currentFloor == 2)
        {
          a = 1;
          goUp();
           
         
        
         
          Arrived();
        }
        else if (currentFloor == 1)
        {
          a = 2;
          goUp();
           
         
        
         
          Arrived();
        }
        
      }
      else if (currentFloor == 3)
      {
         
         
        
         
        Arrived();
      }
    }
      
   

   else if (digitalRead(floor3DownButton) == HIGH) 
  {
    floorAction = 3;
    Direction = 2;
   
      if (currentFloor > floorAction)
      {
          a = 1;
          goDown();
           
         
        
         
          Arrived();
      }
    
    
    else if (currentFloor < floorAction)
      {
        
        if (currentFloor == 2)
        {
          a = 1;
          goUp();
           
         
        
         
          Arrived();
        }
        else if (currentFloor == 1)
        {
          a = 2;
          goUp();
           
         
        
         
          Arrived();
        }
        
      }
      else if (currentFloor == 3)
      {
         
         
        
         
        Arrived();
      }
    }
   
   

     //floor 4
   else if (digitalRead(floor4DownButton) == HIGH) 
  {
    floorAction = 4;
    Direction = 2;
    
        if (currentFloor == 1)
        {
          a = 3;
          goUp();
           
         
        
         
          Arrived();
        }
        else if (currentFloor == 2)
        {
          a = 2;
          goUp();
           
         
        
         
          Arrived();
        }
        else if (currentFloor == 3)
        {
          a = 1;
          goUp();
           
         
        
         
          Arrived();
        }
        else if (currentFloor == floorAction)
        {
          
         
        
         
          Arrived();
        }
  }
  }


  
  

// selection of desired floor
while ((action == 2)&& (selection == 1))
  {
   // Display the floor selection prompt on the LCD
    //lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("Select Floor: ");
    lcd.setCursor(0,1);
    lcd.print("1 2 3 4");
    
    // Wait for user input
    //while (true) {
    if (digitalRead(floor1Button) == HIGH) 
    {
       
        desiredFloor = 1;
        selection = 2;
        action = 3;
        halt = 0;
    
    
    } 
    else if (digitalRead(floor2Button) == HIGH) 
    {
      
        desiredFloor = 2;
        selection = 2;
        action = 3;
        halt = 0;
    
    } 
    else if (digitalRead(floor3Button) == HIGH) 
    {
      
        desiredFloor = 3;
        selection = 2;
        action = 3;
        halt = 0;
    
    } 
    else if (digitalRead(floor4Button) == HIGH) 
    {
      
        desiredFloor = 4;
        selection = 2;
        action = 3;
        halt = 0;
    
    }
    
    }


  // Check if a button for going up or going down has been pressed
  
  
  
while (halt == 0)
{
  
  
  if ((Direction == 1 )&& (currentFloor == 1)&& (desiredFloor == 2)&&(action == 3) )
  {
      toFloor();
        a = 1;
        goUp();
        action = 1;
        destination();
       
      }
   else if ((Direction == 1 )&& (currentFloor == 1)&& (desiredFloor == 3)&&(action == 3))
      {
        toFloor();
        a = 2;
        goUp();
        action = 1;
        destination();
        
      }
  else if ((Direction == 1 )&& (currentFloor == 1)&& (desiredFloor == 4)&&(action == 3))
      {
        toFloor();
        a = 3;
        goUp();
        action = 1;
        destination();
        
      }
  else if ((Direction == 1 )&& (currentFloor == 1)&& (desiredFloor == currentFloor)&&(action == 3))
      {
        toFloor();
        action = 1;
        destination();
        
      }
 
   else if ((Direction == 1 )&& (currentFloor == 2)&&(desiredFloor == 1)&&(action == 3))
    {
      
        invalid();
      }
   else if ((Direction == 1 )&& (currentFloor == 2)&&(desiredFloor == 3)&&(action == 3))
      {
        toFloor();
       a = 1;
        goUp();
        action = 1;
        destination();
        
      }
    else if ((Direction == 1 )&& (currentFloor == 2)&&(desiredFloor == 4)&&(action == 3))
      {
        toFloor();
        a = 2;
        goUp();
        action = 1;
        destination();
        
      }
    else if ((Direction == 1 )&& (currentFloor == 2)&&(desiredFloor == currentFloor)&&(action == 3))
      {
        toFloor();
        action = 1;
        destination();
        
      }
   else if ((Direction == 1 )&& (currentFloor == 3)&&(desiredFloor == 1)&&(action == 3))
  {
     
        invalid();
      }
  else if ((Direction == 1 )&& (currentFloor == 3)&&(desiredFloor == 2)&&(action == 3))
      {
        invalid();
      }
  else if ((Direction == 1 )&& (currentFloor == 3)&&(desiredFloor == 4)&&(action == 3))
      {
        a = 1;
        goUp();
        action = 1;
        destination();
        
      }
   else if ((Direction == 1 )&& (currentFloor == 3)&&(desiredFloor == currentFloor)&&(action == 3))
      {
        toFloor();
        action = 1;
        destination();
        
      }
 else if ((Direction == 1 )&& (currentFloor == 4)&&(desiredFloor == 1)&&(action == 3))
    {
        invalid();
      }
 else if ((Direction == 1 )&& (currentFloor == 4)&&(desiredFloor == 2)&&(action == 3))
      {
        invalid();
      }
  else if ((Direction == 1 )&& (currentFloor == 4)&&(desiredFloor == 3)&&(action == 3))
      {
        invalid();
      }
  else if ((Direction == 1 )&& (currentFloor == 4)&&(desiredFloor == currentFloor)&&(action == 3))
      {
        toFloor();
        action = 1;
        destination();
        
      }
    
    

  else if ((Direction == 2 )&& (currentFloor == 1)&& (desiredFloor >= 1)&&(action == 3))//going down
  {
        action = 0;
      }
      /*
  else if ((Direction == 2 )&& (currentFloor == 1)&& (desiredFloor == 3)&&(action == 3))
      {
        invalid();
      }
  else if ((Direction == 2 )&& (currentFloor == 1)&& (desiredFloor == 4)&&(action == 3))
      {
        invalid();
      }
  else if ((Direction == 2 )&& (currentFloor == 1)&& (desiredFloor == currentFloor)&&(action == 3))
      {
        destination();
      }*/
    
 else if ((Direction == 2 )&& (currentFloor == 2)&& (desiredFloor == 1)&&(action == 3))
    {
      toFloor();
        a = 1;
        goDown();
        action = 1;
        destination();
        
      }
 else if ((Direction == 2 )&& (currentFloor == 2)&& (desiredFloor >= 2)&&(action == 3))
      {
        action = 0;
       invalid();
      }
      /*
 else if ((Direction == 2 )&& (currentFloor == 2)&& (desiredFloor == 4)&&(action == 3))
      {
        invalid();
      }
  else if ((Direction == 2 )&& (currentFloor == 2)&& (desiredFloor == currentFloor)&&(action == 3))
      {
        
        destination();
        
      }*/
  else if ((Direction == 2 )&& (currentFloor == 3)&& (desiredFloor == 1)&&(action == 3))
    {
      toFloor();
        a = 2;
        goDown();
        action = 1;
        destination();
        
      }
  else if ((Direction == 2 )&& (currentFloor == 3)&& (desiredFloor == 2)&&(action == 3))
      {
        toFloor();
        a = 1;
        goDown();
        destination();
      
      }
 else if ((Direction == 2 )&& (currentFloor == 3)&& (desiredFloor >= 3)&&(action == 3))
      {
        toFloor();
        action = 0;
        invalid();
      }
  else if ((Direction == 2 )&& (currentFloor == 3)&& (desiredFloor == currentFloor)&&(action == 3))
      {
        toFloor();
        action = 0;
        destination();
        
      }
    
  else if ((Direction == 2 )&& (currentFloor == 4)&& (desiredFloor == 1)&&(action == 3))
    {
        toFloor();
        a = 3;
        goDown();
        action = 1;
        action = 0;
        destination();
        
      }
   else if ((Direction == 2 )&& (currentFloor == 4)&& (desiredFloor == 2)&&(action == 3))
      {
        toFloor();
        a = 2;
        goDown();
        action = 1;
        destination();
        
      }
  else if ((Direction == 2 )&& (currentFloor == 4)&& (desiredFloor == 3)&&(action == 3))
      {
        toFloor();
        a = 1;
        goDown();
        action = 1;
        destination();
       
      }
  else if ((Direction == 2 )&& (currentFloor == 4)&& (desiredFloor == currentFloor)&&(action == 3))
      {
        toFloor();
        action = 1;
        destination();
        
      }
   
  }
 
  }
  



void motorForward(){
  // Motor A Forward
  
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
    
}

void motorBackward(){
  // Motor A backward
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
 
}

void motorOff(){
  // Motor A Off
  //analogWrite(EN_A, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN_A, 0);
  
}


//Run the motor by accelerating from 0 to top speed
// then decelerating to 0
void motorRun() { 
  
  //To accelerate the motor from 0 to the maximum speed
 for (int i = 0; i < 15; i++) {
    analogWrite(EN_A, 200);
    
    delay(20);
  }
  
  /*//To Decelerate the motor from the maximum speed to 0
  for (int i = 15; i >= 0; --i) {
    analogWrite(EN_A, 200);
    //analogWrite(EN_B, i);
    delay(20);
  }
  */
  delay(300);
  //Finally to turn off the motors
  motorOff();
}

void goUp()
{
  // distances floor 1 to floor 2 8200 steps
  toFloor();
  // Set the target position:
  stepper.moveTo((a*8200));
  // Run to target position with set speed and acceleration/deceleration:
  stepper.runToPosition();
  stepper.setCurrentPosition(0);
  a = 0;

  //delay(1000);
   
}

void goDown()
{
  // distances floor 1 to floor 2 8200 steps
  toFloor();
  // Set the target position:
  stepper.moveTo(-(a*8200));
  // Run to target position with set speed and acceleration/deceleration:
  stepper.runToPosition();
  stepper.setCurrentPosition(0);
  a = 0;

  //delay(1000);
  
}
void Display()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current Floor: ");
  lcd.setCursor(0,1);
  lcd.print(currentFloor);
  //delay(2000);
}

void toFloor()
{
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Going to Floor...");
       lcd.setCursor(0,1);
       lcd.print("Please Wait...");
}

void Arrived()
{
      delay(500);
       
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Arrived");
       lcd.setCursor(0,1);
       lcd.print("To Floor...");
       
       currentFloor = floorAction;
      
        openD();
      closeD();
    delay (500);
      motorOff();
    delay (500);
       
       
    
    
       Display();
       
       selection = 1;
       action = 2;
       
       
}

void destination()
{
      delay(500);
       
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Arrived");
       lcd.setCursor(0,1);
       lcd.print("To destination");
       //delay(2000);
       currentFloor = floorAction;
       
      openD();
      closeD();
    
      
    delay (500);
      motorOff();
    delay (500);
  
  
       Display();
       
       selection = 0;
       action = 1;
       halt = 1;
       
       
       
  
}

void invalid(){
      delay(1000);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("invalid...");
       lcd.setCursor(0,1);
       lcd.print("selection");
       selection = 0;
       action = 0;
       halt = 1;
}

void openD(){
  lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Opening Door");
       lcd.setCursor(0,1);
       lcd.print("Please Enter");
  motorBackward();     
      motorRun();
    delay(1200);
}
 void closeD(){
  lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Closing Door");
       lcd.setCursor(0,1);
       lcd.print("Standby");
  motorForward();
      delay(3000);
      motorRun();
      delay(500);
 }
