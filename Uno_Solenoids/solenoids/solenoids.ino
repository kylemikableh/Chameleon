/**
 * Chameleon Music Robot HUA Project
 * By Kyle Mikolajczyk, Tom Nurse, Ben Draper, Daniel Santamaria
 * 11/30/2020
 */

#define SOLENOID_1_PIN 8
#define SOLENOID_2_PIN 9
#define SOLENOID_3_PIN 10
#define SOLENOID_4_PIN 11
#define SOLENOID_5_PIN 12
#define SOLENOID_6_PIN 13
 
void setup() 
{
  //First we have to establish serial communication
  Serial.begin(9600);

  //Next the pinmodes that will control each solenoid set to OUTPUT
  pinMode(SOLENOID_1_PIN, OUTPUT);
  pinMode(SOLENOID_2_PIN, OUTPUT);
  pinMode(SOLENOID_3_PIN, OUTPUT);
  pinMode(SOLENOID_4_PIN, OUTPUT);
  pinMode(SOLENOID_5_PIN, OUTPUT);
  pinMode(SOLENOID_6_PIN, OUTPUT);
}

void loop()
{  
  //If we are getting serial communication, do this
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    int inByte1 = Serial.read(); // read the first byte
    Serial.print("RECIEVED ");
    Serial.println(inByte1); // print the variable inByte1 to the serial monitor
    //we will also have to be reading the duration(note lenghts here)

    //Here we will have to assign the serial output variables to solenoids and dispatch
  }
  else
  {
    //Did not recieve serial, panic!  
    Serial.println("Not recieving serial signal. Will retry in 5 seconds...");
    delay(5000);
  }
}

/**
 * I am thinking this function should actually send commands to solenoids
 */
void dispatch(int solenoid, int duration)
{
  
}
