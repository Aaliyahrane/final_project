const int xpin = A14;  //variable for x axis
const int ypin = A15;  // variable for y axis
const  int zpin = A16;  // variable for z axis

int ledPin = 32; // set up variable for first trigger
int ledPin1 = 31;
int ledPin2 = 30;

int timesOut = 0; // counter of sorts

int currentPlacex = 0;
int lastPlacex = 0;
int currentPlacey = 0;
int lastPlacey = 0;
int currentPlacez = 0;
int lastPlacez = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  track();
  setled();

}

void track () {

  int x = analogRead(xpin); // read in from x pin
  delay(100);
  int y = analogRead(ypin); // read in from y pin
  delay(100);
  int z = analogRead(zpin); //read in from z pin

  lastPlacex = currentPlacex; // lastplacex is equal to currentplacex
  currentPlacex = analogRead(xpin); //currentplacex is equal to what the pin reads in

  if (currentPlacex > 550 && lastPlacex < 550) {   // if button state reads high and the last reads low,
    timesOut ++;

  }

  lastPlacey = currentPlacey; // lastplacex is equal to currentplacex
  currentPlacey = analogRead(ypin); //currentplacex is equal to what the pin reads in

  if (currentPlacey > 520 && lastPlacey < 520) {   // if button state reads high and the last reads low,
    timesOut ++;
  }
  lastPlacez = currentPlacez; // lastplacex is equal to currentplacex
  currentPlacez = analogRead(zpin); //currentplacex is equal to what the pin reads in

  if (currentPlacez > 620 && lastPlacez < 620) {   // if button state reads high and the last reads low,
    timesOut ++;
  }
  Serial.print(x); //print out x pin reading
  Serial.print("\t"); // tab over

  Serial.print(y);  //print out y pin reading
  Serial.print("\t");  // tab over

  Serial.print(z);  //print out z pin reading

  Serial.print("\t");
  Serial.print(timesOut);
  Serial.print("\n");  // new line

}


void setled() {

  if (timesOut > 60) {
    digitalWrite(ledPin, HIGH);

    if (timesOut > 120) {
      digitalWrite(ledPin1, HIGH);

      if (timesOut > 180) {
        digitalWrite(ledPin2, HIGH);
      }
      if (timesOut > 200){  // just for demo purposes
        timesOut = 0;
      }
    }
  }


}



//need to create a threshhold that will count a movement
//or step once the motion goes outside of that threshhold


/* how could I go about saying that if the x y z axises'
    values are put outside of the threshold a certain
    number of times then the results will trigger one
    light and keep it on.
*/
// need to relate times run with the xyz going out of the
//threshold

// how do you say every time xyz goes out of the threshold add
//one to timesOut

//rather than make code based on numbers base it on change
// basically create the same scenario as the button states from the labs in the
//past with analog reads

