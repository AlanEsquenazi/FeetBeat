//Analog read pins for accelerometer
#include<iostream>
using namespace std;
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;
int prevX = 0;
int prevY = 0;
int prevZ = 0;
double steps = -1;
int counter = 0;
int now_playing = 0;
unsigned long StartTime;
bool going_up = false;
int bpms[100];
char *identifiers[100];
int durations[100];
int last_freqs[10];
char *last_played[20];
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
    for(int i=19;i>=0;i--){
        if(last_played[i]>="0"){
            return i;
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
    int where_lower=0, where_upper=10000;
    int how_many_songs = sizeof(bpms);
    for(int i=0;i<how_many_songs;i++){
        if(bpms[i]>=lower_bound){
            where_lower=i;
            break;
        }
    }
    for(int i=where_lower;i<how_many_songs;i++){
        if(bpms[i]<=upper_bound){
            where_upper=i;
            break;
        }
    }
    if(where_upper==10000){
        where_upper=(how_many_songs);
    }
    int best_choice =19;
    for(int i=lower_bound;i<upper_bound;i++){
        if(in_last_played(identifiers[i])==100000){
            update_last_played(identifiers[i]);
            return identifiers[i];
            now_playing = i;
        }else{
          if(in_last_played(identifiers[i])<=best_choice){
            now_playing=i;
          }
            best_choice = min(best_choice, in_last_played(identifiers[i]));
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
void update_flist(double curr_freq){
        for(int i=1;i<10;i++){
            last_freqs[i-1]=last_freqs[i];
        }
        last_freqs[9]=curr_freq;
}


int main(){
    cout<<"aswdefrghjk1"<<endl;
   bpms[0] = 60;
  identifiers[0] = "60 bpm-1";
  durations[0]=1;
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
int counter = 0;
while(1){
double ElapsedTime;
cout<<"aswdefrghjk"<<endl;
cout<<"steps";cin>>steps;cout<<endl<<"Elapsedtime";cin>>ElapsedTime;
double curr_freq = 60*steps/(ElapsedTime/1000);
counter++;
    update_flist(curr_freq);
    cout<<"flist"<<endl;
    for(int i=0;i<10;i++){
        cout<<last_freqs[i]<<endl;
    }
    if(counter>=durations[now_playing]){
        cout<<"entro";
      update_freq();
      cout<<"ok"<<endl;
      decide_song();
      cout<<"ok2"<<endl;
      //Serial.println("Now Playing:");Serial.println(identifiers[now_playing]);Serial.println('\n');
    }
    cout<<"val_freq"<<valid_freq;
  }
  //read the analog values from the accelerometer
  /*
  int zRead;
    cout<<"zread";cin>>zRead;
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
  */
  //Output read values to Serial monitor
  /*
  Serial.print(" | z: ");
  Serial.println(zRead); 
  Serial.println("Steps");Serial.println(steps);Serial.println('\n');
  Serial.println("np");Serial.println(now_playing);
  Serial.println("playing out");Serial.println(identifiers[9]);Serial.println("lasts for");Serial.println(durations[now_playing]);Serial.println('\n');
  */
 /*
 cout<<"np"<<now_playing<<"playing out"<<identifiers[now_playing]<<"lasts for"<<durations[now_playing];
  prevZ = zRead;
  unsigned long CurrentTime;
  cout<<"currt";cin>>CurrentTime;
  unsigned long ElapsedTime = CurrentTime - StartTime;
  //Serial.println("elt");Serial.println(ElapsedTime);Serial.println('\n');Serial.println("stt");Serial.println(StartTime);Serial.println('\n');
  cout<<"elt"<<ElapsedTime<<"stt"<<StartTime<<endl;
  if(ElapsedTime>1000){
    counter++;
    //Serial.println("counter");Serial.println(counter);Serial.println('\n');
    StartTime=ElapsedTime;
    double curr_freq = steps/(ElapsedTime/1000);
    update_flist(check_full(),curr_freq);
    if(counter>=now_last){
      update_freq();
      decide_song();
      //Serial.println("Now Playing:");Serial.println(identifiers[now_playing]);Serial.println('\n');
    }
  }
  steps = 0;}
  */
  //delay(200); //slow down the serial display to be able to read easier
} 