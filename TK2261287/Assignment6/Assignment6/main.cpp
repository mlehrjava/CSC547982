//
//  main.cpp
//  Assignment6
//
//  Created by TaeYoun Kim on 2013. 11. 27..
//  Copyright (c) 2013 TaeYoun Kim. All rights reserved.
//

//Libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>
#include <ctime>
using namespace std;

//Global Constants

//Function Prototypes
int Selection();
void Problem1();
void p1_Store(int []);
void p1_Find(int [], int &, int &);
void Problem2();
void p2_Store(double []);
void p2_Find(double [],string &, string &, double &, double &);
void Problem3();
void p3_Store(int [], string[]);
void p3_Result(int [], string[]);
void Problem4();
void p4_input(float [][7]);
void p4_result(float [][7]);
void Problem5();
void p5_input(string [],char [],double [][4]);
void Problem6();
void p6_input(int [],int [],double [],double []);
void Problem7();
void p7_input(string [],char [],double [][4]);
void Problem8();
void p8_input(int [],int []);
void Problem9();
void Problem10();
void p10_input(int [][5]);
string Numbering(int);
string Int2String(int);
string Double2String(double);
void Title(string);
bool AskExit(string);
void Exit();

//Execution Begins Here!!!
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variation
    int pNum;
    
    //Selection
    do{
        pNum=Selection();
        switch(pNum){
            case 1:    Problem1();break;
            case 2:    Problem2();break;
            case 3:    Problem3();break;
            case 4:    Problem4();break;
            case 5:    Problem5();break;
            case 6:    Problem6();break;
            case 7:    Problem7();break;
            case 8:    Problem8();break;
            case 9:    Problem9();break;
            case 10:    Problem10();break;
            default:   Exit();
        }
    }while(pNum!=0);
    
    return 0;//If midterm not perfect, return something other than 1
}


int Selection(){
    int i;
    cout<<"Please Select the Problem"<<endl;
    cout<<"---------------------------------"<<endl;
    cout<<"1.Largest/Smallest Array Values"<<endl;
    cout<<"2.Rainfall Statistics"<<endl;
    cout<<"3.Chips and Salsa"<<endl;
    cout<<"4.Monkey Business"<<endl;
    cout<<"5.Grade Book"<<endl;
    cout<<"6.Payroll"<<endl;
    cout<<"7.Grade Book Modification"<<endl;
    cout<<"8.Lottery Application"<<endl;
    cout<<"9.Charge Account Validation"<<endl;
    cout<<"10.Lottery Winners"<<endl;
    cout<<"To exit, enter any other number"<<endl;
    cin>>i;
    if(i<1||i>10){
        i=0;
    }
    return i;
}

void Problem1(){
    int number[10];
    int low,high;
    Title("Largest/Smallest Array Values");
    p1_Store(number);
    p1_Find(number,low,high);
    cout<<"--------------------\nThe Lowest Number is: "
    <<low<<"\nThe Highest Number is: "<<high<<endl;
    AskExit("Want to Exit?");
}

void p1_Store(int n[]){
    for(int i=0;i<10;i++){
        cout<<"Please Enter Any Number - "<<Numbering(i+1)<<" number is: ";
        cin>>n[i];
    }
}

void p1_Find(int n[],int &l,int &h){
    l=n[0];
    h=n[0];
    for(int i=0;i<10;i++){
        if(n[i]<=l)l=n[i];
        if(n[i]>=h)h=n[i];
    }
}

void Problem2(){
    double rainfall[12];
    double total=0,avg=0;
    string low="",high="";
    Title("Rainfall Statistics");
    p2_Store(rainfall);
    p2_Find(rainfall, low, high, total, avg);
    cout<<"--------------------\n"<<low<<endl<<high<<endl
    <<"The total rainfall for year is: "<<total<<"(mm)\n"
    <<"The average monthly rainfall is: "<<avg<<endl;
    AskExit("Want to Exit?");
}

void p2_Store(double n[]){
    for(int i=0;i<12;i++){
        for(bool b=false;b==false;){
            cout<<Numbering(i+1)<<" month's rainfall is(in mm): ";
            cin>>n[i];
            if(n[i]>=0){b=true;}
            else{cout<<"You Entered Negative Number!"<<endl;}
        }
    }
}

