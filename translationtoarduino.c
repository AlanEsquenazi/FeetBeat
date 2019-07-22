//Analog read pins for accelerometer
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;
int prevX = 0;
int prevY = 0;
int prevZ = 0;
int steps = -1;
unsigned long StartTime = millis();
bool going_up = false;
double valid_freq = 0;



void setup(){
  Serial.begin(9600);
}

void loop(){

  //read the analog values from the accelerometer
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
  /*
  Serial.print(" | z: ");
  Serial.println(zRead);
  Serial.println("Steps");Serial.println(steps);Serial.println('\n');
  */
  prevZ = zRead;
  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - StartTime;
  if(ElapsedTime>1000){
    StartTime=ElapsedTime;
    double curr_freq = steps/(ElapsedTime/1000);
    Serial.println(curr_freq);
  }
  delay(500); //slow down the serial display to be able to read easier
}
