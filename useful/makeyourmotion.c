//Analog read pins for accelerometer
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;
int prevX = 0;
int prevY = 0;
int prevZ = 0;
int dx, dy, dz;
double avx, avy, avz;
int dxs[5], dys[5], dzs[5];
const int calibrating = 5;
int delta = 5;
bool going_up = false;
void setup(){
  Serial.begin(9600); 
}
bool is_equal(int i1, double i2, int delta){
    if((i1-delta)<i2 && (i1+delta)>i2){
        return true;
    }else{
        return false;
    }
}
void detect_motion(int beg_x, int beg_y, int beg_z){
    int xRead = analogRead(xPin);
    int yRead = analogRead(yPin);
    int zRead = analogRead(zPin);
    int deltax = xRead-beg_x;
    int deltay = yRead-beg_y;
    int deltaz = zRead-beg_z;
    if(is_equal(deltax, dx, delta)&& is_equal(deltay, dy, delta)&& is_equal(deltaz,dy,delta)){
        Serial.println("motion detected!");Serial.println('\n');
    }
}
void loop(){

  //read the analog values from the accelerometer
  for(int i=0;i<calibrating;i++){
        Serial.println("Please go to one extremeof the motion");delay(5000);
        int xRead = analogRead(xPin);
        int yRead = analogRead(yPin);
        int zRead = analogRead(zPin);
        Serial.println("Please go to the other extreme of the motion");delay(5000);
        dxs[i]=analogRead(xPin)-xRead;dys[i]=analogRead(yPin)-yRead;dzs[i]=analogRead(zPin)-zRead;
  }
  for(int i=0;i<calibrating;i++){
      avx += dxs[i]/calibrating;
      avy += dys[i]/calibrating;
      avz += dzs[i]/calibrating;
  }
  Serial.println("Motion learned; the motion consists in an x variation of");Serial.println(avx);
  Serial.println("a y variation of");Serial.println(avy);Serial.println("and a z variation of");Serial.println(avz);
  Serial.println('\n');
  delay(5000);
while(1){
    Serial.println("now detecting");
    detect_motion(analogRead(xPin), analogRead(yPin), analogRead(zPin));
}
  //Output read values to Serial monitor
  /*
  Serial.print("x: ");
  Serial.print(xRead);
  Serial.print(" | y: ");
  Serial.print(yRead);
  Serial.print(" | z: ");
  Serial.println(zRead); 
  */
  //Serial.println("Steps");
}