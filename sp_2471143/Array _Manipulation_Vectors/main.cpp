/*
  Dr. Mark E. Lehr
 * revised by Steven Piepenhagen
  November 18th, 2013
*/

//Libraries
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

//No Global Constants

//Function Prototypes
vector<int> fillVec(vector <int>);
void prntVec(vector <int>,int);
void delVec(vector <int> ,const int);
void delVal(vector <int>,50,-1);


int main(int argc, char *argv[]){
    //Declare and initialize variables
    srand(static_cast<unsigned int>(time(0)));
    const int SIZE=200;
    vector<int> vect(SIZE);

    //Fill the Array
    vect=fillVec(vect);
    //Print the Array
    prntVec(vect,10);
    //Find and delete and replace
    int sizeOf=delVal(vect,50,-1);
    cout<<"Size of the array = "
        <<sizeOf<<endl;
//    delVec(vect,SIZE);
//    prntVec(vect,SIZE,10);
    
    return EXIT_SUCCESS;
}
/*void shift(int a[],int pos,int end,int value){
     //Delete the position
     for(int i=pos;i<end-1;i++){
             a[i]=a[i+1];
     }*/

/*void delVec(vector <int> a,const int x){
    for(int i=0;i<x;i++){
        if (a[i]==30){
            a.erase(i);
        }
    } 


}
*/
int  szOf(int a[],int n,int value){
     for(int i=0;i<n;i++){
          if(a[i]==value)return i;
     }
     return n;
}

void shift(int a[],int pos,int end,int value){
     //Delete the position
     for(int i=pos;i<end-1;i++){
             a[i]=a[i+1];
     }
     //Replace last position with empty value 
     a[end-1]=value;
}

int  find(int a[],int strt,int end,int value){
     //Try to find the value
     for(int i=strt;i<=end;i++){
             if(a[i]==value) return i;
     }
     //Return if not found
     return -1;
}






int  delVal(int a[],int n,int value,int vInsrt){
    //Find and delete
    int posFnd=0;
    do{ 
        posFnd=find(a,posFnd,n-1,value);
        if(posFnd>0)shift(a,posFnd,n,vInsrt);
    }while(posFnd>0);
    
    //Size of the array
    return szOf(a,n,vInsrt);
}

void prntVec(vector <int> a,int perLine){
     cout<<endl;
     for(int i=0;i<a.size();i++){
          cout<<a[i]<<" ";
          if(i%perLine==(perLine-1))cout<<endl;
     }
     cout<<endl;
}

//Randomly fill an array with 2
//digit numbers
vector<int> fillVec(vector<int> a){
     //Loop and fill the vector
     for(int i=0;i<a.size();i++){
         a[i]=rand()%90+10;
     }
     return a;
}     
