/* Declare the variables that will be used in the sketch */
int motorSpeed;
int x;
int counter = 0;
int motorTurns = 0;
int IRsensor = 1;

/* The setup routine will run once, when the reset button is pressed. 
The setup routine is typically used to initialize the pins.
Since this is a simulation, the pins will not be initialized. */
void setup() {
  Serial.println("Please open the serial monitor, press any key, and press 'Send'. This simulates the push button to start acceleration.");
  Serial.begin(9600);
}

/* The loop routine will run continuously. The main body of your code (the instructions for the Arduino) should be contained within this routine. */
void loop() {
  // read the state of the serial monitor to see if a key has been pressed
  if(Serial.available() > 0) {                // if it has been pressed, enter the loop
    Serial.println("Button pressed");         // print to the serial monitor
    Serial.println("Test run beginning");
    // use a for loop to ramp up the motor speed
    for(x = 10; x <= 255; x++) {
      motorSpeed = x;                         // set motor speed to the value of 'x'
      delay(50);
    } // close for loop
    Serial.println("Acceleration Done");      // print to the serial monitor when the acceleration is at full speed
  // while loop that simulates the reading of an IR sensor. Every 20 "motor turns", a line appears.
    while(counter < 7) {                        // stay in this loop until 7 lines have been detected
      while(motorTurns < 20) {                  // the while loop here is supposed to simulate to the "if(val == 0)" line of code.
        motorTurns++;
        Serial.println(" ");                   
        delay(50);
      } // end while loop
      counter++;                                // count the "line" that appears after 20 motor turns
      Serial.println("------------------");
      motorTurns = 0;                           // update motorTurns back to 0
    } //end while loop
    Serial.println("7 lines detected... deceleration beginning");
    // use a for loop to ramp down motor speed
    for(x = 255; x >= 0; x--) {
      motorSpeed = x;
      delay(50);
    } // end for loop
    Serial.println("Deceleration done");
  } // end if statement
} // end loop routine
