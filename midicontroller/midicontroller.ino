#define setPin0 5
#define setPin1 6
#define setPin2 7
#define setPin3 8

#define inputA0 18
#define inputA1 19
#define inputA2 20
#define inputA3 21
#define inputSwitch 10

#define outputLed 9

#define startbit 0

//set vars
int inputVarA0 = 0;
int inputVarA1 = 0;
int inputVarA2 = 0;
int inputVarA3 = 0;
boolean inputVarSwitch = 0;

int inputOldVarA0 = 0;
int inputOldVarA1 = 0;
int inputOldVarA2 = 0;
int inputOldVarA3 = 0;
boolean inputOldVarSwitch = 0;

//#define byte unsigned char 
// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity)
{
  MIDIEvent noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MIDIUSB.write(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity)
{
  MIDIEvent noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MIDIUSB.write(noteOff);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value)
{
  MIDIEvent event = {0x0B, 0xB0 | channel, control, value};
  MIDIUSB.write(event);
}

void setPin(int channel) // function to select pin on 74HC4067
{
  digitalWrite(setPin0, bitRead(channel, 0));
  digitalWrite(setPin1, bitRead(channel, 1));
  digitalWrite(setPin2, bitRead(channel, 2));
  digitalWrite(setPin3, bitRead(channel, 3));
}

void setup()
{
  //define set pins as output
  pinMode(setPin0, OUTPUT);
  pinMode(setPin1, OUTPUT);
  pinMode(setPin2, OUTPUT);
  pinMode(setPin3, OUTPUT);

  //define analog inputs
  pinMode(inputA0, INPUT);
  pinMode(inputA1, INPUT);
  pinMode(inputA2, INPUT);
  pinMode(inputA3, INPUT);

  //define led switches
  pinMode(inputs, INPUT);
  pinMode(outputLed, OUTPUT);
}

void loop()
{
  for(int i=0; i<16; i++){
      setPin(i);

      inputVarA0 = analogRead(inputA0) * 128 ) / 1024;

      if (inputVarA0 != inputOldVarA0)
      {
        noteOn(0, startbit+i, (inputVarA0);
        inputOldVarA0 = inputVarA0;
      }

      inputVarA1 = analogRead(inputA1) * 128 ) / 1024;

      if (inputVarA1 != inputOldVarA1)
      {
        noteOn(0, startbit+16+i, (inputVarA1);
        inputOldVarA1 = inputVarA1;
      }

      inputVarA2 = analogRead(inputA2) * 128 ) / 1024;

      if (inputVarA2 != inputOldVarA2)
      {
        noteOn(0, startbit+32+i, (inputVarA2);
        inputOldVarA2 = inputVarA2;
      }

      inputVarA3 = analogRead(inputA3) * 128 ) / 1024;

      if (inputVarA3 != inputOldVarA3)
      {
        noteOn(0, startbit+48+i, (inputVarA3);
        inputOldVarA3 = inputVarA3;
      }
      
      inputVarSwitch = digitalRead(inputSwitch);

      if (inputVarSwitch != inputOldVarSwitch)
      {
        if (inputVarSwitch){
            noteOn(0, startbit+64+i, 128);
        }
        else{
            noteOff(0, startbit+64+i, 0);
        }
        inputOldVarSwitch = inputVarSwitch;
      }
  }
  MIDIUSB.flush();
  delay(10);
}