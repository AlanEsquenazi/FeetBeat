#include<bits/stdc++.h> //includes necessary libraries
#include<chrono>
#include "SerialPort.h"
//#include "SerialPort.h"
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
char *port_name = "\\\\.\\COM10";
double prev_read=0, curr_read=0;
//String for incoming data
char incomingData[MAX_DATA_LENGTH];
int how_many_steps = 0;
double curr_freq=0;
int elapsedtime;
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
 //char *port_name = "\\\\.\\COM";
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
            cout<<(*it).second<<endl;
            return;
        }
        best_choice++;
    }
    //all songs are in the 20 last_played
    cout<<(*(last_played.begin()+best_choice))<<endl;
    last_played.erase(last_played.begin()+best_choice);
    last_played.pb(range_tester);
    //here, write song to file
    return;
}
int main(){
    //here, open doc with frequencies
    //the frequency used when choosing a new song will be the average of the
    //ten last frequencies
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
    SerialPort arduino(port_name);
  if (arduino.isConnected()) cout << "Connection Established" << endl;
  else cout << "ERROR, check port name";
  while (arduino.isConnected()){
    auto start = std::chrono::steady_clock::now();
    //Check if data has been read or not
    //int how_many_steps = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
    //cout<<"passos"<<how_many_steps<<endl;
    int curr_read = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
    cout<<"inc_dat"<<incomingData;
    if(incomingData[0]=='1')how_many_steps++;
    //cout<<"olhaso"<<arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
    //curr_read = curr_read-"0";
    //puts(incomingData);
    //cout<<"inc 0"<<incomingData[0]<<endl;
    int slow;
    std::cin>>slow;
    //curr_read = incomingData[0]-'0';
    //cout<<"0men0"<<'0'-'0'<<endl;
    //cout<<"putting"<<endl;
    //puts(incomingData);
    cout<<endl;
    how_many_steps+=curr_read;
    //cout<<"currread"<<curr_read<<endl;
    //prints out data
    /*
    if(curr_read!=prev_read){
      cout<<"diff"<<curr_read<<" "<<prev_read<<endl;
    }else{
      cout<<"same"<<curr_read<<" "<<prev_read<<endl;
    }
    prev_read=curr_read;
    //wait a bit
    */
   auto end = std::chrono::steady_clock::now();
   //cout<<"start"<<std::chrono::duration_cast<std::chrono::milliseconds>(start).count()<<endl;
   //cout<<"end"<<std::chrono::duration_cast<std::chrono::milliseconds>(end).count()<<endl;
   elapsedtime +=(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
   cout<<"elt132 "<<elapsedtime<<endl;
   Sleep(10);
   if(elapsedtime>=1000){
     cout<<"elt"<<elapsedtime<<endl;
     double for_freq = how_many_steps;
     curr_freq = (for_freq/(elapsedtime/1000))*60;
     how_many_steps = 0;
     cout<<"bpm"<<curr_freq<<endl;
     elapsedtime=0;
     bool ignore = false;
	  double curr_freq = 10;
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
}