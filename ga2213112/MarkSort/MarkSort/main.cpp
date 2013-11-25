/* 
 * File:   main.cpp
 * Author: Guillermo Acuna
 * Created on July 18, 2012, 10:32 AM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

void fillArray(int [],int);
void printArray(int [],int,int);
void findMin(int [],int,int);
void swap(int &,int &);
void mSort(int [],int);

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare the array
    const int SIZE=100;
    int array[SIZE];
    //Fill the array
    fillArray(array,SIZE);
    //Print the array
    printArray(array,SIZE,10);
    //Sort the array
    mSort(array,SIZE);
    //Print the array
    printArray(array,SIZE,10);
    //Exit stage right
    return 0;
}

void mSort(int array[],int size){
    for(int i=0;i<size-1;i++){
        findMin(array,size,i);
    }
}

void swap(int &a,int &b){
    a=a^b;
    b=a^b;
    a=a^b;
}

void findMin(int array[],int size,int pos){
    for(int i=pos+1;i<size;i++){
        if(array[pos]>array[i]){
            //Swap the position at this point
            swap(array[pos],array[i]);
        }
    }
}

void fillArray(int array[],int size){
    for(int i=0;i<size;i++){
        array[i]=rand()%90+10;
    }
}

void printArray(int array[],int size,int perLine){
    cout<<endl;
    for(int i=0;i<size;i++){
        cout<<array[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
}

