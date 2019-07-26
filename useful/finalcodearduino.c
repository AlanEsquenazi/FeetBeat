//Analog read pins for accelerometer
//const int xPin = 0;
//const int yPin = 1;
#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART uart = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
const int zPin = 2;
int prevX = 0;
int prevY = 0;
int prevZ = 0;
float steps = -1;
float counter = 0;
int now_playing = 0, now_last = 30;
unsigned long StartTime = millis();
bool going_up = false;
int bpms[9];
char *identifiers[9];
int durations[9];
int last_freqs[10];
char *last_played[10];
float valid_freq = 0;
float delta = 10;
int lower_bound1(int low, int high, int value){
    int middle = (low+high)/2;
    //cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<endl;
    if(value<=bpms[0]){
        return 0;
    }if(value>=bpms[8]) return 8;
    if(bpms[middle]<=value && bpms[middle+1]>value){
    //    cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"r"<<endl;
        return middle;
    }else if(bpms[middle+1]<=value){
      //  cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"right"<<endl;
        lower_bound1(middle, high, value);
    }else{
        //cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"left"<<endl;
        lower_bound1(low, middle, value);
    }
}
int upper_bound1(int low, int high, int value){
    int middle = (low+high)/2;
    //cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"up"<<endl;
    if(value>=bpms[8]){
        //printf("%d %d %d",100, value, bpms[10]);
        return 8;
    }
    if(value<bpms[0]) return 0;
    if(bpms[middle]>value && bpms[middle-1]<=value){
        //cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"r"<<endl;
        //printf("%d %d", 1000, middle);
        return middle;
    }else if(bpms[middle-1]<=value){
        //cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"right"<<endl;
        //printf("%d %d", 763, middle);
        upper_bound1(middle, high, value);
    }else{
        //cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"left"<<endl;
        //printf("%d %d %d", 12567, middle, 999);
        upper_bound1(low, middle, value);
    }
}
int where_in_songs(char* name){
    for(int i=0;i<sizeof(identifiers);i++){
        if(identifiers[i]==name){
            return i;
        }
    }
}
int check_full_played(){
    for(int i=9;i>=0;i--){
        if(last_played[i]=="0"){
            return i-1;
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
    float upper_bound = valid_freq+delta;
    float lower_bound = valid_freq-delta;
//    cout<<"lb"<<lower_bound<<"up"<<upper_bound<<endl;
//    Serial.println("ub");Serial.println(upper_bound);Serial.println("lb");Serial.println(lower_bound);
    int where_lower=0, where_upper=10000;
    where_lower=lower_bound1(0,9,lower_bound);
    where_upper=upper_bound1(0,9,upper_bound);
    int how_many_songs = 8;
    /*
    for(int i=0;i<how_many_songs;i++){
        if(bpms[i]>=lower_bound){
            where_lower=i;
            break;
        }
    }
  //  Serial.println("where_lower");Serial.println(where_lower);Serial.println('\n');
    cout<<"vaientrar";
    for(int i=how_many_songs;i>=where_lower;i--){
        cout<<"i"<<i<<"bpmsi"<<bpms[i]<<"up"<<upper_bound<<endl;
        if(bpms[i]<=upper_bound){
            cout<<"achou"<<i<<endl;
            where_upper=i;
            break;
        }
    }
    */
    if(upper_bound<(bpms[0]-delta)){
        //cout<<"eh";
        where_upper=0;
        now_playing = 0;now_last=durations[0];
        update_last_played(identifiers[0]);
        return identifiers[0];
    }
    else if(where_upper==10000){
        //cout<<"eh2";
        where_upper= how_many_songs;
    }
    //Serial.println("where_upper");Serial.println(where_upper);Serial.println('\n');
    int best_choice = 9;
    //cout<<"wl"<<where_lower<<"wu"<<where_upper<<endl;
    for(int i=where_lower;i<=where_upper;i++){
        //cout<<"looopando"<<endl;
        if(in_last_played(identifiers[i])==10000){
            update_last_played(identifiers[i]);
            now_playing = i;now_last=durations[i];
      //      Serial.println("i");Serial.println(i);Serial.println('\n');
      //cout<<"retornou"<<i<<" "<<identifiers[i];
            return identifiers[i];
        }else{
            //cout<<"caso2"<<endl;
          if(in_last_played(identifiers[i])<=best_choice){
            now_playing=i;now_last=durations[i];
          }
            best_choice = min(best_choice, in_last_played(identifiers[i]));
        }
    }
    int answer = where_in_songs(last_played[best_choice]);  
    update_last_played(last_played[best_choice]);
    now_playing = answer;now_last=durations[answer];
    //Serial.println("i");Serial.println(i);Serial.println('\n');
    return last_played[best_choice];
}
float update_freq(){
    float vf = 0;
    int nonzero = 10;
    for(int i=0;i<10;i++){
        if(last_freqs[i]==0){
            nonzero--;
        }
    }
    for(int i=0;i<10;i++){
        if(last_freqs[i]!=0){
            vf += last_freqs[i]/nonzero;
        }
    }
    return vf;
}
void update_flist(float curr_freq){
        for(int i=1;i<10;i++){
            last_freqs[i-1]=last_freqs[i];
        }
        last_freqs[9]=curr_freq;
}
void setup(){
  bpms[0] = 84;
  identifiers[0] = "0.mp3";
  durations[0]=5;
  bpms[1] = 95;
  identifiers[1] = "1.mp3";
  durations[1]=25;
  bpms[2] = 109;
  identifiers[2] = "2.mp3";
  durations[2]=15;
  bpms[3] = 119;
  identifiers[3] = "3.mp3";
  durations[3]=35;
  bpms[4] = 126;
  identifiers[4] = "4.mp3 ";
  durations[4]=50;
  bpms[5] = 139;
  identifiers[5] = "5.mp3";
  durations[5]=30;
  bpms[6] = 140;
  identifiers[6] = "6.mp3";
  durations[6]=30;
  bpms[7] = 144;
  identifiers[7] = "7.mp3";
  durations[7]=70;
  bpms[8] = 172;
  identifiers[8] = "8.mp3";
  durations[8]=40;
  last_freqs[0]=0;last_freqs[1]=0;
last_freqs[2]=0;last_freqs[3]=0;last_freqs[4]=0;last_freqs[5]=0;last_freqs[6]=0;last_freqs[7]=0;last_freqs[8]=0;last_freqs[9]=0;
last_played[0]="0";last_played[1]="0";last_played[2]="0";last_played[3]="0";last_played[4]="0";last_played[5]="0";last_played[6]="0";last_played[7]=0;last_played[8]="0";last_played[9]="0";
last_played[10]="0";last_played[11]="0";last_played[12]="0";last_played[13]="0";last_played[14]="0";last_played[15]="0";last_played[16]="0";last_played[17]=0;last_played[18]="0";last_played[19]="0";
    //uart.setDeviceName("Fetbet"); /* 7 characters max! */
  //uart.begin();
  Serial.begin(9600); 
}

void loop(){
  //read the analog values from the accelerometer
  int zRead = analogRead(zPin);
  //Serial.println("pz");Serial.println(prevZ);Serial.println("z");Serial.println(zRead);
  if(zRead>(prevZ+8)){
    if(!going_up){
      going_up = true;
    }
  }else{
    if(going_up){
      //Serial.println("step");
      going_up = false;
      steps++;
    }
  }
  //Output read values to Serial monitor
  //Serial.print(" | z: ");
  //Serial.println(zRead); 
  //Serial.println("Steps");Serial.println(steps);Serial.println('\n');
  //Serial.println("np");Serial.println(now_playing);
  //Serial.println("playing out");Serial.println(identifiers[now_playing]);Serial.println("lasts for");Serial.println(durations[now_playing]);Serial.println('\n');
  prevZ = zRead;
  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - StartTime;
  //Serial.println("elt");Serial.println(ElapsedTime);Serial.println('\n');Serial.println("stt");Serial.println(StartTime);Serial.println('\n');Serial.println("curt");Serial.println(CurrentTime);
  if(ElapsedTime>1000){
    counter+=(ElapsedTime/1000);
    //Serial.println("counter");Serial.println(counter);Serial.println('\n');
    StartTime=CurrentTime;
    //Serial.println("steps");Serial.println(steps);Serial.println('\n');
    if(steps>=0){
    float curr_freq = 2*(60*steps)/(ElapsedTime/1000);
    //Serial.println("currfreq");Serial.println(curr_freq);Serial.println('\n');
    update_flist(curr_freq);
    }
    if(counter>=durations[now_playing]){
      //Serial.println("counter");Serial.println(counter);Serial.println('\n');
      counter = 0;
      valid_freq = update_freq();
      decide_song();
      //Serial.println(term);
      //Serial.println("Now Playing:");Serial.println(decide_song());Serial.println(" ");
      //Serial.println("np");Serial.println(now_playing);Serial.println('\n');
      //Serial.println(identifiers[5]);
      if(now_playing==0){
        Serial.println("0.mp3");
      }else{
      Serial.println(identifiers[now_playing]);
      }
      /*
      uart.write('p');uart.write('l');uart.write('a');uart.write('y');
      for(int i=0;i<strlen(identifiers[now_playing]);i++){
          uart.write(identifiers[now_playing][i]);
      }
      */
    }
   steps = 0;
  }
  delay(200); //slow down the serial display to be able to read easier
} 