void p2_Find(double n[], string &l, string &h, double &t, double &a){
    double base=n[0];
    bool single=true;
    for(int i=0;i<12;i++){
        if(n[i]<=base){
            if(n[i]==base&&l.length()>0){
                l+=", ";
                l+=Numbering(i+1);
                single=false;
            }else{
                l=Numbering(i+1);
                single=true;
            }
            base=n[i];
        }
        t+=n[i];
        a+=n[i];
    }
    if(single==true){
        l+=" is the month of lowest rainfall(";
        l+=Double2String(base);
        l+="mm)";
    }else{
        l+=" are the months of lowest rainfall(";
        l+=Double2String(base);
        l+="mm)";
    }
    for(int i=0;i<12;i++){
        if(n[i]>=base){
            if(n[i]==base&&h.length()>0){
                h+=", ";
                h+=Numbering(i+1);
                single=false;
            }else{
                h=Numbering(i+1);
                single=true;
            }
            base=n[i];
        }
    }
    if(single==true){
        h+=" is the month of highest rainfall(";
        h+=Int2String(base);
        h+="mm)";
    }else{
        h+=" are the months of highest rainfall(";
        h+=Int2String(base);
        h+="mm)";
    }
    a=a/12;
}

void Problem3(){
    int SIZE = 5;
    string salsa[SIZE];
    int jars[SIZE];
    salsa[0]=string("mild");
    salsa[1]=string("medium");
    salsa[2]=string("sweet");
    salsa[3]=string("hot");
    salsa[4]=string("zesty");
    Title("Chips and Salsa");
    p3_Store(jars,salsa);
    p3_Result(jars,salsa);
    AskExit("Want to Exit?");
}

void p3_Store(int n[], string s[]){
    for(int i=0;i<5;i++){
        for(bool b=false;b==false;){
            cout<<"How many "<<s[i]<<" salsa you sold?: ";
            cin>>n[i];
            if(n[i]>=0){b=true;}
            else{cout<<"You Entered Negative Number!"<<endl;}
        }
    }
}
void p3_Result(int n[], string s[]){
    int base=n[0];
    string l="",h="";
    int t=0;
    bool single=true;
    for(int i=0;i<5;i++){
        cout<<s[i]<<" salsa sold: "<<n[i]<<endl;
        if(n[i]<=base){
            if(n[i]==base&&l.length()>0){
                l+=", ";
                l+=s[i];
                single=false;
            }else{
                l=s[i];
                single=true;
            }
            base=n[i];
        }
        t+=n[i];
    }
    if(single==true){
        l+=" is the lowest selling salsa :";
        l+=Int2String(base);
    }else{
        l+=" are the lowest selling salsas :";
        l+=Int2String(base);
    }
    for(int i=0;i<5;i++){
        if(n[i]>=base){
            if(n[i]==base&&h.length()>0){
                h+=", ";
                h+=s[i];
                single=false;
            }else{
                h=s[i];
                single=true;
            }
            base=n[i];
        }
    }
    if(single==true){
        h+=" is the highest selling salsa :";
        h+=Int2String(base);
    }else{
        h+=" are the highest selling salsas :";
        h+=Int2String(base);
    }
    cout<<"Total salsa sold: "<<t<<endl<<l<<endl<<h<<endl;
}

void Problem4(){
    float ary[3][7];
    Title("Monkey Business");
    p4_input(ary);
    p4_result(ary);
    AskExit("Want to Exit?");
}

void p4_input(float r[][7]){
    for(int i=0;i<7;i++){
        cout<<"---------\n"<<"| Day "<<i+1<<" |"<<"\n---------"<<endl;
        for(int k=0;k<3;k++){
            for(bool b=false;b==false;){
                cout<<"How many pounds of food does number "<<Numbering(k+1)<<" monkey ate?: ";
                cin>>r[k][i];
                if(r[k][i]>=0){b=true;}
                else{cout<<"You Entered Negative Number!"<<endl;}
            }
        }
    }
}

void p4_result(float n[][7]){
    float m[3];
    string l="";
    float t=0;
    for(int i=0;i<3;i++){
        m[i]=0;
        for(int k=0;k<7;k++){
            m[i]+=n[i][k];
        }
        t+=m[i];
    }
    cout<<"___________________________________________________________________"<<endl;
    t=t/7;
    cout<<"Total amount of pounds of food eaten by monkey family is: "<<t<<"(lbs)"<<endl;
    float base=m[0];
    for(int i=0;i<3;i++){
        if(m[i]<=base){
            if(m[i]==base&&l.length()>0){
                l+=", ";
                l+=Numbering(i+1);
            }else{
                l=Numbering(i+1);
            }
            base=m[i];
        }
    }
    cout<<"The lowest amount of food eaten by "<<l<<": "<<base<<"(lbs)"<<endl;
    l="";
    for(int i=0;i<3;i++){
        if(m[i]>=base){
            if(m[i]==base&&l.length()>0){
                l+=", ";
                l+=Numbering(i+1);
            }else{
                l=Numbering(i+1);
            }
            base=m[i];
        }
    }
    cout<<"The highest amount of food eaten by "<<l<<": "<<base<<"(lbs)"<<endl;
}

