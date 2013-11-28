/* 
 * File:   main.cpp
 * Author: Steven Piepenhagen
 * Purpose: CH6 HOMEWORK ARRAYS
 * 
 * Created on October 14, 2013, 1:00 PM
 */

//libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
//global constants

//function prototypes
void Menu();
int getN();
void def(int);
void problem0();
void problem1();
void problem2();
void problem3();
void problem4();
void problem5();
void problem6();
void problem7();
void problem8();
void problem9();
//problem function prototypes below
//CASE 0
float getLarg(float,float);
float getSmal(float,float);
//CASE 1
float getLarg(float,float,int, int&);
float getSmal(float,float,int,int&);
string getMonth(int);
//CASE 2
int gtSlsa(string[] ,int[] ,int , const int);
int gtHigh(int[],int,int);
int gtLow(int[],int,int);
//CASE 3
//none
//CASE 4
void chkAll(float[],int[],float[],float[],const int TOT);
void dispAll(int[],float[],const int TOT);
//CASE 5
int getTest (char [],char [],const int,int);
void psOrFl(int,const int);
//CASE 6
void getName(string[],const int);
//CASE 7
void genLott(int [],int);
void getLot(int [],int);
void matchNm(int [],int [],int, int&);
void winner(int,int);
//CASE 8
void check (int[],const int,int);
//CASE 9
void lottery(int[],const int,int);
//execution
int main(int argv,char *argc[]){
	int inN;
        do{
         Menu();
         inN=getN();
         switch(inN){
          case 0:    problem0();break;
          case 1:    problem1();break;
          case 2:    problem2();break;
          case 3:    problem3();break;
          case 4:    problem4();break;
          case 5:    problem5();break;
          case 6:    problem6();break;
          case 7:    problem7();break;
          case 8:    problem8();break;
          case 9:    problem9();break;

          default:   def(inN);}
        }while(inN>=0&&inN<=9);
        return 1;
}
    void Menu(){
           cout<<"Type 0 for Gaddis chapter 7 problem 1"<<endl; 
           cout<<"Type 1 for Gaddis chapter 7 problem 2"<<endl;
           cout<<"Type 2 for Gaddis chapter 7 problem 3"<<endl;
           cout<<"Type 3 for Gaddis chapter 7 problem 4"<<endl;
           cout<<"Type 4 for Gaddis chapter 7 problem 8"<<endl;
           cout<<"Type 5 for Gaddis chapter 7 problem 9"<<endl;
           cout<<"Type 6 for Gaddis chapter 7 problem 11"<<endl;
           cout<<"Type 7 for Gaddis chapter 7 problem 13"<<endl; 
           cout<<"Type 8 for Gaddis chapter 8 problem 1"<<endl; 
           cout<<"Type 9 for Gaddis chapter 8 problem 2"<<endl; 
           cout<<"Type anything else to exit \n"<<endl;
    }
    int getN(){
           int inN;
		   cin>>inN;
           return inN;
    }
//Gaddis_7ed_ch7_pr1
    void problem0(){
        cout<<"In Gaddis_7ed_ch7_pr1"<<endl<<endl;
           
        const int   NUM_ENT = 10;//use array to get ten values
        float       number[NUM_ENT];//use floats to enter the number
        int         large=0,//use to get the largest number
                    small=32000;//use to get the smallest number
        
        //get input and explain the program
        cout<<"Enter 10 values and I will tell you the largest and smallest"<<endl;
        //use for loop to get all inputs
        for (int count=1; count<=10;count++){
            cin>>number[count];
            //use function to get the largest and smallest numbers
            large=getLarg(number[count],large);
            small=getSmal(number[count],small);
        }
        //display the largest and smallest
        cout<<"The largest is "<<large<<endl;  
        cout<<"The smallest is "<<small<<endl;  
        }
