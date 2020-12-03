/**
 * Chameleon Music Robot HUA Project
 * By Kyle Mikolajczyk, Tom Nurse, Ben Draper, Daniel Santamaria
 * 11/30/2020
 */

#define SOLENOID_1_PIN 4
#define SOLENOID_2_PIN 5
#define SOLENOID_3_PIN 6
#define SOLENOID_4_PIN 7
#define SOLENOID_5_PIN 12
#define SOLENOID_6_PIN 13

#define MIDI_1 72
#define MIDI_2 73
#define MIDI_3 74
#define MIDI_4 75
#define MIDI_5 76
#define MIDI_6 77
 
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
    delay(10); 
    int inByte2 = Serial.read();
    Serial.print("RECIEVED ");
    Serial.print(inByte1); // print the variable inByte1 to the serial monitor
    Serial.print(" ");
    Serial.println(inByte2);

    //Solenoid 1 will be C4 on the piano which is 72 from MIDI
    dispatch(inByte1, inByte2); //Send notes recieved
  }
}

/**
 * This function handles the recieved channels and velocity from MIDI
 * @args int channel MIDI channel recieved, int velocity Velocity recieved
 * @return
 */
void dispatch(int channel, int velocity)
{
  int pin = 0;
  if(channel == MIDI_1) 
  {
    pin = SOLENOID_1_PIN;
  }
  else if(channel == MIDI_2) 
  {
    pin = SOLENOID_2_PIN;
  }
  else if(channel == MIDI_3) 
  {
    pin = SOLENOID_3_PIN;
  }
  else if(channel == MIDI_4) 
  {
    pin = SOLENOID_4_PIN;
  }
  else if(channel == MIDI_5) 
  {
    pin = SOLENOID_5_PIN;
  }
  else if(channel == MIDI_6) 
  {
    pin = SOLENOID_6_PIN;
  }

  if(pin == 0)
  {
    //Not a recognized note, return
    return;
  }
  
  //0 velocity means stop note, aka set to low
  if(velocity == 0)
  {
    digitalWrite(pin, LOW);
    Serial.print("Set pin ");
    Serial.print(pin);
    Serial.println(" to LOW.");
  }
  else if(velocity > 0) //Means play, we do not have a velocity for a plectrum
  {
    digitalWrite(pin, HIGH);
    Serial.print("Set pin ");
    Serial.print(pin);
    Serial.println(" to HIGH.");
  }
  else
  {
    //garbage recieved don't do anything
    return;
  }
}
