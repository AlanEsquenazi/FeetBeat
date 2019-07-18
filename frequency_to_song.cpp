#include<bits/stdc++.h> //includes necessary libraries
using namespace std; //defines where the 
#define pds pair<double, string>
#define mp(a,b) make_pair(a,b)
#define all(a) a.begin(), a.end()
set <pds> song_list;
double delta = 5;
string range_tester = "aaa";
int my = 0;
vector <string> last_played = {"00","00","00","00","00","00","00","00","00","00","00","00",
"00","00","00","00","00","00","00","00"};
double step_freq;
/*
TODO:
-read frequency from file
-pretty much all file manipulation
-write chosen song to file
-read user's song list from file
-figure out how to get a song's spotify ID
 */
void decide_song(double frequency){
    double low = frequency-delta;
    double high = frequency+delta;
    auto interval_begin = lower_bound(all(song_list),mp(low, range_tester));
    auto interval_end = upper_bound(all(song_list),mp(high, range_tester));
    int best_choice = 0;
    for(auto it = interval_begin;it != interval_end;it++){
        if(find(all(last_played),((*it).second))!=last_played.end()){
            last_played.erase(last_played.begin());
            last_played.push_back((*it).second);
            best_choice++;
            //here, write song to file
            return;
        }
    }
    last_played.erase(last_played.begin()+best_choice);
    //here, write song to file
    return;
}
int main(){
    decide_song(step_freq);
}