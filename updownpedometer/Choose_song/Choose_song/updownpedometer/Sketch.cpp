/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */
#include <util/delay.h>   /* built-in time function */
//#include<bits/stdc++.h> //includes necessary libraries
//#include<iostream.h>
//#include<set.h>
#include<vector>
#include<iomanip>
using namespace std; //defines where the functions used are
#define pds pair<double, string> //for faster typing
#define mp(a,b) make_pair(a,b)
#define all(a) a.begin(), a.end()
#define pb(a) push_back(a)
set <pds> song_list; //set (red-black tree- for our purposes, what matters is that it is sorted) holding song's bpm and identifiers
double delta = 5; //adding a delta to the step frequency, not a good idea to compare double wo delta (and also creating an interval makes it more likely to exist a song in that interval)
string range_tester = "aaa";
vector <string> last_played = {"00","00","00","00","00","00","00","00","00","00","00","00",
"00","00","00","00","00","00","00","00"}; //vector holding 20 last played songs; starts with dummies
double step_freq;
deque<double> last_freqs;
//function to choose song
string decide_song(double frequency){
	double low = frequency-delta; //lower range of the interval
	double high = frequency+delta; //higher range
	//lower and upper bound - return pointer to elements just below and
	//just above the value passed
	auto interval_begin = lower_bound(all(song_list),mp(low, range_tester));
	auto interval_end = upper_bound(all(song_list),mp(high, range_tester));
	//best_choice - song in the interval that was played
	//the longest time ago. in case all songs in the interval
	//are in the 20 last played, this will be played
	int best_choice = 0;
	//iterate through the interval
	for(auto it = interval_begin;it != interval_end;it++){
		if(find(all(last_played),((*it).second))!=last_played.end()){
			//found a song not among 20 last played!
			last_played.erase(last_played.begin());
			last_played.pb((*it).second);
			//here, write song to file
			return((*it).second);
			return;
		}
		best_choice++;
	}
	//all songs are in the 20 last_played
	last_played.erase(last_played.begin()+best_choice);
	last_played.pb(range_tester);
	return((*it).second);
	//here, write song to file
	return;
}
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

//Analog read pins for accelerometer
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;
int prevX = 0;
int prevY = 0;
int prevZ = 0;
int steps = 0;
unsigned long StartTime = millis();
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
  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - StartTime;
  if(ElapsedTime>1000){
	  StartTime=ElapsedTime;
	  bool ignore = false;
	  double curr_freq = steps/(ElapsedTime/1000);
	  if(curr_freq<10){
		  ignore = true;
	  }
		if(last_freqs.size()<10 && !ignore){
			step_freq += curr_freq/10;
			last_freqs.push_back(curr_freq); 
		}else if(!ignore){
			step_freq += curr_freq/10;
			step_freq-=last_freqs.front()/10;
			last_freqs.pop_front();
			last_freqs.push_back(curr_freq);
		}
  }
  //here, wait for a flag from the phone requesting a song
  //call decide song, return the string to the phone
  delay(200); //slow down the serial display to be able to read easier
}

