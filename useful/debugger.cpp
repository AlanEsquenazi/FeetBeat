//Analog read pins for accelerometer
//const int xPin = 0;
//const int yPin = 1;
//#include <SPI.h>
//#include "Adafruit_BLE_UART.h"

//#define ADAFRUITBLE_REQ 10
//#define ADAFRUITBLE_RDY 2
//#define ADAFRUITBLE_RST 9

//Adafruit_BLE_UART uart = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
//const int zPin = 2;
//int prevX = 0;
//int prevY = 0;
//int prevZ = 0;
#include<iostream>
using namespace std;
double steps = -1;
double counter = 0;
int now_playing = 0, now_last = 30;
unsigned long StartTime = 0;
bool going_up = false;
int bpms[9];
char *identifiers[9];
int durations[9];
int last_freqs[10];
char *last_played[20];
double valid_freq = 0;
double delta = 10;
int where_in_songs(char* name){
    for(int i=0;i<sizeof(identifiers);i++){
        if(identifiers[i]==name){
            return i;
        }
    }
}
int check_full_played(){
    for(int i=19;i>=0;i--){
        if(last_played[i]=="0"){
            return i-1;
        } 
    }
    return 0;
}
int in_last_played(char* to_test){
    for(int i=0;i<19;i++){
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
        for(int i=1;i<19;i++){
            last_played[i-1]=last_played[i];
        }
        last_played[19]=to_play;
    }
}
char* decide_song(){
    double upper_bound = valid_freq+delta;
    double lower_bound = valid_freq-delta;
    cout<<"lb"<<lower_bound<<"up"<<upper_bound<<endl;
//    Serial.println("ub");Serial.println(upper_bound);Serial.println("lb");Serial.println(lower_bound);
    int where_lower=0, where_upper=10000;
    int how_many_songs = 8;
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
    if(upper_bound<(bpms[0]-delta)){
        cout<<"eh";
        where_upper=0;
        now_playing = 0;now_last=durations[0];
        update_last_played(identifiers[0]);
        return identifiers[0];
    }
    else if(where_upper==10000){
        cout<<"eh2";
        where_upper= how_many_songs;
    }
    //Serial.println("where_upper");Serial.println(where_upper);Serial.println('\n');
    int best_choice = 19;
    cout<<"wl"<<where_lower<<"wu"<<where_upper<<endl;
    for(int i=where_lower;i<=where_upper;i++){
        cout<<"looopando"<<endl;
        if(in_last_played(identifiers[i])==10000){
            update_last_played(identifiers[i]);
            now_playing = i;now_last=durations[i];
      //      Serial.println("i");Serial.println(i);Serial.println('\n');
      cout<<"retornou"<<i<<" "<<identifiers[i];
            return identifiers[i];
        }else{
            cout<<"caso2"<<endl;
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
double update_freq(){
    double vf = 0;
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
}
void update_flist(double curr_freq){
        for(int i=1;i<10;i++){
            last_freqs[i-1]=last_freqs[i];
        }
        last_freqs[9]=curr_freq;
}
int main(){bpms[0] = 60;
  identifiers[0] = "60 bpm-1";
  durations[0]=3;
  bpms[1] = 60;
  identifiers[1] = "60 bpm-2";
  durations[1]=40;
  bpms[2] = 60;
  identifiers[2] = "60 bpm-3";
  durations[2]=22;
  bpms[3] = 70;
  identifiers[3] = "70 bpm-1";
  durations[3]=35;
  bpms[4] = 80;
  identifiers[4] = "80 bpm-1";
  durations[4]=100;
  bpms[5] = 90;
  identifiers[5] = "90 bpm-1";
  durations[5]=30;
  bpms[6] = 93;
  identifiers[6] = "93 bpm-1";
  durations[6]=30;
  bpms[7] = 101;
  identifiers[7] = "101 bpm-1";
  durations[7]=120;
  bpms[8] = 110;
  identifiers[8] = "110 bpm-1";
  durations[8]=30;
  last_freqs[0]=0;last_freqs[1]=0;
last_freqs[2]=0;last_freqs[3]=0;last_freqs[4]=0;last_freqs[5]=0;last_freqs[6]=0;last_freqs[7]=0;last_freqs[8]=0;last_freqs[9]=0;
last_played[0]="0";last_played[1]="0";last_played[2]="0";last_played[3]="0";last_played[4]="0";last_played[5]="0";last_played[6]="0";last_played[7]=0;last_played[8]="0";last_played[9]="0";
last_played[10]="0";last_played[11]="0";last_played[12]="0";last_played[13]="0";last_played[14]="0";last_played[15]="0";last_played[16]="0";last_played[17]=0;last_played[18]="0";last_played[19]="0";

    cout<<bpms[0];
    for(int i=0;i<9;i++){
        cout<<"musica"<<bpms[i]<<' '<<identifiers[i]<<' '<<durations[i]<<endl;
    }
    valid_freq = 100;
    char* j = decide_song();
    cout<<j<<endl;
}