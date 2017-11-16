const int xpin = A14;  //variable for x axis
const int ypin = A15;  // variable for y axis
const  int zpin = A16;  // variable for z axis

int ledPin = 32; // set up variable for first trigger
int ledPin1 = 31;
int ledPin2 = 30;

int timesOut = 0; // counter of sorts
int currentPlacex = 0;
int currentPlacey = 0;
int currentPlacez = 0;
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
  for ( timesOut = 1; timesOut <= 255; timesOut++) { // i dont quite understand the power of this

//         in the condition of the for loop I should be working with the xyz values
//         

    int x = analogRead(xpin); // read in from x pin
    delay(100);
    int y = analogRead(ypin); // read in from y pin
    delay(100);
    int z = analogRead(zpin); //read in from z pin


    Serial.print(x); //print out x pin reading
    Serial.print("\t"); // tab over

    Serial.print(y);  //print out y pin reading
    Serial.print("\t");  // tab over

    Serial.print(z);  //print out z pin reading

    Serial.print("\t");
    Serial.print(timesOut);
    Serial.print("\n");  // new line

    //if ( x > 550 or x < 490 ) {  // x axis threshold
    if (currentPlacex == ( x > 550 or x < 490)) {

      // timesOut ;
    }
    //    digitalWrite(ledPin, HIGH);
    //  } else {
    //    digitalWrite(ledPin, LOW);
    //  }
    //if ( y > 550 or y < 490) {   // y axis threshold
    if (currentPlacey == ( x > 550 or x < 490)) {

      timesOut ++;

    }
    //    digitalWrite(ledPin1, HIGH);
    //  } else {
    //    digitalWrite(ledPin1, LOW);
    //  }

    //if ( z > 650 or z < 610 ) {  // z axis threshold

    if (currentPlacez == ( x > 550 or x < 490)) {

      timesOut ++;
    }


    //    digitalWrite(ledPin2, HIGH);
    //  } else {
    //    digitalWrite(ledPin2, LOW);
    //  }

  }
}

void setled() {

  if (timesOut >= 60) {
    digitalWrite(ledPin, HIGH);

    if (timesOut >= 120) {
      digitalWrite(ledPin1, HIGH);

      if (timesOut >= 250) {
        digitalWrite(ledPin2, HIGH);
      }
    }
  }


}


// what makes motion important enough to track

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