void Problem5(){
    string name[5];
    char grade[5];
    double score[5][4];
    Title("Grade Book");
    p5_input(name,grade,score);
    AskExit("Want to Exit?");
}

void p5_input(string n[],char g[],double s[][4]){
    double gd[5];
    for(int x=0;x<5;x++){
        cout<<"Enter the Student's name: ";
        cin>>n[x];
        Title(n[x]);
        gd[x]=0;
        for(int k=0;k<4;k++){
            for(bool b=false;b==false;){
                cout<<"Enter the "<<Numbering(k+1)<<" score of the test: ";
                cin>>s[x][k];
                if(s[x][k]>=0&&s[x][k]<=100){b=true;}
                else{cout<<"You Entered Incorrect Number!"<<endl;}
            }
            gd[x]+=s[x][k];
        }
        gd[x]/=4;
        if(gd[x]>=90)g[x]='A';
        else if(gd[x]>=80)g[x]='B';
        else if(gd[x]>=70)g[x]='C';
        else if(gd[x]>=60)g[x]='D';
        else {g[x]='F';}
        cout<<endl;
    }
    for(int i=0;i<5;i++){
        cout<<n[i]<<": "<<g[i]<<"("<<gd[i]<<"}"<<endl;
    }
}

void Problem6(){
    int empId[7]={5658845,4520125,7895122,8777541,8451277,1302850,7580489};
    int hours[7];
    double payRate[7];
    double wages[7];
    Title("Payroll");
    p6_input(empId,hours,payRate,wages);
    AskExit("Want to Exit?");
}

void p6_input(int id[],int h[],double p[],double w[]){
    string str;
    for(int x=0;x<7;x++){
        str="ID: ";
        str+=Int2String(id[x]);
        Title(str);
        for(bool b=false;b==false;){
            cout<<"Enter the hour employee worked: ";
            cin>>h[x];
            if(h[x]>=0){b=true;}
            else{cout<<"You Entered Negative Number!"<<endl;}
        }
        for(bool b=false;b==false;){
            cout<<"Enter the pay rate(higher than $6.00/hr: ";
            cin>>p[x];
            if(p[x]>=6.00){b=true;}
            else{cout<<"You Entered Incorrect Number!"<<endl;}
        }
        w[x]=h[x]*p[x];
        cout<<endl;
    }
    for(int i=0;i<5;i++){
        cout<<showpoint<<fixed<<setprecision(2);
        cout<<"ID) "<<id[i]<<" - gross wage: $"<<w[i]<<endl;
    }
}

void Problem7(){
    string name[5];
    char grade[5];
    double score[5][4];
    Title("Grade Book Modification");
    p7_input(name,grade,score);
    AskExit("Want to Exit?");
    
}

void p7_input(string n[],char g[],double s[][4]){
    double gd[5];
    double lowest=0;
    for(int x=0;x<5;x++){
        cout<<"Enter the Student's name: ";
        cin>>n[x];
        Title(n[x]);
        gd[x]=0;
        lowest=100;
        for(int k=0;k<4;k++){
            for(bool b=false;b==false;){
                cout<<"Enter the "<<Numbering(k+1)<<" score of the test: ";
                cin>>s[x][k];
                if(s[x][k]>=0&&s[x][k]<=100){b=true;}
                else{cout<<"You Entered Incorrect Number!"<<endl;}
            }
            if(s[x][k]<=lowest)lowest=s[x][k];
            gd[x]+=s[x][k];
        }
        gd[x]=(gd[x]-lowest)/3;
        if(gd[x]>=90)g[x]='A';
        else if(gd[x]>=80)g[x]='B';
        else if(gd[x]>=70)g[x]='C';
        else if(gd[x]>=60)g[x]='D';
        else {g[x]='F';}
        cout<<endl;
    }
    for(int i=0;i<5;i++){
        cout<<n[i]<<": "<<g[i]<<"("<<gd[i]<<"}"<<endl;
    }
}

