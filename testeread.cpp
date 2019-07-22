//This code snippet will help you to read data from arduino

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<chrono>
#include "SerialPort.h"

using std::cout;
using std::endl;
/*Portname must contain these backslashes, and remember to
replace the following com port*/
char *port_name = "\\\\.\\COM10";
double prev_read=0, curr_read=0;
//String for incoming data
char incomingData[MAX_DATA_LENGTH];
int how_many_steps = 0;
double curr_freq=0;
int elapsedtime;
int main()
{
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
   }
  }
}