//Gaddis_7ed_ch7_pr2
    void problem1(){
           cout<<"In Gaddis_7ed_ch7_pr2"<<endl<<endl;
        const int   MONTHS = 12;//use array to get twelve values
        float       month[MONTHS];//use floats to enter the rainfall
        float       largest=0,//use to get the largest amount of rainfall
                    small=32000,//use to get the smallest amount of rainfall
                    total=0,//total rainfall
                    average=0;//use to get the smallest number
        int     x,//smallest
                y, 
                z;//largest

        //get input and explain the program
        cout<<"Enter the average rainfall for each month and "
                "this will calculate the average rainfall "<<endl;
        //use for loop to get all inputs
        for (int count=0; count<12;count++){
            do{
                cin>>month[count];
            }while (month[count]<0);   
            total+=(month[count]);
            y = count + 1;
            largest=getLarg(month[count],largest, y, x);
            small=getSmal(month[count],small,y,z);
        }
        average=total/12;    
        cout<<fixed<<showpoint<<setprecision(2);
        //display the largest,smallest,total and average
        cout<<"The largest is "<<getMonth(x)<<" with "<<largest<<endl;     
        cout<<"The smallest is "<<getMonth(z)<<" with "<<small<<endl;   
        cout<<"The total rainfall for the year is "<<total<<endl;   
        cout<<"The average rainfall for the year is "<<average<<endl;
        
    }
//Gaddis_7ed_ch7_pr3
    void problem2(){
           cout<<"In Gaddis_7ed_ch7_pr3"<<endl<<endl;
           
        //input output variables go here
        const int TYPES=5;
        string      salsa[TYPES]={"Mild  ","Medium","Sweet ","Hot   ","Zesty "};
        int         sold[TYPES],
                    total=0,
                    high=0,
                    low=0;
    
        //get sales input for each salsa type also get total in process
        total=gtSlsa(salsa,sold,total,TYPES);   
        cout<<"Salsa type"<<setw(25)<<"Quantity sold"<<endl;
        for (int b=0;b<TYPES;b++){
            cout<<salsa[b]<<setw(20)<<sold[b]<<endl;
        }
        high=gtHigh(sold,TYPES,high);
        low=gtLow(sold,TYPES,low);
        cout<<""<<endl;
        cout<<"Salsa with the highest amount sold was "<<salsa[high]<<endl;
        cout<<"Salsa with the lowest amount sold was "<<salsa[low]<<endl;
        cout<<"Total amount of salsa sold is "<<total<<" units"<<endl;
    }
//Gaddis_7ed_ch7_pr4
    void problem3(){
           cout<<"In Gaddis_7ed_ch7_pr4"<<endl<<endl;
           
        const int   MONKEY=3, DAY=7;//use array to get twelve values
        int         nameOf[MONKEY][DAY];// 3x7 array for monkey and food values
        int         average[DAY],//days of the week numbered 1-7
                    least=1000000,// least amount of food eaten by a monkey
                    most=0;//most amount of food eaten by a single monkey

        //get input and explain the program
        cout<<"This will calculate the total amount of food eaten by the three "<<endl;
        cout<<"monkeys and also tell which is eating the most and least"<<endl;
    
        //use for loop to get all inputs
        for (int a=0; a<MONKEY;a++){
                nameOf[a];
                cout<<"For monkey number "<<a+1<<endl;
                //nested loop for nested array
                for (int b=0; b<DAY;b++){
                    do{
                        cout<<"Enter amount of food eaten for day "<<b+1<<" ";
                        cin>>nameOf[a][b];
                    }while(nameOf[a][b]<0);
                    //use if statements to calculate for the most and least
                    if (nameOf[a][b]>most){
                        most=nameOf[a][b];
                    }
                    if (nameOf[a][b]<least){
                        least=nameOf[a][b];
                    }
                }
        }
        //display daily averages with table
        for (int c=0;c<DAY;c++){
            average[c]=(nameOf[0][c]+nameOf[1][c]+nameOf[2][c])/(MONKEY);
            cout<<"The average for day "<<c+1<<" is "<<average[c]<<endl;
        }
        //display most and least values
        cout<<"The most food eaten by a single monkey in a day is "<<most<<endl;
        cout<<"The least food eaten by a single monkey in a day is "<<least<<endl; 
        cout<<""<<endl;
    }
