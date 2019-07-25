#include<iostream>
using namespace std;
double bpms[10] = {1,2,3,4,5,6,7,8,9,10};
int lower_bound1(int low, int high, int value){
    int middle = (low+high)/2;
    //cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<endl;
    if(value<=bpms[0]){
        return 0;
    }if(value>=bpms[9]) return 9;
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
    if(value>=bpms[9]){
        //printf("%d %d %d",100, value, bpms[10]);
        return 9;
    }
    if(value<bpms[0]) return 0;
    if(bpms[middle]>value && bpms[middle-1]<=value){
        cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"r"<<endl;
        //printf("%d %d", 1000, middle);
        return middle;
    }else if(bpms[middle-1]<=value){
        cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"right"<<endl;
        //printf("%d %d", 763, middle);
        upper_bound1(middle, high, value);
    }else{
        cout<<"low"<<low<<"high"<<high<<"low"<<"mid"<<middle<<"left"<<endl;
        //printf("%d %d %d", 12567, middle, 999);
        upper_bound1(low, middle, value);
    }
}
int main(){
    //double f= 3;
    for(int i=0;i<10;i++){
        cout<<"i="<<i<<"l"<<lower_bound1(0,10,i)<<"u"<<upper_bound1(0,10,i)<<endl;
    }
    //scanf("%d",&f);
    //cout<<lower_bound1(0,10,f)<<" "<<upper_bound1(1,10,f);
    //printf("%d %d",lower_bound(0,10,f), upper_bound(0,10,f));
}