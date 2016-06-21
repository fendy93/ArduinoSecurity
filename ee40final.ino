#include <Password.h>
#include <Keypad.h> 
#define buzzer 10
#define led 11
#define led2 12
#define led3 13

int sound = 250;
int tf = 1;

//Sonar 1
int echoPin1 =2;
int initPin1 =3;
int distance1 =0;

//Sonar 2
int echoPin2 =4;
int initPin2 =5;
int distance2 =0;

//Sonar 3
int echoPin3 =6;
int initPin3 =7;
int distance3 =0;

//Sonar 4
int echoPin4 =8;
int initPin4 =9;
int distance4 =0;

Password password = Password( "DD40" );

const byte numRows = 4; //four rows
const byte numCols = 4; //four columns

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {22,24,26,28}; //Rows 0 to 3
byte colPins[numCols]= {30,32,34,36}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad keypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols); 

void setup(){

  pinMode(initPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(initPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(initPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(initPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
  //digitalWrite(ledPin,HIGH);
  //keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}
  
void loop(){
  
  distance1 = getDistance(initPin1, echoPin1);
  
  distance2 = getDistance(initPin2, echoPin2);
  
  distance3 = getDistance(initPin3, echoPin3);

  distance4 = getDistance(initPin4, echoPin4);
  
  
  char keypressed = keypad.getKey();
  
  if (keypressed != NO_KEY)
  {
    if (keypressed == '*')
    { 
      if ( password.evaluate() )
      {
        tf=0;
        digitalWrite(led3, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led, HIGH);
        noTone(buzzer);
      }
      password.reset();
    }
    
    else {
      
    if (keypressed == '#')
    {
      tf=1;
      password.reset();
    }
    else
    {
      password.append(keypressed);
    }
  }
 
  } 
  
  if (tf ==1) {
  doShit(distance1, distance2, distance3, distance4);
  }
  
  else{
    digitalWrite(led, HIGH);
  }
  
  delay(0);
}



int getDistance (int initPin, int echoPin){

 digitalWrite(initPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(initPin, LOW); 
 unsigned long pulseTime = pulseIn(echoPin, HIGH); 
 int distance = pulseTime/58;
 return distance;
 
}


void doShit(int dist1,int dist2,int dist3,int dist4){
   
   
   if ( ( (dist1 <=5) || (dist2<=5) || (dist3<=5) || (dist4<=5) ) &&  ( (dist1 >0) || (dist2>0) || (dist3>0) || (dist4>0) ) )  {
      digitalWrite(led3, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led, LOW);
      
      sound = 450;
      tone(buzzer, sound);
                    } 
   
    else{
      
     
    if ( ((dist1 <= 20) || (dist2 <= 20) ||(dist3 <= 20) ||(dist4 <= 20)) && ( (dist1 >5) || (dist2>5) || (dist3>5) || (dist4>5) ) ) {
      digitalWrite(led3, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led, LOW);
      
      sound = 250;
      tone(buzzer, sound);
                      } 

    else{
      
    if ( ((dist1 > 20) && (dist2 > 20) && (dist3 > 20) &&(dist4 > 20)) || ( (dist1 <= 0) && (dist2 <= 0) && (dist3 <= 0) &&(dist4 <= 0) ) ){
      Serial.println(" Out of range");
      digitalWrite(led3, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led, HIGH);
      noTone(buzzer);
                    }
        }
    }
 }