//Gaddis_7ed_ch7_pr8
    void problem4(){
           cout<<"In Gaddis_7ed_ch7_pr8"<<endl<<endl;
               //input output variables
           const int TOT=7;//total employees to calculate for
           int       empid[TOT]={5658845,4520125,7895122,8777541,
                            8451277,1302850,7580489};//employee id's
           float     payrate[TOT],//pay rate
                     hours[TOT],//hours worked
                     wages[TOT];// gross wages         
    
           //display purpose
           cout<<"This is a way to check gross wages just enter "
                   "hours worked and pay rate for each employee #"<<endl;
           //Get user input and calculate
           chkAll(hours,empid,payrate,wages,TOT);
           //display all calculations
           dispAll(empid,wages,TOT); 
    }
//Gaddis_7ed_ch7_pr9
    void problem5(){
           cout<<"In Gaddis_7ed_ch7_pr9"<<endl<<endl;
           //input output variables
           const int TOTAL=20;
           char dmvKey[TOTAL]={'B','D','A','A','C','A','B','A','C','D',
                                'B','C','D','A','D','C','C','B','D','A'},
                   test[TOTAL];   
           int  count=0;
           //display purpose
           cout<<"This is a way to check for a passing score on a DMV test"<<endl;
           
           //Get user input and compare
           count=getTest(test,dmvKey,TOTAL,count);
           psOrFl(count,TOTAL);
    }
//Gaddis_7ed_ch7_pr11
    void problem6(){
           cout<<"In Gaddis_7ed_ch7_pr11"<<endl<<endl;
    
           //input output variables
           const int STUDENT=5,TEST=4;
           string name[STUDENT];
           int tstGrde[STUDENT][TEST],
                   average[STUDENT];
           char grade[STUDENT];
    
           getName(name,STUDENT);
           for(int b=0; b<STUDENT;b++){
               cout<<"Enter the score "<<name[b]<<" received on each test"<<endl;
               average[b]=0;
               for (int c=0;c<TEST;c++){
                   do{
                       cout<<"#"<<c+1<<"  :";
                       //get test grades
                       cin>>tstGrde[b][c];
                   }while(tstGrde[b][c]>100 || tstGrde[b][c]<0);
                   //add total of grades
                   average[b]+=tstGrde[b][c];
               }
               //calculate the average
               average[b]/=TEST;
           }
           //use for loop to display results
           for(int d=0;d<=STUDENT;d++){    
               cout<<"The average for "<<name[d]<<" is "<<average[d]<<"% "
                       " their letter grade is a(n)"; 
               if (average[d]>=90){
                   cout<<" A"<<endl;
               }
               else if (average[d]<90 && average[d]>=80){
                   cout<<" B"<<endl;
               }
               else if (average[d]<80 && average[d]>=70){
                   cout<<" C"<<endl;
               }
               else if (average[d]<70 && average[d]>=60){
                   cout<<" D"<<endl;
               }
               else {
                   cout<<" F"<<endl;
               }
           }
    }
//Gaddis_7ed_ch7_pr13
     void problem7(){
           cout<<"In Gaddis_7ed_ch7_pr13"<<endl<<endl;
           
           //input output variables here
           const int   AMOUNT=5; //amount of winning numbers
           int         lottery[AMOUNT], //winning lottery number array
                       ticket[AMOUNT], //user picks
                       matches=0; //used to find how many matches/
           //initialize the random number generator
           unsigned seed = time(0);
           srand(seed);
           //get lottery numbers from user
           getLot(ticket,AMOUNT);
           //generate winning lottery numbers
           genLott(lottery,AMOUNT);
           //check for matches
           matchNm(ticket,lottery,AMOUNT,matches);
           //display win or lose results
           winner(AMOUNT,matches);
     }
//Gaddis_7ed_ch8_pr1
    void problem8(){
           cout<<"In Gaddis_7ed_ch8_pr1"<<endl<<endl;
           
           //input output variables       
           const int SIZE=18;
           //int list is all numbers which are valid
           int list[SIZE]={5658845,4520125,7895122,8777541,8451277,1302850,8080152,
                        4562555,5552012, 5050552,7825877,1250255,1005231,
                        6545231,3852085,7576651,7881200,4581002};
           int getNum=0; // get user input for account
           //display purpose and get input to check for validation
           cout<<"Please enter your account number:";
           cin>>getNum;
           //check for number to be equal to a number in the string
           check(list,SIZE,getNum);  
    }
