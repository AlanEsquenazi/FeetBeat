#include <avr/io.h>       /* Define pins & ports */
#include <util/delay.h>   /* built-in time function */
#include<bits/stdc++.h> //includes necessary libraries
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
vector <double> frequencies;//I dont think i need a vector for this
//the actual frequencies dont matter, just their average
/*
If i receive 0 (low) as a freq, can i recognize that as a break and just ignore?
I think I could
 */
/*
TODO:
-read frequency from file
-pretty much all file manipulation
-write chosen song to file
-read user's song list from file
-figure out how to get a song's spotify ID
-figure out how to connect to the bluetotooth board on the arduino
-figure out if i need an extra file to communicate with the Arduino
-
 */
//function to choose song
void decide_song(double frequency){
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
            return;
        }
        best_choice++;
    }
    //all songs are in the 20 last_played
    last_played.erase(last_played.begin()+best_choice);
    last_played.pb(range_tester);
    //here, write song to file
    return;
}
int main(){
    //here, open doc with frequencies
    //the frequency used when choosing a new song will be the average of the
    //ten last frequencies
    while(1){
        //TODO: learn how to delay in c++ - 
        //can use sleep(5), sleep_for(nanoseconds(5000000))
        /*
        2 possible logics
        1-delay and always read
        2-read upon updating (TODO - learn how to do this)
         */
        //pop_front of freq, push back new frequency
        //calculate new average, save that to step_freq
        //choose a new song with the new step_freq
        //write the new song to the file

    }
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

}