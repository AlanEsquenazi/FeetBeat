#include<bits/stdc++.h>
using namespace std;
#define pds pair<double, string>
#define mp(a,b) make_pair(a,b)
#define all(a) a.begin(), a.end()
set <pds> song_list;
double delta = 5;
int my = 0;
vector <string> last_played = ("00", 20);
double step_freq;
/*
TODO:
-read frequency from file
-pretty much all file manipulation
 */
void decide_song(double frequency){
    double low = frequency-delta;
    double high = frequency+delta;
    auto interval_begin = lower_bound(all(song_list),mp(low, 'a'));
    auto interval_end = upper_bound(all(song_list),mp(high, 'a'));
    int best_choice = 0;
    for(auto it = interval_begin;it != interval_end;it++){
        if(last_played.find((*it))!=last_played.end()){
            last_played.pop_front();
            last_played.push_back(*it);
            best_choice++;
            //here, write song to file
            return;
        }
    }
    last_played.erase(best_choice);
    //here, write song to file
    return;
}
int main(){
    decide_song(step_freq);
}