//Gaddis_7ed_ch8_pr2
    void problem9(){
        cout<<"In Gaddis_7ed_ch8_pr2"<<endl<<endl;
        //input output variables       
        const int NUMTIX=10;
        //int list is all numbers which are valid
        int tickets[NUMTIX]={13579,26791,26792,33445,55555,62483,
                        77777,79422,85647,93121};
        int winNum=0; // get user input for winning number
        
        //display purpose and get input to check for validation
        do{   
            cout<<"Please enter the winning 5-digit lottery number and this "<<endl;
            cout<<"program will let you know if you won"<<endl;
            cin>>winNum;
        }while (winNum>99999 || winNum<10000);
        //check for number to be equal to a number in the string
        lottery(tickets,NUMTIX,winNum);
    }
    void def(int inN){
        cout<<"You typed "<<inN<<" to exit the program"<<endl;
    }
    
//_________________ASSIGNMENT FUNCTIONS BELOW___________________________________
//--------------------------CASE 0----------------------------------------------
    float getLarg(float check,float large){
        if (check>large){
            return (check);
        }
        else{
            return (large);
        }
    }
    float getSmal(float check,float small){
        if (check<small){
            return (check);
        }
        else{
            return (small);
        }
    }
//------------------------------------------------------------------------------
   
    
    
//--------------------------CASE 1----------------------------------------------
    float getLarg(float check,float large, int spot, int& spot2){
        if (check>large){
            spot2=spot;
            return (check);
        }
        else{
            return (large);
        }
    }
    float getSmal(float check,float small, int spot, int& spot2){
        if (check<small){
            spot2=spot;
            return (check);
        }
        else{
            return (small);
        }
    }  
    string getMonth(int x){
        switch(x){
            case 1:
                return "January";
                break;
            case 2:
                return "February";
                break;
            case 3:
                return "March";
                break;
            case 4:
                return "April";
                break;
            case 5:
                return "May";
                break;
            case 6:
                return "June";
                break;
            case 7:
                return "July";
                break;
            case 8:
                return "August";
                break;
            case 9:
                return "September";
                break;
            case 10:
                return "October";
                break;
            case 11:
                return "November";
                break;
            case 12:
                return "December";
                break;     
        }
    }
//------------------------------------------------------------------------------
    
    
    
    
//--------------------------CASE 2----------------------------------------------  
    int gtSlsa(string salsa[],int sold[],int total,const int TYPES){ 
        for (int a=0;a<TYPES;a++){
            do{
                cout<<"Please enter total jars sold last month for the "
                        "salsa type: "<<salsa[a]<<endl;
                cin>>sold[a];
            }while(sold[a]<0);
            total+=sold[a];
        }
        return (total);
    }
    int gtHigh(int sold[],const int TYPES,int high){
        for (int b=0;b<TYPES;b++){
            if (sold[b]>sold[high]){
                high=b;        
            }
        }return (high);
    }
    int gtLow(int sold[],const int TYPES,int low){
        for (int b=0;b<TYPES;b++){
            if (sold[b]<sold[low]){
                low=b;        
            }
        }return (low);
    }
//------------------------------------------------------------------------------
    
    
    
    
//--------------------------CASE 3----------------------------------------------
    //none
//------------------------------------------------------------------------------
    
    
    
    
//--------------------------CASE 4----------------------------------------------
    void chkAll(float hours[],int empid[],float payrate[],float wages[],const int TOT){
        for(int x=0;x<TOT;x++){
            //get employees information
            do{
                cout<<"Please enter employee #'s "<<empid[x]<<" payrate"<<endl;
                cin>>payrate[x];
            }while(payrate[x]<6);
            do{
                cout<<"hours worked: "<<endl;
                cin>>hours[x];
            }while(hours[x]<6);
            //set precision
            cout<<fixed<<showpoint<<setprecision(2);
            //calculate gross pay
            wages[x]=payrate[x]*hours[x];
        }
    }
    void dispAll(int empid[],float wages[],const int TOT){
        for(int y=0;y<TOT;y++){
            cout<<"For Employee # "<<empid[y]<<" gross wages are $"<<wages[y]<<endl;
        }
    }