void Problem8(){
    int lottery[5];
    int user[5];
    Title("Lottery Application");
    p8_input(lottery,user);
    AskExit("Want to Exit?");
}

void p8_input(int l[],int u[]){
    int prize=0;
    for(int i=0;i<5;i++){
        l[i]=rand()%10;
        cout<<l[i]<<endl;
        for(bool b=false;b==false;){
            cout<<"Enter the "<<Numbering(i+1)<<" number of your lottery(0-9): ";
            cin>>u[i];
            if(u[i]>=0&&u[i]<10){b=true;}
            else{cout<<"You Entered Incorrect Number!"<<endl;}
        }
        if(l[i]==u[i])prize++;
    }
    cout<<endl;
    if(prize==5){
        cout<<"Congratuation! you're a grand prize winner!"<<endl;
    }else{
        cout<<prize<<" matching digits in your lottery"<<endl;
    }
    cout<<"Result________\n| ";
    for(int i=0;i<5;i++){
        cout<<l[i]<<" ";
    }
    cout<<" |\n| ";
    for(int i=0;i<5;i++){
        cout<<u[i]<<" ";
    }
    cout<<" |"<<endl;
}

void Problem9(){
    int account[18]={5658845,4520125,7895122,8777541,8451277,1302850,
                     8080152,4562555,5552012,5050552,7825877,1250255,
                     1005231,6545231,3852085,7576651,7881200,4581002};
    int input;
    bool b=false;
    Title("Charge Account Validation");
    cout<<"Please Enter the account number:";
    cin>>input;
    for(int i=0;i<18;i++){
        if(account[i]==input)b=true;
    }
    if(b==true)cout<<"The number - "<<input<<" is valid."<<endl;
    else cout<<"The number - "<<input<<" is invalid"<<endl;
    AskExit("Want to Exit?");
}

void Problem10(){
    int lucky[10][5]={{1,3,5,7,9},{2,6,7,9,1},{2,6,7,9,2},{3,3,4,4,5},{5,5,5,5,5},{6,2,4,8,3},{7,7,7,7,7},{7,9,4,2,2},{8,5,6,4,7},{9,3,1,2,1}};
    Title("Lottery Winners");
    p10_input(lucky);
    AskExit("Want to Exit?");
}

void p10_input(int l[][5]){
    int r[5];
    int prize=0;
    for(int i=0;i<5;i++){
        for(bool b=false;b==false;){
            cout<<"Enter the "<<Numbering(i+1)<<" number of your lottery(0-9): ";
            cin>>r[i];
            if(r[i]>=0&&r[i]<10){b=true;}
            else{cout<<"You Entered Incorrect Number!"<<endl;}
        }
    }
    for(int i=0;i<10&&prize<5;i++){
        prize=0;
        for(int k=0;k<5;k++){
            if(l[i][k]==r[k])prize++;
        }
    }
    cout<<endl;
    if(prize==5){
        cout<<"Congratuation! A grand prize winner in this week!"<<endl;
    }else{
        cout<<"This week has no winner."<<endl;
    }
    cout<<"Result______________________\n| Magic number: ";
    for(int i=0;i<5;i++){
        cout<<r[i]<<" ";
    }
    for(int i=0;i<10;i++){
        cout<<" |\n| buyer number: ";
        for(int k=0;k<5;k++){
            cout<<l[i][k]<<" ";
        }
    }
    cout<<" |"<<endl;
}

void Title(string str){
    unsigned long len=str.length();
    string str2="";
    for(int k=0;k<len+4;k++){str2+="-";}
    cout<<endl<<str2<<endl<<"| "<<str<<" |"<<endl<<str2<<endl<<endl;
}

string Numbering(int i){
    string str;
    if(i==1)str="1st";
    else if(i==2)str="2nd";
    else if(i==3)str="3rd";
    else {str=Int2String(i);str+="th";}
    return str;
}

string Int2String(int n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

string Double2String(double n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

bool AskExit(string str){
    string a;
    bool c;
    for(bool b=false;b==false;){
        cout<<str<<"(Y)"<<endl;
        cin>>a;
        if(a=="Y"||a=="y"){c=true;b=true;}
        //else if(a=="N"||a=="n"){c=false;b=true;}
    }
    return c;
}

void Exit(){
    cout<<"Thank You"<<endl;
}