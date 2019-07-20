//Analog read pins for accelerometer
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;
int prevX = 0;
int prevY = 0;
int prevZ = 0;
int steps = 0;
bool going_up = false;
void setup(){
  Serial.begin(9600); 
}

void loop(){

  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);
  if(zRead>(prevZ+8)){
    if(!going_up){
      going_up = true;
    }
  }else{
    if(going_up){
      going_up = false;
      steps++;
    }
  }
  //Output read values to Serial monitor
  Serial.print("x: ");
  Serial.print(xRead);
  Serial.print(" | y: ");
  Serial.print(yRead);
  Serial.print(" | z: ");
  Serial.println(zRead); 
  Serial.println("Steps");Serial.println(steps);Serial.println('\n');
  prevZ = zRead;
  delay(200); //slow down the serial display to be able to read easier
}