//------------------------------------------------------------------------------
    
    
    
    
    
//--------------------------CASE 5----------------------------------------------
    int getTest(char test[],char dmvKey[],const int TOTAL,int count){
        for(int x=0;x<TOTAL;x++){
            do{
                cout<<"Please enter your answer for # "<<x+1<<endl;
                cin>>test[x];        
            }while(test[x] !='A' && test[x] !='B' && test[x] !='C' && test[x] !='D');
            if (test[x]==dmvKey[x]){
                count+=1;
            }
        }
        return (count);
    }
    void psOrFl(int count,const int TOTAL){
        cout<<"You answered "<<count<<" out of "<<TOTAL<<endl;
        if (count>14){
            cout<<"CONGRATULATIONS you passed your driving test"<<endl;
        }
        else {
            cout<<"Nope you failed the test"<<endl;
        }
    }
//------------------------------------------------------------------------------
    
    
    
    
    
//--------------------------CASE 6----------------------------------------------
    void getName(string name[],const int STUDENT){
        for(int a=0;a<STUDENT;a++){
            cout<<"Enter student number "<<a+1<<" name"<<endl;
            cin>>name[a];
        }
    }
//------------------------------------------------------------------------------
    
    
    
    
    
    
//--------------------------CASE 7----------------------------------------------
    void genLott(int lottery[],int AMOUNT){
        cout<<"The lottery numbers are "<<endl;
        for (int x=0;x<AMOUNT;x++){
            lottery[x]=1 + rand() % 9; //between 1-9
            //use do-while loop so there are no duplicates
            do {
                lottery[x]=1 + rand() % 9;
            } while (lottery[x]==lottery[x-1] || lottery[x]==lottery[x-2] || 
                    lottery[x]==lottery[x-3] || lottery[x]==lottery[x-4] ||
                    lottery[x]==lottery[x-5]);
            //display winning numbers
            cout<<lottery[x]<<" ";
        }
    }
    void getLot(int ticket[],int AMOUNT){
        //display purpose and get information
        cout<<"Enter your lottery numbers (between 1-9) and this program will "
                "let you know how many match, and if you won"<<endl;
        for (int y=0; y<AMOUNT;y++){
            do{
                cout<<"Enter lottery # "<<y+1<<endl;
                cin>>ticket[y];
            }while(ticket[y]>9 || ticket[y]<1);
        }
    }
    void matchNm(int ticket[],int lottery[],int AMOUNT, int& matches){
        int     lotnum=0,
                tunum=0;
        for (int z=0; z<AMOUNT;z++){
            tunum=ticket[z];
            for (int a=0; a<AMOUNT;a++){
                lotnum=lottery[a];
                if (tunum==lotnum){
                    matches+=1;
                } 
            }
        }
    }
    void winner(int AMOUNT,int matches){
        cout<<""<<endl;
        cout<<"The number of matches are "<<matches<<endl; 
        if (matches==AMOUNT){
            cout<<"You are the grand prize winner! CONGRATULATIONS!!!"<<endl;
        } 
        else{
            cout<<"so close..."<<endl;
        }
    }
//------------------------------------------------------------------------------
    
    
    
    
    
//--------------------------CASE 8----------------------------------------------
    void check (int list[],const int SIZE,int getN){
        //use for loop to step through the function
        for (int x=0;x<=(SIZE-1);x++){
            //if statement to check against the list
            if (list[x]==getN){
                cout<<"Welcome to your account"<<endl;
                //break from "for" loop if true
                return;
            }
        }
        //display error message if incorrect
        cout<<"Input does not match any account numbers on file"<<endl;   
    }
//------------------------------------------------------------------------------
    
    
    
    
    
//--------------------------CASE 9----------------------------------------------
    void lottery (int tickets[],const int NUMTIX,int winN){
        //use for loop to step through the function
        for (int x=0;x<=(NUMTIX-1);x++){
            //if statement to check against the list
            if (tickets[x]==winN){
                cout<<"Congratulations you WIN!!!!"<<endl;
                //break from "for" loop if true
                return;
            }
        }
        //display error message if incorrect
        cout<<"Nope, you didn't win this week"<<endl;   
    }

