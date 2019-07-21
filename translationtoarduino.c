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
int bpms[100];
char *identifiers[100];
int last_freqs[10];
char *last_played[10];
double valid_freq = 0;
double delta = 10;
int check_full(){
    for(int i=9;i>=0;i--){
        if(last_freqs[i]>=10){
            return i;
        } 
    }
    return 0;
}
int check_full_played(){
    for(int i=9;i>=0;i--){
        if(last_played[i]>="0"){
            return i;
        } 
    }
    return 0;
}
int in_last_played(char* to_test){
    for(int i=0;i<10;i++){
        if(last_played[i]==to_test){
            return i;
        }
    }
    return 10000;
}
void update_last_played(char* to_play){
    if(check_full_played()){
        last_played[check_full_played()+1]=to_play;
    }else{
        for(int i=1;i<9;i++){
            last_played[i-1]=last_played[i];
        }
        last_played[9]=to_play;
    }
}
char* decide_song(){
    double upper_bound = valid_freq+delta;
    double lower_bound = valid_freq-delta;
    int where_lower=0, where_upper=10000;
    int how_many_songs = sizeof(bpms);
    for(int i=0;i<how_many_songs;i++){
        if(bpms[i]>=lower_bound){
            where_lower=i;
            break;
        }
    }
    for(int i=where_lower;i<how_many_songs;i++){
        if(bpms[i]>upper_bound){
            where_upper=i;
            break;
        }
    }
    if(where_upper==10000){
        where_upper=(how_many_songs);
    }
    int best_choice =0;
    for(int i=lower_bound;i<upper_bound;i++){
        if(in_last_played(identifiers[i])==100000){
            update_last_played(identifiers[i]);
            return identifiers[i];
        }else{
            best_choice = max(best_choice, in_last_played(identifiers[i]));
        }
    }
    update_last_played(last_played[best_choice]);
    return last_played[best_choice];
}
void update_freq(){
    valid_freq = 0;
    int nonzero = 10;
    for(int i=0;i<10;i++){
        if(last_freqs[i]<10){
            nonzero--;
        }
    }
    for(int i=0;i<10;i++){
        if(last_freqs[i]>=10){
            valid_freq += last_freqs[i]/nonzero;
        }
    }
}
void update_flist(int is_full, double curr_freq){
    if(is_full==0){
        for(int i=1;i<10;i++){
            last_freqs[i-1]=last_freqs[i];
        }
        last_freqs[9]=curr_freq;
    }else{
        last_freqs[is_full]=curr_freq;
    }
}
void setup(){
  bpms[0] = 100;
  identifiers[0] = "7xGfFoTpQ2E7fRF5lN10tr";
  last_freqs[0]=0;last_freqs[1]=0;
last_freqs[2]=0;last_freqs[3]=0;last_freqs[4]=0;last_freqs[5]=0;last_freqs[6]=0;last_freqs[7]=0;last_freqs[8]=0;last_freqs[9]=0;
last_played[0]="0";last_played[1]="0";last_played[2]="0";last_played[3]="0";last_played[4]="0";last_played[5]="0";last_played[6]="0";last_played[7]=0;last_played[8]="0";last_played[9]="0";

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
  Serial.print(" | z: ");
  Serial.println(zRead); 
  Serial.println("Steps");Serial.println(steps);Serial.println('\n');
  prevZ = zRead;
  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - StartTime;
  if(ElapsedTime>1000){
    StartTime=ElapsedTime;
    double curr_freq = steps/(ElapsedTime/1000);
    update_flist(check_full(),curr_freq);
  }
  delay(200); //slow down the serial display to be able to read easier
}