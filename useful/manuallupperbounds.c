#include<stdio.h>
int test_array[10] = {1,2,3,4,5,6,7,8,9,10};
int lower_bound(int low, int high, int value){
    if(value<=test_array[0]){
        return 0;
    }if(value>=test_array[9]) return 9;
    int middle = (low+high)/2;
    if(test_array[middle]<=value && test_array[middle+1]>value){
        return middle;
    }else if(test_array[middle+1]<=value){
        lower_bound(middle, high, value);
    }else{
        lower_bound(low, middle, value);
    }
}
int upper_bound(int low, int high, int value){
    int middle = (low+high)/2;
    if(value>=test_array[9]){
        //printf("%d %d %d",100, value, test_array[10]);
        return 9;
    }
    if(value<=test_array[0]) return 0;
    if(test_array[middle]>value && test_array[middle-1]<=value){
        //printf("%d %d", 1000, middle);
        return middle;
    }else if(test_array[middle+1]<=value){
        //printf("%d %d", 763, middle);
        upper_bound(middle, high, value);
    }else{
        //printf("%d %d %d", 12567, middle, 999);
        upper_bound(low, middle, value);
    }
}
int main(){
    int f;
    scanf("%d",&f);
    printf("%d %d",lower_bound(0,10,f), upper_bound(0,10,f));
}