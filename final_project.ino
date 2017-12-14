
const int xpin = A14;  //variable for x axis
const int ypin = A15;  // variable for y axis
const  int zpin = A16;  // variable for z axis

int ledPin = 32; // set up variable for first trigger
int ledPin1 = 31;
int ledPin2 = 30;
int ledPin3 = 23;
int ledPin4 = 22;
int ledPin5 = 21;

int timesOut = 0; // regular counter
int activeCounter = 0;

int currentPlacex = 0;
int lastPlacex = 0;
int currentPlacey = 0;
int lastPlacey = 0;
int currentPlacez = 0;
int lastPlacez = 0;

int modeSwitch = 29;

unsigned long currentTime  = 0; //this variable will be overwritten by millis() each iteration of loop
unsigned long pastTime     = 0; //no time has passed yet
int           currentState = 0; //the default state
unsigned long seconds = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(modeSwitch, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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

  lastPlacex = currentPlacex; // lastplacex is equal to currentplacex
  currentPlacex = analogRead(xpin);
  //currentplacex is equal to what the pin reads in

  if ((currentPlacex >= 465 && lastPlacex < 465) or (currentPlacex <= 465 && lastPlacex > 465)) {
    // if button state reads high and the last reads low,
    timesOut ++;
    activeCounter++;
  }
  lastPlacey = currentPlacey; // lastplacex is equal to currentplacex
  currentPlacey = analogRead(ypin); //currentplacex is equal to what the pin reads in

  if ((currentPlacey >= 600  && lastPlacey < 600) or (currentPlacey <= 600 && lastPlacey > 600)) {  // if button state reads high and the last reads low,
    timesOut ++;
    activeCounter++;

  }
  lastPlacez = currentPlacez; // lastplacex is equal to currentplacex
  currentPlacez = analogRead(zpin); //currentplacex is equal to what the pin reads in

  if ((currentPlacez >= 610  && lastPlacez < 610) or (currentPlacez <= 610 && lastPlacez > 610 )) {  // if button state reads high and the last reads low,
    timesOut ++;
    activeCounter++;

  }

  if (digitalRead(modeSwitch) == HIGH) {
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);

    activeCounter = timesOut;  // so that in the serial monitor, they actually come out the same in both modes
    Serial.print("\t");
    Serial.print("r");

    if (timesOut > 60 ) {
      digitalWrite(ledPin, HIGH); // these values in regular use would be much higher to fit more over a day

      if (timesOut > 120) {  // but for the purposes of demoing, they are lower
        digitalWrite(ledPin1, HIGH);

        if (timesOut > 180) {
          digitalWrite(ledPin2, HIGH);
        }
        if (timesOut > 250) { // just for demo purposes
          timesOut = 0;
          digitalWrite(ledPin, LOW);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, LOW);
        }
      }
    }
  }



  else if (digitalRead(modeSwitch) == LOW) {

    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);

    Serial.print("\t");
    Serial.print("a");
  }
  Serial.print("\t");
  Serial.print(timesOut);
  Serial.print("\t");
  Serial.print(activeCounter);
  Serial.print("\n");

  // if the counter reaches 100 steps in less than 60 seconds print the time
  //and save it somehow
  // then print the time between the next 100 steps and if the average time
  //is low then turn on some lights for a show

  pastTime    = currentTime; //currentTime at this point is the current time from the previous iteration, this should now be pastTime
  currentTime = millis();    //currentTime is now the current time (again).
  unsigned long timePassed = currentTime - pastTime; //this is roll-over proof, if currentTime is small, and pastTime large, the result rolls over to a small positive value, the time that has passed

  if (activeCounter >= 0) {


    //TIMER START
    if ( timePassed >= 1000 );           // increasing variable "seconds" every second
    {
      seconds ++;
      pastTime = currentTime;
    }

    if ( seconds == 60 && activeCounter >= 40)   { // for demo purposes
      digitalWrite(ledPin3, HIGH);
    }
    else if ( seconds == 120 && activeCounter >= 80) {
      digitalWrite(ledPin4, HIGH);
    }
    else if (seconds == 180 && activeCounter >= 100 ) {
      digitalWrite(ledPin5, HIGH);
    }
  }

  Serial.print (seconds);
  Serial.print ("\t");

}

//11.9.17 - need to create a threshhold that will count a movement
//or step once the motion goes outside of that threshhold


/*11.9.17 -  how could I go about saying that if the x y z axises'
    values are put outside of the threshold a certain
    number of times then the results will trigger one
    light and keep it on.
*/
//11.9.17 -  need to relate times run with the xyz going out of the
//threshold - DONE

// 11.16.17 - how do you say every time xyz goes out of the threshold add
//one to timesOut - DONE

//11.23.17 - rather than make code based on numbers base it on change
// basically create the same scenario as the button states from the labs in the
//past with analog reads - DONE

// 11.30.17 - get steps to count while in my pocket - DONE

// 11.30.17 - add a switch or button that would set a mode saying that after you take
// a certain amount of steps in a certain amount of time a light would go on - DONE

// 11.30.17 - I need to find a way to make the switch not mess everything up and still function
// need to get the active counter to be a second counter may not be able to set it equal to timesOut
//from there get some kind of average and based on whether the time between the 100 steps is high or low turn on
//different lights - DONE


