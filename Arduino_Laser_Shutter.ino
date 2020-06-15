int inA1 = 11; // input 1 of the stepper                Connection pins on the arduino are 11 10 9 8  for the shutter that has an elbow on the connector and 7 6 5 4 for the other one, if shutters do not behave correctly turn around the connections 
int inA2 = 10; // input 2 of the stepper
int inB1 = 9; // input 3 of the stepper
int inB2 = 8; // input 4 of the stepper

int in2A1 = 7; // input 1 of the 2nd stepper
int in2A2 = 4; // input 2 of the 2nd stepper
int in2B1 = 6; // input 3 of the 2nd stepper
int in2B2 = 5; // input 4 of the 2nd stepper

int stepDelay = 10; // Delay between steps in milliseconds

void setup() {                
  pinMode(inA1, OUTPUT);     
  pinMode(inA2, OUTPUT);     
  pinMode(inB1, OUTPUT);     
  pinMode(inB2, OUTPUT);
  pinMode(in2A1, OUTPUT);     
  pinMode(in2A2, OUTPUT);     
  pinMode(in2B1, OUTPUT);     
  pinMode(in2B2, OUTPUT);       

  Serial.begin(9600);
  Serial.println("Shutter Arduino");
}

void step1() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, HIGH);   
  digitalWrite(inB1, HIGH);   
  digitalWrite(inB2, LOW);   
  delay(stepDelay);
  
}
void step2() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, HIGH);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, HIGH);   
  delay(stepDelay);
}
void step3() {
  digitalWrite(inA1, HIGH);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, HIGH);   
  delay(stepDelay);
}
void step4() {
  digitalWrite(inA1, HIGH);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, HIGH);   
  digitalWrite(inB2, LOW);   
  delay(stepDelay);
}
void stopMotor() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, LOW);   
}

void closeShutter() {
  step1();
  step3();
  step2();
}

void openShutter() {
  step3();
  step4();
  step1();
  step2();
}

void step21() {
  digitalWrite(in2A1, LOW);   
  digitalWrite(in2A2, HIGH);   
  digitalWrite(in2B1, HIGH);   
  digitalWrite(in2B2, LOW);   
  delay(stepDelay);
  
}
void step22() {
  digitalWrite(in2A1, LOW);   
  digitalWrite(in2A2, HIGH);   
  digitalWrite(in2B1, LOW);   
  digitalWrite(in2B2, HIGH);   
  delay(stepDelay);
}
void step23() {
  digitalWrite(in2A1, HIGH);   
  digitalWrite(in2A2, LOW);   
  digitalWrite(in2B1, LOW);   
  digitalWrite(in2B2, HIGH);   
  delay(stepDelay);
}
void step24() {
  digitalWrite(in2A1, HIGH);   
  digitalWrite(in2A2, LOW);   
  digitalWrite(in2B1, HIGH);   
  digitalWrite(in2B2, LOW);   
  delay(stepDelay);
}
void stop2Motor() {
  digitalWrite(in2A1, LOW);   
  digitalWrite(in2A2, LOW);   
  digitalWrite(in2B1, LOW);   
  digitalWrite(in2B2, LOW);   
}

void close2Shutter() {
  step23();
  step24();
  step22();
}

void open2Shutter() {
  step24();
  step23();
  step22();
}

void loop() {
  String Dummy = "";
  Dummy = SerialRead();

if (Dummy == "11111210111049"){      // Open Shutter one
  openShutter();
  Serial.println("MOVED");
}

else if (Dummy == "11111210111050"){     // Open Shutter two
  open2Shutter();
  Serial.println("MOVED");
}

else if (Dummy == "9910811111510149"){    // Close Shutter one
  closeShutter();
  Serial.println("MOVED");
}

else if (Dummy == "9910811111510150"){   // Close Shutter two
  close2Shutter();
  Serial.println("MOVED");
}

else if (Dummy == "100101109111"){
  Demo();
  Serial.println("MOVED");
}

else {
}
  
  stopMotor();
  stop2Motor();
  delay(50);
}

String SerialRead() {
  if (Serial.available() > 0)    // If the serial is trying to communicate calls the functiond SelectedCell() stated below and
Serial.println("-----------------------------------------------");  // print a dashed line 
  String inputData;                                                  // String that will determine the cell being measured
  inputData = String("");                                            // Assign a void value to the string CellNum
     delay(50);                                                   //Small delay to allow for the serial to buffer all the data
        if (Serial.available()>1)    // If there are in the serial 2 or 3 values (L12 counts as 3 and R1 counts as 2 values) read the seria, otherwise (see else if)
        {  
                inputData = String("");                          //Reset inputData to a blank space before reading
                for(int i = Serial.available();i>0;i--) // Take the amount of digits in the serial and read them; i.e if the Serial.available() is 3 it will read the serial 3 times
                {
                inputData += Serial.read(); // Append the read value to the previous one to form a complete string with all the values from the serial 
                }
                Serial.println(inputData);  //Print the raw data for development purposes //Comment if not developing
        }
return (inputData);     //As this is a function it returns the string of the inputData that has been selected
}

void Demo(){
  for (int i = 0; i < 13; i++){
    openShutter();
    open2Shutter();
    delay(10);
    closeShutter();
    close2Shutter();
    delay(10);
}
}

