/*
* File:   main.cpp
* Author: TaeYoun Kim
* Created by Minji Kim on 2013. 11. 18..
* programming tools
* 1.0.11.18 //Xcode on OSX
* 1.1.11.26 //Qt Creator on Windows
* source - http://www.asciiworld.com/-Maps-.html  //World Map
*          http://www.chris.com/ASCII/  //Some Ascii code arts
*          http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20  //Ascii code text generator
*          http://blog.naver.com/dreamfox?Redirect=Log&logNo=30034645468 //String to Integer(KOR)
*          http://ascii.co.uk/art/dollar //Dollar image
  */

/*
 * PATCH NOTE
 * 1.0.11.18 - Setup libraries and basic settings
 * 1.1.11.26 - Intro banner
 * 1.2.11.26 - Add world map on intro
 * 1.3.11.27 - Change Font on Intro
 * 1.4.11.28 - Setup MENU
 * 1.5.11.29 - Create Visualized board
 * 1.6.12.01 - Add functions and variables on board
 * 1.7.12.02 - Build universial memory controller
 * 1.8.12.04 - Add constant informations
 * 1.9.12.04 - build structure for store user data
 * 1.10.12.04 - build letter and number image to use in multiple functions easily
 * 1.11.12.05 - fix some errors and add few variables in structure
 * 1.12.12.05 - Add 'rolling dices' action
 * 1.13.12.06 - Build more systems
 * 1.14.12.06 - Add Price info in the GameData
 * 1.15.12.07 - Build pay systems
 * 1.16.12.08 - Finished Basic systems
 * 2.0.12.08 - Alpha test version start
 * 2.1.12.08 - Add Chance card
 * 2.2.12.08 - Add Event card
 * 2.3.12.08 - Add Winner function
 * 2.4.12.08 - Fix some bugs
 * 2.5.12.08 - Fixed Fatal Error that appears when 4th player plays
 * 2.6.12.08 - Add some systems and fix more bugs
 * 2.7.12.08 - Alpha test successfully ends
 * 3.0.12.08 - Beta test starts
 * 3.1.12.08 - Delete custom mode
 * 3.2.12.08 - Add some system functions
 * 3.3.12.08 - Fixed Critical Error that player cannot visit other's land
 * 3.4.12.08 - Add Jail and airport
 * 3.5.12.09 - Now Jackpot is working
 * 3.5.12.09 - tax and casino's problem solved
 * 3.5.12.09 - Add exit on the menu
 * 3.6.12.10 - word correction - Pari->Paris, add STARTCAPITAL constant double for player can change their money easily.
 * 3.7.12.10 - Fixed bug that apears incorrect money on the board when player does not play.
 * 3.8.12.10 - Close Beta Test successfully ends
 */

/*
 *ERRORS
 *[001] - Cannot start the game/any key function does not work
 *[002] - Error when player input the player-name
 *[003] - Player is game over
 *[004] - Event card phase
  */

/*
 *Notes
 *cout<<showpoint<<fixed<<setprecision(2);
 */

//Libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>
#include <windows.h>
using namespace std;
#include "Player.h"

//Global Constants
const string VERSION="3.8.12.10.b";
const int MAXCHANCE=3;
const int MAXEVENT=3;
const double STARTCAPITAL=1000;

//function Prototypes
 //----SYSTEM---------
void GameStart();
void s_initializeData(GameData *);
string s_PlacePlayer(int,bool,P);
string s_PlaceOwner(int);
void s_PurchasePlace(int,int,GameData *,P *);
void s_GameOver(int,GameData *, P *);
void s_CallOrder(int,GameData, P *);
void s_StarterSetting(int,P *);
void s_EventCard(int,GameData, P *);
void s_Winner(int,GameData,P);
void s_jail(int,GameData,P *);
void s_air(int,GameData,P *);
void s_jackpot(int,GameData,P *);
void s_casino(int,GameData,P *);
void s_tax(int,GameData,P *);
//----UTILITY--------
string I2S(int);
string D2S(double);
int S2I(string);
string IntRank(int);
double u_Round(double val);

void u_ConvertLetter(string, int &, int &);
string u_StrImg(string, int, int, bool, GameData);
int u_placeowner_changer(int);
string InputString(string [],string [],string,string,int,int,bool,bool);
 //----DISPLAY--------
string d_Title(int,bool,bool,int,int);
string d_Menu(int,bool,bool,int);
string d_Board(int,bool,bool,int);
string d_Dice(int,bool,bool,int,int,int,int,GameData);
string d_DiceNumber(int,int,GameData);
string d_MovePlayer(int ,bool, bool, int,int, GameData,P *);
double d_PlaceInfo_Prices(int,int,int,GameData);
string d_Chance(int,bool, bool, int,int,GameData,P *);
string d_Event(int,bool, bool, int,int,GameData,P *);
string d_Event2_Lottery(int,bool, bool, int,int,GameData,P *);
string d_Jackpot(int);
string d_Setting(int,bool,bool,int,GameData,P);
string d_PlayerSetting(int,bool,bool,int,P *);
string d_PlaceInfo(int,bool,bool,bool,int,int,GameData,P *);
string d_BlankLine(int ,bool , bool , int ,int);
string d_temp(int,bool,bool,int,string,string,GameData);
string d_Jackpot2(double);


//int main(int argc, const char * argv[]){
int main(){
    srand(static_cast<unsigned int>(time(0)));
    GameStart();
}

void GameStart(){
    string menu[9]={"1","2","3","4","5","6","7","8","9"};
    string begin;
    int playerWhere[4];
    int place[10][36];
    P player,*playername=&player;
    GameData gamedata, *gd=&gamedata;
    bool endGame=false;
    s_initializeData(gd);
    player.jackpot=200;
    d_Title(0,true,false,50,100);
    begin=InputString(menu,menu,"Enter any key to start the game\n",d_Title(0,false,true,0,0)+"ERROR[001] - ",0,0,true,true);
    d_Menu(0,true,false,20);
    begin=InputString(menu,menu,"Please Select the menu\n",d_Menu(0,false,true,0)+"Incorrect number - ",2,0,true,false);
    if(begin=="2")return;
    d_PlayerSetting(0,true,false,20,playername);
    string name[4]={"","","",""};
    for(int i=0;i<4;i++){
        player.name[i]=InputString(menu,name,"Please Enter the "+IntRank(i+1)+" player's name. If Player does not play, enter 0\n",d_PlayerSetting(0,false,true,0,playername)+"ERROR[002] - ",0,3,true,false);
        if(player.name[i]!="0"){
            s_StarterSetting(i,playername);
            name[i]=player.name[i];
        }else{
            player.status[i]=false;
        }
        d_PlayerSetting(0,true,false,20,playername);
    }
    /*
    player.name[0]="123";
    player.name[1]="222";
    player.name[2]="asdf";
    s_StarterSetting(0,playername);
    s_StarterSetting(1,playername);
    s_StarterSetting(2,playername);
    player.chance[0]=2;
    //player.turn[0]=4;
    //player.money[0]=150;
    //player.money[0]=150;
    //gamedata.placeowner[12]=0;
    //gamedata.placelevel[12]=1;
    player.status[1]=true;
    player.status[2]=true;
    player.status[3]=false;
    */
    do{
        int odr=0;
        do{
            double prim=player.money[odr];
            if(player.status[odr]==true){
                if(player.specialEvent[odr]!=0){
                    if(player.specialEvent[odr]==1){
                        int mxmenu=3;
                        string mstr="";
                        if(player.money[odr]>=100){mstr+=" 4. Pay the bail";mxmenu++;}
                        d_Setting(0,true,false,20,gamedata,player);
                        player.order[odr]=S2I(InputString(menu,menu,"Player "+player.name[odr]+"'s Menu: 1.roll dices for double 2.see chance card 3.surrender"+mstr+"\n",d_Setting(0,false,true,0,gamedata,player)+"Incorrect number - ",mxmenu,0,true,false));
                        if(player.order[odr]==1){
                            player.dice[odr][0]=rand()%6+1;
                            player.dice[odr][1]=rand()%6+1;
                            d_Dice(0,true,false,20,20,player.dice[odr][0],player.dice[odr][1],gamedata);
                            Sleep(1000);
                            if(player.dice[odr][0]==player.dice[odr][1]){
                                d_MovePlayer(0,true,false,20,odr,gamedata,playername);
                            }else{
                                player.jail[odr]--;
                                if(player.jail[odr]<=0){
                                    player.specialEvent[odr]=0;
                                }
                            }
                        }else if(player.order[odr]==4){
                            player.money[odr]-=100;
                            player.specialEvent[odr]=0;
                            player.jail[odr]=0;
                        }else{
                            s_CallOrder(odr,gamedata,playername);
                        }
                    }else if(player.specialEvent[odr]==2){
                        d_Setting(0,true,false,20,gamedata,player);
                        player.order[odr]=S2I(InputString(menu,menu,"Player "+player.name[odr]+"'s Menu: 1.take airplane 2.see chance card 3.surrender\n",d_Setting(0,false,true,0,gamedata,player)+"Incorrect number - ",3,0,true,false));
                        if(player.order[odr]==1){
                            string limit[35];
                            int idx;
                            for(int r=0;r<35;r++){limit[r]=I2S(r+1);}
                            d_Setting(0,true,false,0,gamedata,player);
                            idx=S2I(InputString(limit,limit,"Enter the number you want to jump(1~35)\n",d_Setting(0,false,true,0,gamedata,player)+"Incorrect number - ",35,0,true,false));
                            player.dice[odr][0]=idx;
                            player.dice[odr][1]=0;
                            d_MovePlayer(0,true,false,20,odr,gamedata,playername);
                            Sleep(1000);
                        }else{
                            s_CallOrder(odr,gamedata,playername);
                        }
                    }
                }else{
                    d_Setting(0,true,false,20,gamedata,player);
                    player.order[odr]=S2I(InputString(menu,menu,"Player "+player.name[odr]+"'s Menu: 1.roll dices 2.see chance card 3.surrender\n",d_Setting(0,false,true,0,gamedata,player)+"Incorrect number - ",3,0,true,false));
                    s_CallOrder(odr,gamedata,playername);
                }
                if(player.order[odr]==3){
                    s_GameOver(odr,gd,playername);
                }
                if(player.order[odr]==2){
                    odr--;
                }
                if(player.order[odr]==6){
                    string mstr="1.store new card";
                    int mxmenu=1;
                    int pos=player.position[odr];
                    int bl=gamedata.placelevel[pos];
                    int tn=player.turn[odr];
                    int temp=0;
                    if(gamedata.placetype[pos]==3){//chance
                        int gcard=rand()%MAXCHANCE+1;
                        if(player.chance[odr]!=0&&gcard!=player.chance[odr]){
                            temp=player.chance[odr];
                            mstr+=" 2.keep card(";mstr+=gamedata.cardname[0][0][player.chance[odr]];mstr+=")";mxmenu++;
                        }
                        player.chance[odr]=gcard;
                        d_Chance(0,true,false,20,odr,gamedata,playername);
                        player.order[odr]=S2I(InputString(menu,menu,"You get new chance card - "+mstr+"\n",d_Chance(0,false,true,0,odr,gamedata,playername)+"Incorrect number - ",mxmenu,0,true,false));
                        if(player.order[odr]==2)player.chance[odr]=temp;
                    }else if(gamedata.placetype[pos]==4){//event
                        player.event[odr]=rand()%MAXEVENT+1;
                        d_Event(0,true,false,20,odr,gamedata,playername);
                        temp=S2I(InputString(menu,menu,"Press any key to continue\n",d_Chance(0,false,true,0,odr,gamedata,playername)+"ERROR[004] - ",0,0,true,true));
                        s_EventCard(odr,gamedata,playername);
                    }
                }
                if(player.order[odr]==7){
                    int mxmenu=1;
                    int pos=player.position[odr];
                    int pt=gamedata.placetype[pos];
                    if(pt==6){
                        s_casino(odr,gamedata,playername);
                        if(player.status==false){
                            s_GameOver(odr,gd,playername);
                        }
                    }else if(pt==7){
                        s_tax(odr,gamedata,playername);
                    }else if(pt==5){
                        if(gamedata.placename[pos]=="Jail"){
                            player.specialEvent[odr]=1;
                            s_jail(odr,gamedata,playername);
                        }else if(gamedata.placename[pos]=="Airport"){
                            player.specialEvent[odr]=2;
                            s_air(odr,gamedata,playername);
                        }else if(gamedata.placename[pos]=="Jackpot"){
                            s_jackpot(odr,gamedata,playername);
                        }
                    }
                }
                if(player.order[odr]==5){
                    d_PlaceInfo(0,true,false,false,20,odr,gamedata,playername);
                    string mstr="'s Menu: 1.leave";;
                    int mxmenu=1;
                    int pos=player.position[odr];
                    int bl=gamedata.placelevel[pos];
                    int tn=player.turn[odr];
                    int type=0;
                    if(gamedata.placetype[pos]==1){
                        if(gamedata.placeowner[pos]==4){
                            type=1;
                            if(player.money[odr]>=d_PlaceInfo_Prices(0,0,pos,gamedata)){mstr+=" 2.buy land";mxmenu++;}
                            if(tn>=1&&player.money[odr]>=d_PlaceInfo_Prices(0,1,pos,gamedata)){mstr+=" 3.buy house";mxmenu++;}
                            if(tn>=2&&player.money[odr]>=d_PlaceInfo_Prices(0,2,pos,gamedata)){mstr+=" 4.buy Inn";mxmenu++;}
                            if(tn>=3&&player.money[odr]>=d_PlaceInfo_Prices(0,3,pos,gamedata)){mstr+=" 5.buy hotel";mxmenu++;}
                        }else{
                            if(gamedata.placeowner[pos]==odr){
                                type=2;
                                if(tn>=1&&tn>=bl&&player.money[odr]>=d_PlaceInfo_Prices(3,bl,pos,gamedata))
                                {mstr+=" 2.Upgrade to ";mstr+= gamedata.buildingname[bl+1];;mxmenu++;}
                                if(tn>=2&&tn>=bl&&bl<3&&player.money[odr]>=d_PlaceInfo_Prices(3,bl,pos,gamedata)+d_PlaceInfo_Prices(3,bl+1,pos,gamedata))
                                {mstr+=" 3.Upgrade to ";mstr+= gamedata.buildingname[bl+2];;mxmenu++;}
                                if(tn>=3&&tn>=bl&&bl<3&&player.money[odr]>=d_PlaceInfo_Prices(3,bl,pos,gamedata)+d_PlaceInfo_Prices(3,bl+1,pos,gamedata)+d_PlaceInfo_Prices(3,bl+2,pos,gamedata))
                                {mstr+=" 4.Upgrade to ";mstr+= gamedata.buildingname[bl+3];;mxmenu++;}
                            }else{
                                type=3;
                                if(player.money[odr]>=d_PlaceInfo_Prices(2,bl,pos,gamedata))
                                {mstr+=" 2.buy place";;mxmenu++;}
                            }
                        }
                    }else if(gamedata.placetype[pos]==2){
                        if(gamedata.placeowner[pos]==4){
                            type=1;
                            if(player.money[odr]>=d_PlaceInfo_Prices(0,0,pos,gamedata)){mstr+=" 2.buy land";mxmenu++;}
                        }else{
                            if(gamedata.placeowner[pos]!=odr){
                                gamedata.placeprice[1][1][pos]+=25;
                            }
                        }
                    }
                    if(player.status[odr]==false){
                        s_GameOver(odr,gd,playername);
                        player.order[odr]=S2I(InputString(menu,menu,"Player "+player.name[odr]+" became insolvent.\nPress any key to continue",d_PlaceInfo(0,false,true,false,0,odr,gamedata,playername)+"ERROR[003] - ",0,0,true,true));
                    }
                    else{
                        player.order[odr]=S2I(InputString(menu,menu,"Player "+player.name[odr]+mstr+"\n",d_PlaceInfo(0,false,true,false,0,odr,gamedata,playername)+"Incorrect number - ",mxmenu,0,true,false));
                        if(player.order[odr]!=1){
                            s_PurchasePlace(type,odr,gd,playername);
                            d_PlaceInfo(0,true,false,true,20,odr,gamedata,playername);
                            player.order[odr]=S2I(InputString(menu,menu,"Press any key to continue",d_PlaceInfo(0,false,true,true,0,odr,gamedata,playername)+"ERROR[004] - ",0,0,true,true));
                        }
                    }
                }
            }
            if(prim!=player.money[odr]){
                if(prim>player.money[odr]){player.jackpot+=u_Round((prim-player.money[odr])*0.2);}
                else{player.jackpot+=u_Round((player.money[odr]-prim)*0.2);}
            }
            if(player.status[odr]==true&&player.dice[odr][0]==player.dice[odr][1]){odr--;}
            odr++;
            //check winner
            int winner=0;
            for(int ind=0;ind<4;ind++){if(player.status[ind]==true){winner++;}}
            if(winner==1){
                winner=4;
                for(int knd=0;knd<4;knd++){
                    if(player.status[knd]==true){
                        s_Winner(knd,gamedata,player);
                        return;
                    }
                }
            }
        }while(odr<4);
    }while(endGame==false);

    //d_Setting(0,true,false,20);
    //begin=InputString(menu,menu,"Please Select the menu\n",d_Board(0,false,true,0)+"Incorrect number - ",3,0,true,true);
}

void s_CallOrder(int pn,GameData g, P *p){
    int x;
    string y[1];
    for(int i=0;i<4;i++){
        if((*p).order[pn]==1){//Dice
            (*p).dice[pn][0]=rand()%6+1;
            (*p).dice[pn][1]=rand()%6+1;
            d_Dice(0,true,false,20,20,(*p).dice[pn][0],(*p).dice[pn][1],g);
            Sleep(1000);
            d_MovePlayer(0,true,false,20,pn,g,p);
            Sleep(2000);
            return;
        }else if((*p).order[pn]==2){//see card
            d_Chance(0,true,false,20,pn,g,p);
            x=S2I(InputString(y,y,"Press any key to return\n",d_Chance(0,false,true,0,pn,g,p)+"Incorrect number - ",0,0,true,true));
            return;
        }else if((*p).order[pn]==3){
            (*p).status[pn]=false;
        }
    }
}
void s_jail(int pn,GameData g,P *p){
    int x;
    string y[1];
    if((*p).chance[pn]==3){
        (*p).chance[pn]=0;
        (*p).specialEvent[pn]=0;
        d_temp(0,true,false,20,"Jail","You used chance card to escape from the jail.",g);
        x=S2I(InputString(y,y,"Enter any key to continue\n",d_temp(0,false,true,0,"Jail","You used chance card to escape from the jail.",g)+"Incorrect number - ",0,0,true,true));
    }else{
        (*p).jail[pn]=3;
        d_temp(0,true,false,20,"Jail","You cannot move from the jail while 3 turns",g);
        x=S2I(InputString(y,y,"Enter any key to continue\n",d_temp(0,false,true,0,"Jail","You used chance card to escape from the jail.",g)+"Incorrect number - ",0,0,true,true));
    }
}

void s_jackpot(int pn,GameData g,P *p){
    int x;
    string y[1];
    string str="You hit the jackpot!!! - $";
    str+=D2S((*p).jackpot);
    (*p).money[pn]+=(*p).jackpot;
    (*p).jackpot=200;
    d_temp(0,true,false,20,"Jackpot",str,g);
    x=S2I(InputString(y,y,"Enter any key to continue\n",d_temp(0,false,true,0,"Jackpot",str,g)+"Incorrect number - ",0,0,true,true));

}

void s_air(int pn,GameData g,P *p){
    int x;
    string y[1];
    d_temp(0,true,false,20,"Airport","You can go wherever you want to go next turn",g);
    x=S2I(InputString(y,y,"Enter any key to continue\n",d_temp(0,false,true,0,"Airport","You can go wherever you want to go next turn",g)+"Incorrect number - ",0,0,true,true));
}

void s_casino(int pn,GameData g,P *p){
    int x;
    string y[1];
    string str;
    if((*p).money[pn]>=50){
        str="You visit casino and bet $50 - if you win, you'll get $100";
        d_temp(0,true,false,20,"CASINO",str,g);
        x=S2I(InputString(y,y,"Enter any key to see result\n",d_temp(0,false,true,0,"CASINO",str,g)+"Incorrect number - ",0,0,true,true));
        x=rand()%2;
        if(x==1){
            (*p).money[pn]+=100;
            str="Good Luck! you got $100!!";
            d_temp(0,true,false,20,"YOU WIN",str,g);
            x=S2I(InputString(y,y,"Enter any key to see result\n",d_temp(0,false,true,0,"YOU WIN",str,g)+"Incorrect number - ",0,0,true,true));
        }else{
            (*p).money[pn]-=50;
            str="I'm so sorry.";
            d_temp(0,true,false,20,"YOU LOSE",str,g);
            x=S2I(InputString(y,y,"Enter any key to see result\n",d_temp(0,false,true,0,"YOU LOSE",str,g)+"Incorrect number - ",0,0,true,true));
        }
    }else{
        str="You visit casino,but you don't have enough money. Please visit later";
        d_temp(0,true,false,20,"CASINO",str,g);
        x=S2I(InputString(y,y,"Enter any key to see result\n",d_temp(0,false,true,0,"CASINO",str,g)+"Incorrect number - ",0,0,true,true));
    }
}

void s_tax(int pn,GameData g,P *p){
    int x;
    string y[1];
    double tax =(*p).money[pn]*0.1;
    string str="You have to pay $";
    str+=D2S(tax);
    if((*p).chance[pn]==2){
        str+=", but you evade a tax!!(chance card has gone)";
        (*p).chance[pn]=0;
    }else{
        (*p).money[pn]-=((*p).money[pn]*0.1);
    }
    d_temp(0,true,false,20,"Tax Service",str,g);
    x=S2I(InputString(y,y,"Enter any key to continue\n",d_temp(0,false,true,0,"Tax Service",str,g)+"Incorrect number - ",0,0,true,true));
}

string d_temp(int i,bool Animation, bool save, int duration1,string str1,string str2,GameData g){
    string str="";
     int d=duration1;
    if(Animation==true)i=0;
    do{
        if(i==15)str+= u_StrImg(str1,0,0,false,g);
        else if(i==16)str+= u_StrImg(str1,0,1,false,g);
        else if(i==17)str+= u_StrImg(str1,0,2,false,g);
        else if(i==18)str+= u_StrImg(str1,0,3,false,g);
        else if(i==19)str+= u_StrImg(str1,0,4,false,g);
        else if(i==20)str+= u_StrImg(str1,0,5,false,g);
       else if(i==40)str+= str2;
        else if(i<=42)str+="";
       if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
       else{i++;str+="\n";}
   }while(i<=42&&(Animation==true||save==true));
    return str;

}

void s_Winner(int pn,GameData g,P p){
    bool Animation=true,save=false;
    string str="";
    int d=50;
    int i=0;
    if(i==11||i==31||i==28||i==41)Sleep(500);
    if(i==41)Sleep(500);
    if(Animation==true)i=0;
    do{
            if(i==5)str+= u_StrImg("R E S U L T",0,0,false,g);
       else if(i==6)str+= u_StrImg("R E S U L T",0,1,false,g);
       else if(i==7)str+= u_StrImg("R E S U L T",0,2,false,g);
       else if(i==8)str+= u_StrImg("R E S U L T",0,3,false,g);
       else if(i==9)str+= u_StrImg("R E S U L T",0,4,false,g);
       else if(i==10)str+= u_StrImg("R E S U L T",0,5,false,g);
       else if(i==15)str+= u_StrImg("Player",0,0,false,g);
       else if(i==16)str+= u_StrImg("Player",0,1,false,g);
       else if(i==17)str+= u_StrImg("Player",0,2,false,g);
       else if(i==18)str+= u_StrImg("Player",0,3,false,g);
       else if(i==19)str+= u_StrImg("Player",0,4,false,g);
       else if(i==20)str+= u_StrImg("Player",0,5,false,g);
       else if(i==23)str+= u_StrImg(p.name[pn],0,0,false,g);
       else if(i==24)str+= u_StrImg(p.name[pn],0,1,false,g);
       else if(i==25)str+= u_StrImg(p.name[pn],0,2,false,g);
       else if(i==26)str+= u_StrImg(p.name[pn],0,3,false,g);
       else if(i==27)str+= u_StrImg(p.name[pn],0,4,false,g);
       else if(i==28)str+= u_StrImg(p.name[pn],0,5,false,g);
       else if(i==31)str+= u_StrImg("is WINNER",0,0,false,g);
       else if(i==32)str+= u_StrImg("is WINNER",0,1,false,g);
       else if(i==33)str+= u_StrImg("is WINNER",0,2,false,g);
       else if(i==34)str+= u_StrImg("is WINNER",0,3,false,g);
       else if(i==35)str+= u_StrImg("is WINNER",0,4,false,g);
       else if(i==36)str+= u_StrImg("is WINNER",0,5,false,g);
       else if(i==42)str+= "                                  Thank you for enjoy.";
        else if(i>=41)str+="";
       if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
       else{i++;str+="\n";}
   }while(i<=43&&(Animation==true||save==true));
   Sleep(5000);
}

void s_EventCard(int pn,GameData g, P *p){
    int x;
    string y[1];
    int e=(*p).event[pn];
    int pos=(*p).position[pn];
    if(e==1){//Going jail
        int jail;
        if(pos>9){
            jail=45-pos;
        }else{
            jail=9-pos;
        }
        (*p).dice[pn][0]=jail;
        (*p).dice[pn][1]=0;
        d_BlankLine(0,true,false,20,20);
        d_MovePlayer(0,true,false,20,pn,g,p);
        Sleep(1000);
    }else if(e==2){//Lottery
        d_Event2_Lottery(0,true,false,20,pn,g,p);
        x=S2I(InputString(y,y,"Press any key to continue\n",d_Event2_Lottery(0,false,true,0,pn,g,p)+"ERROR[005] - ",0,0,true,true));
    }else if(e==3){//Going Start line
        int start;
        if(pos!=0){
            start=36-pos;
            (*p).dice[pn][0]=start;
            (*p).dice[pn][1]=0;
            d_BlankLine(0,true,false,20,20);
            d_MovePlayer(0,true,false,20,pn,g,p);
            Sleep(1000);
        }
    }
}


string d_Chance(int i,bool Animation, bool save, int duration1,int pn,GameData g,P *p){
    string str="";
    string card1;
    string card2;
    if((*p).chance[pn]==0){
        card1="Empty";
        card2="You do not have any card.";
    }else{
        card1=g.cardname[0][0][(*p).chance[pn]];
        card2=g.cardname[0][1][(*p).chance[pn]];
    }
     int d=duration1;
    if(Animation==true)i=0;
    do{
       if(i==5)     str+=  "          _________________________________                         ";
       else if(i==6)str+=  "         [\\             __________         \\                        ";
       else if(i==7)str+=  "         [\\\\           /  ________\\         \\                       ";
       else if(i==8)str+=  "          \\\\\\          \\  \\_________         \\                      ";
       else if(i==9)str+=  "           \\\\\\          \\___________\\         \\                     ";
       else if(i==10)str+= "            \\\\\\           ____    ____         \\                    ";
       else if(i==11)str+= "             \\\\\\          \\   \\___\\   \\         \\                   ";
       else if(i==12)str+= "              \\\\\\          \\    ____   \\         \\                  ";
       else if(i==13)str+= "               \\\\\\          \\___\\   \\___\\         \\                 ";
       else if(i==14)str+= "                \\\\\\              ________          \\                ";
       else if(i==15)str+= "                 \\\\\\            |   ___  \\          \\               ";
       else if(i==16)str+= "                  \\\\\\           |   ___   \\          \\              ";
       else if(i==17)str+= "                   \\\\\\          |__|    \\__\\          \\             ";
       else if(i==18)str+= "                    \\\\\\           ____    ___          \\            ";
       else if(i==19)str+= "                     \\\\\\          \\   \\  /   \\          \\           ";
       else if(i==20)str+= "                      \\\\\\          \\   \\/     \\          \\          ";
       else if(i==21)str+= "                       \\\\\\          \\_____/\\___\\          \\         ";
       else if(i==22)str+= "                        \\\\\\            __________          \\        ";
       else if(i==23)str+= "                         \\\\\\          /  ________\\          \\       ";
       else if(i==24)str+= "                          \\\\\\         \\  \\_________          \\      ";
       else if(i==25)str+= "                           \\\\\\         \\___________\\          \\     ";
       else if(i==26)str+= "                            \\\\\\          ____________          \\    ";
       else if(i==27)str+= "                             \\\\\\         \\   ________\\          \\   ";
       else if(i==28)str+= "                              \\\\\\         \\   ________\\          \\  ";
       else if(i==29)str+= "                               \\\\\\         \\___________\\          \\ ";
       else if(i==30)str+= "                                \\\\\\ _______________________________\\";
       else if(i==31)str+= "                                 \\\\|_______________________________/";
       else if(i==32)str+= "                                  \\|______________________________/ ";
       else if(i==33)str+= "";
       else if(i==34)str+= u_StrImg(card1,0,0,false,g);
       else if(i==35)str+= u_StrImg(card1,0,1,false,g);
       else if(i==36)str+= u_StrImg(card1,0,2,false,g);
       else if(i==37)str+= u_StrImg(card1,0,3,false,g);
       else if(i==38)str+= u_StrImg(card1,0,4,false,g);
       else if(i==39)str+= u_StrImg(card1,0,5,false,g);
       else if(i==40)str+= card2;
        else if(i>=41)str+="";
       if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
       else{i++;str+="\n";}
   }while(i<=42&&(Animation==true||save==true));
    return str;

}


string d_Event2_Lottery(int i,bool Animation, bool save, int duration1,int pn,GameData g,P *p){
    string str="";
    int d=duration1;
    (*p).money[pn]+=200;
    if(Animation==true)i=0;
    do{
       if(i==2)str+= u_StrImg("Prize Winner",0,0,false,g);
       else if(i==3)str+= u_StrImg("Prize Winner",0,1,false,g);
       else if(i==4)str+= u_StrImg("Prize Winner",0,2,false,g);
       else if(i==5)str+= u_StrImg("Prize Winner",0,3,false,g);
       else if(i==6)str+= u_StrImg("Prize Winner",0,4,false,g);
       else if(i==7)str+= u_StrImg("Prize Winner",0,5,false,g);
       else if(i==8)str+= "";
       else if(i==9)str+= "";
       else if(i==10)str+= " ______________________________________________________________________ ";
       else if(i==11)str+= "|.============[_F_E_D_E_R_A_L___R_E_S_E_R_V_E___N_O_T_E_]=============.|";
       else if(i==12)str+= "||%&%&%&%_    _        _ _ _   _ _  _ _ _     _       _    _  %&%&%&%&||";
       else if(i==13)str+= "||%&.-.&/||_||_ | ||\\||||_| \\ (_ ||\\||_(_  /\\|_ |\\|V||_|)|/ |\\ %&.-.&&||";
       else if(i==14)str+= "||&// |\\ || ||_ \\_/| ||||_|_/ ,_)|||||_,_) \\/|  ||| ||_|\\|\\_|| &// |\\%||";
       else if(i==15)str+= "||| | | |%               ,-----,-'____'-,-----,               %| | | |||";
       else if(i==16)str+= "||| | | |&% \"\"\"\"\"\"\"\"\"\"  [    .-;\"`___ `\";-.    ]             &%| | | |||";
       else if(i==17)str+= "||&\\===//                `).'' .'`_.- `. '.'.(`  A 76355942 J  \\\\===/&||";
       else if(i==18)str+= "||&%'-'%/1                // .' /`     \\    \\\\                  \\%'-'%||";
       else if(i==19)str+= "||%&%&%/`   d8888b       // /   \\  _  _;,    \\\\      .-\"\"\"-.  1 `&%&%%||";
       else if(i==20)str+= "||&%&%&    8P |) Yb     ;; (     > a  a| \\    ;;    //A`Y A\\\\    &%&%&||";
       else if(i==21)str+= "||&%&%|    8b |) d8     || (    ,\\   \\ |  )   ||    ||.-'-.||    |%&%&||";
       else if(i==22)str+= "||%&%&|     Y8888P      ||  '--'/`  -- /-'    ||    \\\\_/~\\_//    |&%&%||";
       else if(i==23)str+= "||%&%&|                 ||     |\\`-.__/       ||     '-...-'     |&%&%||";
       else if(i==24)str+= "||%%%%|                 ||    /` |._ .|-.     ||                 |%&%&||";
       else if(i==25)str+= "||%&%&|  A 76355942 J  /;\\ _.'   \\  } \\  '-.  /;\\                |%&%&||";
       else if(i==26)str+= "||&%.-;               (,  '.      \\  } `\\   \\'  ,)   ,.,.,.,.,   ;-.%&||";
       else if(i==27)str+= "||%( | ) 1  \"\"\"\"\"\"\"   _( \\  ;...---------.;.; / )_ ```\"\"\"\"\"\"\" 1 ( | )%||";
       else if(i==28)str+= "||&%'-'==================\\`------------------`/=================='-'%&||";
       else if(i==29)str+= "||%&%&%&%&%&%&%%&%&&&%&%%&)O N E  D O L L A R(%&%&%&%&%&%&%%&%&&&%&%%&||";
       else if(i==30)str+= "||%JGS%&%&%&%&%&%&%&%&%&&/_.----------------._\\%&%&%%&%&&%%&%&%&%&%&%&||";
       else if(i==31)str+= "'\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`";
       else if(i==32)str+= "";
       else if(i==33)str+= "";
       else if(i==34)str+= u_StrImg("400",25,0,false,g);
       else if(i==35)str+= u_StrImg("400",25,1,false,g);
       else if(i==36)str+= u_StrImg("400",25,2,false,g);
       else if(i==37)str+= u_StrImg("400",25,3,false,g);
       else if(i==38)str+= u_StrImg("400",25,4,false,g);
       else if(i==39)str+= u_StrImg("400",25,5,false,g);
        else if(i==40)str+= "";
        else if(i>=41)str+="";
       if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
       else{i++;str+="\n";}
   }while(i<=42&&(Animation==true||save==true));
    return str;
}


string d_BlankLine(int i,bool Animation, bool save, int duration1,int line){
    string str="";
    int d=duration1;
    if(Animation==true)i=0;
    do{
        if(i<=line)str+="";
        if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
        else{i++;str+="\n";}
    }while(i<=line&&(Animation==true||save==true));
    return str;

}


string d_Event(int i,bool Animation, bool save, int duration1,int pn,GameData g,P *p){
    string str="";
     int d=duration1;
    if(Animation==true)i=0;
    do{
       if(i==8)str+=  "          _________________________________                      ";
       else if(i==9)str+=  "         [\\           ____________         \\                     ";
       else if(i==10)str+= "         [\\\\          \\   ________\\         \\                    ";
       else if(i==11)str+= "          \\\\\\          \\   ________\\         \\                   ";
       else if(i==12)str+= "           \\\\\\          \\___________\\         \\                  ";
       else if(i==13)str+= "            \\\\\\           ___      ___         \\                 ";
       else if(i==14)str+= "             \\\\\\          \\  \\    /  /          \\                ";
       else if(i==15)str+= "              \\\\\\          \\  \\__/  /            \\               ";
       else if(i==16)str+= "               \\\\\\          \\______/              \\              ";
       else if(i==17)str+= "                \\\\\\           ___________          \\             ";
       else if(i==18)str+= "                 \\\\\\          \\   _______\\          \\            ";
       else if(i==19)str+= "                  \\\\\\          \\   _______\\          \\           ";
       else if(i==20)str+= "                   \\\\\\          \\__________\\          \\          ";
       else if(i==21)str+= "                    \\\\\\           ____    ___          \\         ";
       else if(i==22)str+= "                     \\\\\\          \\   \\  /   \\          \\        ";
       else if(i==23)str+= "                      \\\\\\          \\   \\/     \\          \\       ";
       else if(i==24)str+= "                       \\\\\\          \\_____/\\___\\          \\      ";
       else if(i==25)str+= "                        \\\\\\          ____________          \\     ";
       else if(i==26)str+= "                         \\\\\\         \\____    ___\\          \\    ";
       else if(i==27)str+= "                          \\\\\\             \\   \\              \\   ";
       else if(i==28)str+= "                           \\\\\\             \\   \\              \\  ";
       else if(i==29)str+= "                            \\\\\\             \\___\\              \\ ";
       else if(i==30)str+= "                             \\\\\\________________________________\\";
       else if(i==31)str+= "                              \\\\|_______________________________/";
       else if(i==32)str+= "                               \\|______________________________/ ";
       else if(i==33)str+= "";
       else if(i==34)str+= u_StrImg(g.cardname[1][0][(*p).event[pn]],0,0,false,g);
       else if(i==35)str+= u_StrImg(g.cardname[1][0][(*p).event[pn]],0,1,false,g);
       else if(i==36)str+= u_StrImg(g.cardname[1][0][(*p).event[pn]],0,2,false,g);
       else if(i==37)str+= u_StrImg(g.cardname[1][0][(*p).event[pn]],0,3,false,g);
       else if(i==38)str+= u_StrImg(g.cardname[1][0][(*p).event[pn]],0,4,false,g);
       else if(i==39)str+= u_StrImg(g.cardname[1][0][(*p).event[pn]],0,5,false,g);
       else if(i==40)str+= g.cardname[1][1][(*p).event[pn]];
        else if(i>=41)str+="";
       if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
       else{i++;str+="\n";}
   }while(i<=42&&(Animation==true||save==true));
    return str;

}

void s_StarterSetting(int pn,P *p){
    (*p).status[pn]=true;
    (*p).position[pn]=0;
    (*p).turn[pn]=0;
    (*p).chance[pn]=0;
    (*p).money[pn]=STARTCAPITAL;
    (*p).specialEvent[pn]=0;
}

void s_PurchasePlace(int type,int pn, GameData *g,P *p){
    int pos=(*p).position[pn];
    int odr=(*p).order[pn];
    double *mny=&(*p).money[pn];
    int *owner=&(*g).placeowner[pos];
    int *bl=&(*g).placelevel[pos];
    if(type==1){//buy new
        *owner=pn;
        *mny-=d_PlaceInfo_Prices(0,odr-2,pos,*g);
        *bl=odr-1;
    }else if(type==2){//upgrade
        //order =2
        if(odr==2)*mny-=d_PlaceInfo_Prices(3,*bl,pos,*g);
        else if(odr==3)*mny-=(d_PlaceInfo_Prices(3,*bl,pos,*g)+d_PlaceInfo_Prices(3,*bl+1,pos,*g));
        else if(odr==4)*mny-=(d_PlaceInfo_Prices(3,*bl,pos,*g)+d_PlaceInfo_Prices(3,*bl+1,pos,*g)+d_PlaceInfo_Prices(3,*bl+2,pos,*g));
        *bl+=odr-1;
    }else if(type==3){//buy others
        *mny-=d_PlaceInfo_Prices(1,*bl,pos,*g);
        *owner=pn;
    }
}

void s_GameOver(int pn, GameData *g,P *p){
    for(int i=0;i<36;i++){
        if((*g).placeowner[i]==pn){
            (*g).placeowner[i]=4;
            (*g).placelevel[i]=0;
        }
    }
}

string d_PlaceInfo(int i,bool Animation, bool save, bool view, int duration1,int pn,GameData g,P *p){
    string str="",str2;
    int pos=(*p).position[pn];
    int tn=(*p).turn[pn];
    int bl=g.placelevel[pos];
    int bt=g.placetype[pos];
    int d=duration1;
    if(tn>3)tn=3;
    if(Animation==true)i=0;
    do{
        if(i==20)str+= u_StrImg(g.placename[pos],5,0,false,g);
        else if(i==21)str+= u_StrImg(g.placename[pos],5,1,false,g);
        else if(i==22)str+= u_StrImg(g.placename[pos],5,2,false,g);
        else if(i==23)str+= u_StrImg(g.placename[pos],5,3,false,g);
        else if(i==24)str+= u_StrImg(g.placename[pos],5,4,false,g);
        else if(i==25)str+= u_StrImg(g.placename[pos],5,5,false,g);
        else if(i==26){str+= "Owner: ";if(g.placeowner[pos]!=4)str+= (*p).name[g.placeowner[pos]];}
        else if(i==27){
            str+= "Your capital: $";
            if(Animation==true&&save==false){
                str+=D2S((*p).money[pn]);
                if(g.placeowner[pos]!=4&&g.placeowner[pos]!=pn){
                    if((*p).chance[pn]==1){
                        (*p).money[pn]+=(d_PlaceInfo_Prices(1,bl,pos,g)*1.5);
                        str+=" + ";
                        str+=D2S(d_PlaceInfo_Prices(1,bl,pos,g)*1.5);
                        str+="(chance)";
                        (*p).chance[pn]=0;
                    }
                    str+=" - ";
                    str+=D2S(d_PlaceInfo_Prices(1,bl,pos,g));
                    str+=" = $";
                    str+=D2S((*p).money[pn]-d_PlaceInfo_Prices(1,bl,pos,g));
                    if((*p).money[pn]-d_PlaceInfo_Prices(1,bl,pos,g)<=0){
                        str+=" you lost all money - GAME OVER";
                        (*p).money[g.placeowner[pos]]+=(*p).money[pn];
                        (*p).status[pn]=false;
                    }else{
                        (*p).money[g.placeowner[pos]]+=d_PlaceInfo_Prices(1,bl,pos,g);
                        (*p).money[pn]-=d_PlaceInfo_Prices(1,bl,pos,g);
                    }
                }
            }else{
                str+=D2S((*p).money[pn]);
            }
        }
        else if(i==28)str+= " _____________________________________________________________________________________________ ";
        else if(i==29)str+= "|                                                                                             |";
        else if(i==30){
            str+= "|  ";
            str+= g.buildingname[bl];
            for(int x=0;x<14-g.buildingname[bl].length();x++){str+=" ";}
            str+="                                                                             |";
        }
        else if(i==31)str+= "|_____________________________________________________________________________________________|";
        else if(i==32){str+= "|                                              ";str+=g.buildingimage[bl][0];}
        else if(i==33){
            str+= "|  ";
            if(view==true){
                str2="Congratulations!";
            }else{
                if(bl==0){
                    str2="land price: $";
                    str2+=D2S(d_PlaceInfo_Prices(0,0,pos,g));
                }else{
                    str2="room charge: $";
                    str2+=D2S(d_PlaceInfo_Prices(1,bl,pos,g));
                }
            }
            str+=str2;
            for(int x=0;x<40-str2.length();x++){str+=" ";}
            str+="    ";
            str+=g.buildingimage[bl][1];
        }
        else if(i==34){str+= "|                                              ";str+=g.buildingimage[bl][2];}
        else if(i==35){
            str+= "|  ";
            if(view==true){
                str2="Building Owner: ";
                str2+=(*p).name[g.placeowner[pos]];
            }else{
                if(bt==2){
                    str2="";
                }else{
                    if(bl==0){
                        if(tn>=1){
                            str2="land+house price: $";
                            str2+=D2S(d_PlaceInfo_Prices(0,1,pos,g));
                        }else{
                            str2="";
                        }
                    }else{
                        str2="Selling: $";
                        str2+=D2S(d_PlaceInfo_Prices(2,bl,pos,g));
                    }
                }
            }
            str+=str2;
            for(int x=0;x<40-str2.length();x++){str+=" ";}
            str+="    ";
            str+=g.buildingimage[bl][3];
        }
        else if(i==36){str+= "|                                              ";str+=g.buildingimage[bl][4];}
        else if(i==37){
            str+= "|  ";
            if(view==true){
                str2="Building: ";
                str2+=g.buildingname[bl];
            }else{
                if(bt==2){
                    str2="";
                }else{
                    if(bl==0){
                        if(tn>=2){
                            str2="land+Inn price: $";
                            str2+=D2S(d_PlaceInfo_Prices(0,2,pos,g));
                        }else{
                            str2="";
                        }
                    }else{
                        if(bl<5&&g.placeowner[pos]==pn){
                            str2="Upgrade to ";
                            str2+= g.buildingname[bl+1];
                            str2+=": $";
                            str2+=D2S(d_PlaceInfo_Prices(3,bl,pos,g));
                        }else{
                            str2="";
                        }
                    }
                }
            }
            str+=str2;
            for(int x=0;x<40-str2.length();x++){str+=" ";}
            str+="    ";
            str+=g.buildingimage[bl][5];
        }
        else if(i==38){str+= "|                                              ";str+=g.buildingimage[bl][6];}
        else if(i==39){
            str+= "|  ";
            if(view==true){
                str2="Room charge: $";
                str2+=D2S(d_PlaceInfo_Prices(1,bl,pos,g));
            }else{
                if(bt==2){
                    str2="";
                }else{
                    if(bl==0){
                        if(tn>=3){
                            str2="land+hotel price: $";
                            str2+=D2S(d_PlaceInfo_Prices(0,3,pos,g));
                        }else{
                            str2="";
                        }
                    }else{
                        if(bl<3&&tn>=bl&&g.placeowner[pos]==pn){
                            str2="Upgrade to ";
                            str2+= g.buildingname[bl+2];
                            str2+=": $";
                            str2+=D2S(d_PlaceInfo_Prices(3,bl,pos,g)+d_PlaceInfo_Prices(3,bl+1,pos,g));
                        }else{
                            str2="";
                        }
                    }
                }
            }
            //str2+=d_PlaceInfo_Prices(0,tn,pos,g);
            str+=str2;
            for(int x=0;x<40-str2.length();x++){str+=" ";}
            str+="    ";
            str+=g.buildingimage[bl][7];
        }
        else if(i==40){str+= "|                                              ";str+=g.buildingimage[bl][8];}
        else if(i==41){
            str+= "|  ";
            if(view==true){
                str2="";
            }else{
                if(bt==2){
                    str2="";
                }else{
                    if(bl==0){
                        if(tn>=3){
                            str2="";
                        }else{
                            str2="";
                        }
                    }else{
                        if(bl<2&&tn>=bl&&g.placeowner[pos]==pn){
                            str2="Upgrade to ";
                            str2+= g.buildingname[bl+3];
                            str2+=": $";
                            str2+=D2S(d_PlaceInfo_Prices(3,bl,pos,g)+d_PlaceInfo_Prices(3,bl+1,pos,g)+d_PlaceInfo_Prices(3,bl+2,pos,g));
                        }else{
                            str2="";
                        }
                    }
                }
            }
            //str2=d_PlaceInfo_Prices(,bl,pos,g);
            str+=str2;
            for(int x=0;x<40-str2.length();x++){str+=" ";}
            str+="    ";
            str+=g.buildingimage[bl][9];
        }
        else if(i==42)str+= "|______________________________________________|______________________________________________|";
        if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
        else{i++;str+="\n";}
    }while(i<=42&&(Animation==true||save==true));
    return str;
}

double d_PlaceInfo_Prices(int i,int bl,int place,GameData g){
    return g.placeprice[i][bl][place];
}

void s_ChangePlayerState(P *p,int pn,int order, int v1, int v2, int v3, int v4){
    /*
     *1-move
     *
     */
    if(int order=1){
        int i=(*p).position[pn]+v1;
        if(i>=36)i-=36;
        (*p).position[pn]=i;
    }
}

void u_ConvertLetter(string str, int &i, int &k){
    if(str=="A"){i=0;k=0;}
    else if(str=="B"){i=0;k=1;}
    else if(str=="C"){i=0;k=2;}
    else if(str=="D"){i=0;k=3;}
    else if(str=="E"){i=0;k=4;}
    else if(str=="F"){i=0;k=5;}
    else if(str=="G"){i=0;k=6;}
    else if(str=="H"){i=0;k=7;}
    else if(str=="I"){i=0;k=8;}
    else if(str=="J"){i=0;k=9;}
    else if(str=="K"){i=0;k=10;}
    else if(str=="L"){i=0;k=11;}
    else if(str=="M"){i=0;k=12;}
    else if(str=="N"){i=0;k=13;}
    else if(str=="O"){i=0;k=14;}
    else if(str=="P"){i=0;k=15;}
    else if(str=="Q"){i=0;k=16;}
    else if(str=="R"){i=0;k=17;}
    else if(str=="S"){i=0;k=18;}
    else if(str=="T"){i=0;k=19;}
    else if(str=="U"){i=0;k=20;}
    else if(str=="V"){i=0;k=21;}
    else if(str=="W"){i=0;k=22;}
    else if(str=="X"){i=0;k=23;}
    else if(str=="Y"){i=0;k=24;}
    else if(str=="Z"){i=0;k=25;}
    else if(str=="a"){i=1;k=0;}
    else if(str=="b"){i=1;k=1;}
    else if(str=="c"){i=1;k=2;}
    else if(str=="d"){i=1;k=3;}
    else if(str=="e"){i=1;k=4;}
    else if(str=="f"){i=1;k=5;}
    else if(str=="g"){i=1;k=6;}
    else if(str=="h"){i=1;k=7;}
    else if(str=="i"){i=1;k=8;}
    else if(str=="j"){i=1;k=9;}
    else if(str=="k"){i=1;k=10;}
    else if(str=="l"){i=1;k=11;}
    else if(str=="m"){i=1;k=12;}
    else if(str=="n"){i=1;k=13;}
    else if(str=="o"){i=1;k=14;}
    else if(str=="p"){i=1;k=15;}
    else if(str=="q"){i=1;k=16;}
    else if(str=="r"){i=1;k=17;}
    else if(str=="s"){i=1;k=18;}
    else if(str=="t"){i=1;k=19;}
    else if(str=="u"){i=1;k=20;}
    else if(str=="v"){i=1;k=21;}
    else if(str=="w"){i=1;k=22;}
    else if(str=="x"){i=1;k=23;}
    else if(str=="y"){i=1;k=24;}
    else if(str=="z"){i=1;k=25;}
    else if(str=="1"){i=2;k=1;}
    else if(str=="2"){i=2;k=2;}
    else if(str=="3"){i=2;k=3;}
    else if(str=="4"){i=2;k=4;}
    else if(str=="5"){i=2;k=5;}
    else if(str=="6"){i=2;k=6;}
    else if(str=="7"){i=2;k=7;}
    else if(str=="8"){i=2;k=8;}
    else if(str=="9"){i=2;k=9;}
    else if(str=="0"){i=2;k=0;}
    else if(str==" "){i=3;k=0;}
}

string u_StrImg(string str, int space, int line, bool complete, GameData g){
    string str2,str3="";
    int y,z;
    for(int x=0;x<6;x++){
        for(int i=0;i<space;i++){str3+=" ";}
        for(int k=0;k<str.length();k++){
            str2=str.substr(k,1);
            u_ConvertLetter(str2,y,z);
            if(complete==true){cout<<";";str3+=g.letter[y][z][x];}
            else{str3+=g.letter[y][z][line];}
        }
        if(complete==true){str3+="\n";}
        else{return str3;}
    }
    return str3;
}

string InputString(string ansTrue[], string ansFalse[], string ask, string reTryTxt,
                  int numTrue, int numFalse, bool askAgain, bool anyKey){
    string input;
    if(askAgain==false){cout<<ask;}
    for(bool b=false;b==false;){
        if(askAgain==true){cout<<ask;}
         cin>>input;
        if(anyKey==true){b=true;}
        else{
            for(int i=0;i<numTrue;i++){
                if(input==ansTrue[i]){b=true;}
            }
            if(numTrue==0&&numFalse!=0)b=true;
            for(int i=0;i<numFalse;i++){
                 if(input==ansFalse[i]){b=false;}
            }
            if(b==false){cout<<reTryTxt;}
        }
    }
    return input;
}

string I2S(int input){
    stringstream ss;
    ss << input;
     string str = ss.str();
    return str;
}

string D2S(double input){
    stringstream ss;
    ss << input;
    string str = ss.str();
    return str;
}

int S2I(string str){
    int i=atoi(str.c_str());
    return i;
}

string IntRank(int i){
    string str=I2S(i);
    str+="th";
    if(i==1)str="1st";
    else if(i==2)str="2nd";
    else if(i==3)str="3rd";
    return str;
}

string d_Title(int i,bool Animation, bool save, int duration1,int duration2){
     string str="";
    int d=duration1;
    if(Animation==true)i=0;
    do{
        if(i>23)d=duration2;
        if(i==23||i==34||i==42)Sleep(500);
        if(i==0)str+= "          _______________________________________________________________                 ";
         else if(i==1)str+= "         /         ,_   .  ._. _.  .                                     \\                ";
        else if(i==2)str+= "        /      , _-\\','|~\\~      ~/      ;-'_   _-'     ,;_;_,    ~~-     \\               ";
         else if(i==3)str+= "       |/~~-\\_/-'~'--' \\~~| ',    ,'      /  / ~|-_\\_/~/~      ~~--~~~~'--_|              ";
        else if(i==4)str+= "       |/              ,/'-/~ '\\ ,' _  , '|,'|~                   ._/-, /~ |              ";
         else if(i==5)str+= "       |~/-'~\\_,       '-,| '|. '   ~  ,\\ /'~                /    /_  /~   |              ";
        else if(i==6)str+= "       |.-~      '|        '',\\~|\\       _\\~     ,_  ,               /|    |              ";
         else if(i==7)str+= "       |      '\\        /'~          |_/~\\\\,-,~  \\ \\\"         ,_,/ |       |              ";
        else if(i==8)str+= "       |       |       /            ._-~'\\_ _~|              \\ ) /         |              ";
         else if(i==9)str+= "       |        \\   __-\\           '/      ~ |\\  \\_          /  ~          |              ";
        else if(i==10)str+="       |.,         '\\ |,  ~-_      - |          \\\\_' ~|  /\\  \\~ ,          |              ";
         else if(i==11)str+="       |           ~-_'  _;       '\\           '-,   \\,' /\\/  |            |              ";
        else if(i==12)str+="       |             '\\_,~'\\_       \\_ _,       /'    '  |, /|'            |              ";
         else if(i==13)str+="       |               /     \\_       ~ |      /         \\  ~'; -,_.       |              ";
        else if(i==14)str+="       |               |       ~\\        |    |  ,        '-_, ,; ~ ~\\     |              ";
         else if(i==15)str+="       |                \\,      /        \\    / /|            ,-, ,   -,   |              ";
        else if(i==16)str+="       |                 |    ,/          |  |' |/          ,-   ~ \\   '.  |              ";
         else if(i==17)str+="       |                ,|   ,/           \\ ,/              \\       |      |              ";
        else if(i==18)str+="       |                /    |             ~                 -~~-, /   _   |              ";
         else if(i==19)str+="       |                |  ,-'                                    ~    /   |              ";
        else if(i==20)str+="       |                / ,'                                      ~        |              ";
         else if(i==21)str+="        \\              ',|  ~                                             /               ";
        //else if(i==22)str+="        \\                 ~'                                              /               ";
         else if(i==22)str+="         \\_______________________________________________________________/                ";
        else if(i==23)str+="     $$\\      $$\\                                                   $$\\                   ";
         else if(i==24)str+="     $$$\\    $$$ |                                                  $$ |                  ";
        else if(i==25)str+="     $$$$\\  $$$$ | $$$$$$\\  $$$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  $$ |$$\\   $$\\         ";
         else if(i==26)str+="     $$\\$$\\$$ $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$ |$$ |  $$ |        ";
        else if(i==27)str+="     $$ \\$$$  $$ |$$ /  $$ |$$ |  $$ |$$ /  $$ |$$ /  $$ |$$ /  $$ |$$ |$$ |  $$ |        ";
         else if(i==28)str+="     $$ |\\$  /$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |$$ |  $$ |        ";
        else if(i==29)str+="     $$ | \\_/ $$ |\\$$$$$$  |$$ |  $$ |\\$$$$$$  |$$$$$$$  |\\$$$$$$  |$$ |\\$$$$$$$ |        ";
         else if(i==30)str+="     \\__|     \\__| \\______/ \\__|  \\__| \\______/ $$  ____/  \\______/ \\__| \\____$$ |        ";
        else if(i==31)str+="                                                $$ |                    $$\\   $$ |        ";
         else if(i==32)str+="                                                $$ |                    \\$$$$$$  |        ";
        else if(i==33)str+="                                                \\__|                     \\______/         ";
         else if(i==34)str+=" $$\\      $$\\                     $$\\       $$\\       $$$$$$$$\\                            ";
        else if(i==35)str+=" $$ | $\\  $$ |                    $$ |      $$ |      \\__$$  __|                           ";
         else if(i==36)str+=" $$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\  $$ | $$$$$$$ |         $$ | $$$$$$\\  $$\\   $$\\  $$$$$$\\  ";
        else if(i==37)str+=" $$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$ |$$  __$$ |         $$ |$$  __$$\\ $$ |  $$ |$$  __$$\\ ";
         else if(i==38)str+=" $$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ |$$ /  $$ |         $$ |$$ /  $$ |$$ |  $$ |$$ |  \\__|";
        else if(i==39)str+=" $$$  / \\$$$ |$$ |  $$ |$$ |      $$ |$$ |  $$ |         $$ |$$ |  $$ |$$ |  $$ |$$ |      ";
         else if(i==40)str+=" $$  /   \\$$ |\\$$$$$$  |$$ |      $$ |\\$$$$$$$ |         $$ |\\$$$$$$  |\\$$$$$$  |$$ |      ";
        else if(i==41)str+=" \\__/     \\__| \\______/ \\__|      \\__| \\_______|         \\__| \\______/  \\______/ \\__|      ";
        else if(i==42){str+="                           Copyright (R) TaeYoun Kim. All right reserved(VER. ";str+=VERSION;str+=")";}
        if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
         else{i++;str+="\n";}
    }while(i<=42&&(Animation==true||save==true));
    return str;
}

string d_Menu(int i,bool Animation, bool save, int duration1){
    string str="";
     int d=duration1;
    if(Animation==true)i=0;
    do{
        if(i==11)str+= "              .                                          ";
        else if(i==12)str+= "              |~                                         ";
         else if(i==13)str+= "             /|\\                                         ";
        else if(i==14)str+= "            |-.-|             __  __ ______ _   _ _    _ ";
        else if(i==15)str+= "            '-:-'            |  \\/  |  ____| \\ | | |  | |";
         else if(i==16)str+= "             [|]             | \\  / | |__  |  \\| | |  | |";
        else if(i==17)str+= "             [|]             | |\\/| |  __| | . ` | |  | |";
        else if(i==18)str+= "             [|]             | |  | | |____| |\\  | |__| |";
         else if(i==19)str+= "             [|]             |_|  |_|______|_| \\_|\\____/ ";
        else if(i==20)str+="             [|]                                         ";
        else if(i==21)str+="            .[|].                                        ";
         else if(i==22)str+="            :/|\\:             1. Normal Game             ";
        else if(i==23)str+="            [/|\\]                - start game            ";
        else if(i==24)str+="            [/|\\]                                         ";
         else if(i==25)str+="          .:_#|#_:.                                       ";
        else if(i==26)str+="          |_ '-' _|           2. Exit Game               ";
        else if(i==27)str+="          /\\:-.-:/\\              - End program              ";
         else if(i==28)str+="         /\\|_[|]_|/\\                                     ";
        else if(i==29)str+="       _/\\|~ [|] ~|/\\_                                   ";
        else if(i==30)str+="       [''=-.[|].-='']                                   ";
         else if(i==31)str+="       :-._   |   _.-:                                   ";
        else if(i==32)str+="       //\\;::-:-::;/\\\\                                   ";
        else if(i==33)str+="      /\\.'-\\\\/|\\//-'./\\                                  ";
         else if(i==34)str+="    .'\\/'   :\\|/:   '\\/'.                                ";
        else if(i==35)str+="  .//\\('    [\\|/]    ')/\\\\.                              ";
         else if(i==36)str+=" '':][\\.'  .[\\|/].  './][:''                             ";
        else if(i==37)str+="     ''    :/\\|/\\:    ''                                 ";
         else if(i==38)str+="          .[\\/|\\/].                                      ";
        else if(i==39)str+="            '.|.'                                        ";
        else if(i==40)str+="              '                                          ";
         else if(i>=41)str+="";
        if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
        else{i++;str+="\n";}
    }while(i<=42&&(Animation==true||save==true));
     return str;

}

string d_PlayerSetting(int i,bool Animation, bool save, int duration1,P *playername){
    string str="";
     int d=duration1;
    if(Animation==true)i=0;
    do{
        if(i==10)str+= "                     *                       ";
        if(i==11)str+= "                     :                       ";
        if(i==12)str+= "                     |                       ";
        if(i==13)str+= "                     |                       ";
        if(i==14)str+= "                     |                       ";
        if(i==15)str+= "                    :|:                      ";
        if(i==16){str+= "                    |||                 1p. ";
            if((*playername).status[0]==true)str+=(*playername).name[0];}
        if(i==17)str+= "               _____|||_____                 ";
        if(i==18){str+= "              /=============\\           2p. ";
            if((*playername).status[1]==true)str+=(*playername).name[1];}
        if(i==19)str+= "          ---<~~~~~~~~~~~~~~~>---            ";
        if(i==20){str+= "              \\-------------/           3p. ";
            if((*playername).status[2]==true)str+=(*playername).name[2];}
        if(i==21)str+= "               \\___________/                 ";
        if(i==22){str+= "                 \\||:::||/              4p. ";
            if((*playername).status[3]==true)str+=(*playername).name[3];}
        if(i==23)str+= "                  ||:::||                    ";
        if(i==24)str+= "                  ||:::||                    ";
        if(i==25)str+= "                  ||:::||                    ";
        if(i==26)str+= "                  ||ooo||                    ";
        if(i==27)str+= "                  ||___||                    ";
        if(i==28)str+= "                  ||:::||                    ";
        if(i==29)str+= "                  ||:::||                    ";
        if(i==30)str+= "                  ||:::||                    ";
        if(i==31)str+= "                  ||:::||                    ";
        if(i==32)str+= "                  ||:::||                    ";
        if(i==33)str+= "                 /||:::||\\                   ";
        if(i==34)str+= "                / ||:::|| \\                  ";
        if(i==35)str+= "               /  ||:::||  \\                 ";
        if(i==36)str+= "              /   ||:::||   \\                ";
        if(i==37)str+= "          ___/____||:::||____\\____           ";
        if(i==38)str+= "         /~~~~~~~~~~~~~~~~~~~~~~~~\\          ";
        if(i==39)str+= "        /   |~~~~~~~~|  _____      \\         ";
        if(i==40)str+= "        |   |________| |  |  |     |         ";
        if(i==41)str+= "  ______|______________|__|__|_____|_________";
        else if(i>=41)str+="";
       if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
       else{i++;str+="\n";}
   }while(i<=42&&(Animation==true||save==true));
    return str;

}




string d_Board(int i,bool Animation, bool save, int duration1){
    string str="";
    int d=duration1;
    if(Animation==true)i=0;
    do{
        if(i==0)str+= " _____________________________________________________________________________________________ ";
    else if(i==1)str+= "|          | B.SILIA|  BALI  |SANTIAGO| EVENT  |  OSLO  | S.HOLM | CHANCE | MOSCOW |          |";
   else if(i==2)str+= "|   JAIL   |        |        |        |        |        |        |        |        | JACKPOT! |";
    else if(i==3)str+= "|          |        |        |        |        |        |        |        |        |          |";
   else if(i==4)str+= "|          |________|________|________|________|________|________|________|________|          |";
    else if(i==5)str+= "|__________|________|________|________|________|________|________|________|________|__________|";
   else if(i==6)str+= "| S.PORE | |                                                                       | | ATHENS |";
    else if(i==7)str+= "|        | |                                                                       | |        |";
   else if(i==8)str+= "|        | |         __________                                                    | |        |";
    else if(i==9)str+= "|________|_|        /    C    /)                                                   |_|________|";
   else if(i==10)str+="| NEWDELI| |       /    H    //                                                    | | P.RICO |";
    else if(i==11)str+="|        | |      /    A    //                                                     | |        |";
   else if(i==12)str+="|        | |     /    N    //                                                      | |        |";
    else if(i==13)str+="|________|_|    /    G    //                                                       |_|________|";
   else if(i==14)str+="| CHANCE | |   /____E____//                                                        | |  ROME  |";
    else if(i==15)str+="|        | |   \\\\\\\\\\/                                                         | |        |";
   else if(i==16)str+="|        | |                                                                       | |        |";
    else if(i==17)str+="|________|_|                           _________________                           |_|________|";
   else if(i==18)str+="| BANGKOK| |                          |                 |                          | | EVENT  |";
    else if(i==19)str+="|        | |                          |  J A C K P O T  |                          | |        |";
   else if(i==20)str+="|        | |                  ________|_________________|________                  | |        |";
    else if(i==21)str+="|________|_|                 |                                   |                 |_|________|";
   else if(i==22)str+="|  GUAM  | |                 |                                   |                 | | BERLIN |";
    else if(i==23)str+="|        | |                 |___________________________________|                 | |        |";
   else if(i==24)str+="|        | |                                                                       | |        |";
    else if(i==25)str+="|________|_|                                                                       |_|________|";
   else if(i==26)str+="| CAIRO  | |                                                                       | | SICILiA|";
    else if(i==27)str+="|        | |                                                     __________        | |        |";
   else if(i==28)str+="|        | |                                                    /    E    /)       | |        |";
    else if(i==29)str+="|________|_|                                                   /    V    //        |_|________|";
   else if(i==30)str+="| CASINO | |                                                  /    E    //         | |  PARI  |";
    else if(i==31)str+="|        | |                                                 /    N    //          | |        |";
   else if(i==32)str+="|        | |                                                /    T    //           | |        |";
    else if(i==33)str+="|________|_|                                               /_________//            |_|________|";
   else if(i==34)str+="| TUNIS  | |                                               |_________/             | | LONDON |";
    else if(i==35)str+="|        | |                                                                       | |        |";
   else if(i==36)str+="|        | |                                                                       | |        |";
    else if(i==37)str+="|________|_|_______________________________________________________________________|_|________|";
   else if(i==38)str+="|          |________|________|________|________|________|________|________|________|          |";
    else if(i==39)str+="|  START!  |  L.A.  |  TAX   |NEW YORK| EVENT  | SEOUL  | TOKYO  | CHANCE |BEIJING | AIRPORT! |";
   else if(i==40)str+="|          |        |        |        |        |        |        |        |        |          |";
    else if(i==41)str+="|          |        |        |        |        |        |        |        |        |          |";
   else if(i==42)str+="|__________|________|________|________|________|________|________|________|________|__________|";
         if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
        else{i++;str+="\n";}
    }while(i<=42&&(Animation==true||save==true));
    return str;

}

string d_Dice(int i,bool Animation, bool save, int duration1,int duration2,int num1,int num2,GameData g){
    string str="";
    int d=duration1;
    int db=54;
    if(num1==num2)db=62;
    if(Animation==true)i=0;
    do{
        if(i==16)Sleep(500);
        if(i>15)d=duration2;
        if(i==6)str+= " ______     ______     __         __         __     __   __     ______                 ";
        else if(i==7)str+= "/\\  == \\   /\\  __ \\   /\\ \\       /\\ \\       /\\ \\   /\\ \"-.\\ \\   /\\  ___\\                ";
        else if(i==8)str+= "\\ \\  __<   \\ \\ \\/\\ \\  \\ \\ \\____  \\ \\ \\____  \\ \\ \\  \\ \\ \\-.  \\  \\ \\ \\__ \\     __        ";
        else if(i==9)str+= " \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\   /\\ \\       ";
        else if(i==10)str+="  \\/_/ /_/   \\/_____/   \\/_____/   \\/_____/   \\/_/   \\/_/ \\/_/   \\/_____/   \\ \\ \\      ";
        else if(i==11)str+="                               _____     __     ______     ______     ______ \\ \\ \\     ";
        else if(i==12)str+="                              /\\  __-.  /\\ \\   /\\  ___\\   /\\  ___\\   /\\  ___\\ \\ \\_\\    ";
        else if(i==13)str+="                              \\ \\ \\/\\ \\ \\ \\ \\  \\ \\ \\____  \\ \\  __\\   \\ \\___  \\ \\/_/_   ";
        else if(i==14)str+="                               \\ \\____-  \\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\/\\_____\\  /\\_\\  ";
        else if(i==15)str+="                                \\/____/   \\/_/   \\/_____/   \\/_____/   \\/_____/  \\/_/  ";
        else if(i==36)str+="        ___________________                                  ";
        else if(i==37){str+="       /\\         ";str+=d_DiceNumber(num1,0,g);str+=" \\                                 ";}
        else if(i==38){str+="      /  \\        ";str+=d_DiceNumber(num1,1,g);str+="  \\    ___________________         ";}
        else if(i==39){str+="     /    \\       ";str+=d_DiceNumber(num1,2,g);str+="   \\  /\\          ";str+=d_DiceNumber(num2,0,g);str+="\\        ";}
        else if(i==40){str+="    /      \\      ";str+=d_DiceNumber(num1,3,g);str+="    \\/  \\         ";str+=d_DiceNumber(num2,1,g);str+=" \\       ";}
        else if(i==41){str+="   /        \\     ";str+=d_DiceNumber(num1,4,g);str+="     \\   \\        ";str+=d_DiceNumber(num2,2,g);str+="  \\      ";}
        else if(i==42){str+="  /          \\    ";str+=d_DiceNumber(num1,5,g);str+="      \\   \\       ";str+=d_DiceNumber(num2,3,g);str+="   \\     ";}
        else if(i==43){str+=" /            \\                  \\   \\      ";str+=d_DiceNumber(num2,4,g);str+="    \\    ";}
        else if(i==44){str+="/              \\__________________\\   \\     ";str+=d_DiceNumber(num2,5,g);str+="     \\   ";}
        else if(i==45){str+="\\              /                  /    \\                  \\  ";}
        else if(i==46)str+=" \\            /                  /      \\__________________\\ ";
        else if(i==47)str+="  \\          /                  /       /                  / ";
        else if(i==48)str+="   \\        /                  /       /                  /  ";
        else if(i==49)str+="    \\      /                  /       /                  /   ";
        else if(i==50)str+="     \\    /                  /       /                  /    ";
        else if(i==51)str+="      \\  /                  /\\      /                  /     ";
        else if(i==52)str+="       \\/__________________/  \\    /                  /      ";
        else if(i==53)str+="                               \\  /                  /       ";
        else if(i==54)str+="                                \\/__________________/        ";
        else if(i==55)str+="                                                                               __   __     ";
        else if(i==56)str+="                _____     ______     __  __     ______     __         ______  /\\ \\ /\\ \\    ";
        else if(i==57)str+="               /\\  __-.  /\\  __ \\   /\\ \\/\\ \\   /\\  == \\   /\\ \\       /\\  ___\\ \\ \\_\\\\ \\_\\   ";
        else if(i==58)str+="               \\ \\ \\/\\ \\ \\ \\ \\/\\ \\  \\ \\ \\_\\ \\  \\ \\  __<   \\ \\ \\____  \\ \\  __\\  \\/_/_\\/_/_  ";
        else if(i==59)str+="                \\ \\____-  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  /\\_\\ /\\_\\ ";
        else if(i==60)str+="                 \\/____/   \\/_____/   \\/_____/   \\/_____/   \\/_____/   \\/_____/  \\/_/ \\/_/ ";
        else if(i>=db||i<=5||(i>15&&i<36))str+="";
        if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
        else{i++;str+="\n";}
    }while(i<=db&&(Animation==true||save==true));
     return str;

}

string d_DiceNumber(int n,int h,GameData g){
    string str="";
    if(n==1){
        str+="  ";
        str+=g.letter[2][n][h];
        str+="  ";
    }else if(n==2){
        str+=" ";
        str+=g.letter[2][n][h];
        str+=" ";
    }else if(n==3||n==5||n==6){
        str+=g.letter[2][n][h];
        str+=" ";
    }else if(n==4){
        str+=g.letter[2][n][h];
    }
    return str;
}

int u_placeowner_changer(int i){
    if(i==4)return i-4;
    return i+1;
}

string d_MovePlayer(int i,bool Animation, bool save, int duration1,int pn, GameData g,P *p){
    string str="";
    int cp=(*p).position[pn];
    s_ChangePlayerState(p,pn,1,(*p).dice[pn][0]+(*p).dice[pn][1],0,0,0);
    int ap=(*p).position[pn];
    int d=duration1;
    if(g.placetype[ap]==1||g.placetype[ap]==2){(*p).order[pn]=5;}
    else if(g.placetype[ap]==3||g.placetype[ap]==4)(*p).order[pn]=6;
    else if(g.placetype[ap]==5||g.placetype[ap]==6||g.placetype[ap]==7)(*p).order[pn]=7;
    if(Animation==true)i=0;
    do{
       if(i==5)str+=  " _______________                             _______________    ";
       else if(i==6)str+=  "|               |         O                 |               |   ";
       else if(i==7){str+=  "|    ";
                       if(g.placetype[cp]==1||g.placetype[cp]==2){str+=I2S(u_placeowner_changer(g.placeowner[cp]));}
                       else{str+=" ";}
                       str+="     ";
                       if(g.placetype[cp]==1||g.placetype[cp]==2){str+=I2S(g.placelevel[cp]);}
                       else{str+=" ";}
                       str+="    |        /|\\/               |    ";
                       if(g.placetype[ap]==1||g.placetype[ap]==2){str+=I2S(u_placeowner_changer(g.placeowner[ap]));}
                       else{str+=" ";}
                       str+="     ";
                       if(g.placetype[ap]==1||g.placetype[ap]==2){str+=I2S(g.placelevel[ap]);}
                       else{str+=" ";}
                       str+="    |   ";
                   }
       else if(i==8)str+=  "|_______________|        \\|_                |_______________|   ";
       else if(i==9)str+=  "|               |       _/  \\      |\\       |               |   ";
       else if(i==10){str+="|  ";
                        str+=g.placename[cp];
                        for(int k=0;k<11-g.placename[cp].length();k++){str+=" ";}
                        str+="  |    ______________| \\      |  ";
                        str+=g.placename[ap];
                        for(int k=0;k<11-g.placename[ap].length();k++){str+=" ";}
                        str+="  |   ";
                    }
       else if(i==11)str+= "|               |   |                 \\     |               |   ";
       else if(i==12)str+= "|               |   |______________   /     |               |   ";
       else if(i==13)str+= "|               |                  | /      |               |   ";
       else if(i==14)str+= "|               |                  |/       |               |   ";
       else if(i==15)str+= "|               |                           |               |   ";
       else if(i==16)str+= "|_______________|                           |_______________|   ";
       else if(i==17){
            if(ap<cp){
                str+= "You passed Start line - You earned $200";
                (*p).money[pn]+=200;
            }else{
                str+= "";
            }
       }
       else if(i>=18||i<=4)str+="";
       if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
       else{i++;str+="\n";}
    }while(i<=18&&(Animation==true||save==true));
     return str;

}

string s_PlacePlayer(int place,bool top,P player){
    //Max Place is 36 - start is 0
    string str="";
    int num=1;
    if(top==false){num+=2;str+=" ";}
    for(int i=0;i<2;i++){
        if(player.position[i+num-1]==place&&player.status[i+num-1]==true){
             str+=I2S(i+num);
        }else{
            str+=" ";
        }
        if(i==0)str+=" ";
    }
    if(top==true){str+=" ";}
     return str;
}

/*string s_PlaceOwner(int p[], int place){
    string str="";
    for(int i=0;i<4;i++){
        if(p==i){str=I2S(i+1);}
    }
    return str;
}*/

void u_LoadBoardInfo(int player[][4],int place[][36],int *wplayer, int *mplayer, int *cplayer, int *oplace, int *lplace){
    for(int i=0;i<4;i++){
        player[0][i]=*(wplayer+i);
        player[2][i]=*(mplayer+i);
        player[3][i]=*(cplayer+i);
    }
    for(int k=0;k<36;k++){
        place[2][k]=*(oplace+k);
    }
}

string d_Jackpot(int m){
    string str="";
    for(int i=0;i<28;i++){
        if(pow(10.0,i)>m){
            str+=I2S(m);
            for(int k=0;k<29-i;k++){
                str+=" ";
             }
            break;
        }
    }
    return str;
}

string d_Jackpot2(double m){
    string str="";
    string str2=D2S(m);
    for(int i=0;i<29-str2.length();i++){
        str+=" ";
    }
    str2+=str;
    return str2;
}

string u_currentcapital(int pn,P p){
    string str=D2S(p.money[pn]),str2="";
    if(p.status[pn]==false)str="";
    for(int i=0;i<25-str.length();i++){str2+=" ";}
    str+=str2;
    return str;
}

string d_Setting(int i,bool Animation, bool save, int duration1,GameData g, P player){
    string str="";
    int jackpot=10;
    int d=duration1;
    if(Animation==true)i=0;
     do{
        if(i==0){str+= " _____________________________________________________________________________________________ ";}
        else if(i==1){str+= "|          | B.SILIA|  BALI  |SANTIAGO| EVENT  |  OSLO  | S.HOLM | CHANCE | MOSCOW |          |";}
         else if(i==2){str+= "|   JAIL   |  ";str+=s_PlacePlayer(10,true,player);str+="  |  ";str+=s_PlacePlayer(11,true,player);str+="  |  ";str+=s_PlacePlayer(12,true,player);str+="  |  ";str+=s_PlacePlayer(13,true,player);str+="  |  ";str+=s_PlacePlayer(14,true,player);str+="  |  ";str+=s_PlacePlayer(15,true,player);str+="  |  ";str+=s_PlacePlayer(16,true,player);str+="  |  ";str+=s_PlacePlayer(17,true,player);str+="  | JACKPOT! |";}
         else if(i==3){str+= "|   ";str+=s_PlacePlayer(9,true,player);str+="   |  ";str+=s_PlacePlayer(10,false,player);str+="  |  ";str+=s_PlacePlayer(11,false,player);str+="  |  ";str+=s_PlacePlayer(12,false,player);str+="  |  ";str+=s_PlacePlayer(13,false,player);str+="  |  ";str+=s_PlacePlayer(14,false,player);str+="  |  ";str+=s_PlacePlayer(15,false,player);str+="  |  ";str+=s_PlacePlayer(16,false,player);str+="  |  ";str+=s_PlacePlayer(17,false,player);str+="  |   ";str+=s_PlacePlayer(18,true,player);str+="   |";}
         else if(i==4){str+= "|   ";str+=s_PlacePlayer(9,false,player);str+="   |________|________|________|________|________|________|________|________|   ";str+=s_PlacePlayer(18,false,player);str+="   |";}
         else if(i==5){str+= "|__________|__";str+=I2S(u_placeowner_changer(g.placeowner[10]));str+="__";str+=I2S(g.placelevel[10]);str+="__|__";str+=I2S(u_placeowner_changer(g.placeowner[11]));str+="__";str+=I2S(g.placelevel[11]);str+="__|__";str+=I2S(u_placeowner_changer(g.placeowner[12]));str+="__";str+=I2S(g.placelevel[12]);str+="__|________|__";str+=I2S(u_placeowner_changer(g.placeowner[14]));str+="__";str+=I2S(g.placelevel[14]);str+="__|__";str+=I2S(u_placeowner_changer(g.placeowner[15]));str+="__";str+=I2S(g.placelevel[15]);str+="__|________|__";str+=I2S(u_placeowner_changer(g.placeowner[17]));str+="__";str+=I2S(g.placelevel[17]);str+="__|__________|";}
        else if(i==6){str+= "| S.PORE | |                                                                       | | ATHENS |";}
         else if(i==7){str+= "|  ";str+=s_PlacePlayer(8,true,player);str+="  |";str+=I2S(u_placeowner_changer(g.placeowner[8]));str+="|                                                                       |";str+=I2S(u_placeowner_changer(g.placeowner[19]));str+="|  ";str+=s_PlacePlayer(19,true,player);str+="  |";}
         else if(i==8){str+= "|  ";str+=s_PlacePlayer(8,false,player);str+="  |";str+=I2S(g.placelevel[8]);str+="|         __________                                                    |";str+=I2S(g.placelevel[19]);str+="|  ";str+=s_PlacePlayer(19,false,player);str+="  |";}
        else if(i==9){str+= "|________|_|        /    C    /)                  P1 $ ";str+=u_currentcapital(0,player);str+="   |_|________|";}
        else if(i==10){str+="| NEWDELI| |       /    H    //                   P2 $ ";str+=u_currentcapital(1,player);str+="   | | P.RICO |";}
         else if(i==11){str+="|  ";str+=s_PlacePlayer(7,true,player);str+="  |";str+=I2S(u_placeowner_changer(g.placeowner[7]));str+="|      /    A    //                    P3 $ ";str+=u_currentcapital(2,player);str+="   |";str+=I2S(u_placeowner_changer(g.placeowner[20]));str+="|  ";str+=s_PlacePlayer(20,true,player);str+="  |";}
         else if(i==12){str+="|  ";str+=s_PlacePlayer(7,false,player);str+="  |";str+=I2S(g.placelevel[7]);str+="|     /    N    //                     P4 $ ";str+=u_currentcapital(3,player);str+="   |";str+=I2S(g.placelevel[20]);str+="|  ";str+=s_PlacePlayer(20,false,player);str+="  |";}
         else if(i==13){str+="|________|_|    /    G    //                                                       |_|________|";}
        else if(i==14){str+="| CHANCE | |   /____E____//                                                        | |  ROME  |";}
         else if(i==15){str+="|  ";str+=s_PlacePlayer(6,true,player);str+="  | |   \\\\\\\\\\\\\\\\\\\\/                                                         |";str+=I2S(u_placeowner_changer(g.placeowner[21]));str+="|  ";str+=s_PlacePlayer(21,true,player);str+="  |";}
         else if(i==16){str+="|  ";str+=s_PlacePlayer(6,false,player);str+="  | |                                                                       |";str+=I2S(g.placelevel[21]);str+="|  ";str+=s_PlacePlayer(21,false,player);str+="  |";}
         else if(i==17){str+="|________|_|                           _________________                           |_|________|";}
        else if(i==18){str+="| BANGKOK| |                          |                 |                          | | EVENT  |";}
         else if(i==19){str+="|  ";str+=s_PlacePlayer(5,true,player);str+="  |";str+=I2S(u_placeowner_changer(g.placeowner[5]));str+="|                          |  J A C K P O T  |                          | |  ";str+=s_PlacePlayer(22,true,player);str+="  |";}
         else if(i==20){str+="|  ";str+=s_PlacePlayer(5,false,player);str+="  |";str+=I2S(g.placelevel[5]);str+="|                  ________|_________________|________                  | |  ";str+=s_PlacePlayer(22,false,player);str+="  |";}
         else if(i==21){str+="|________|_|                 |                                   |                 |_|________|";}
        else if(i==22){str+="|  GUAM  | |                 | $ ";str+=d_Jackpot2(player.jackpot);str+="   |                 | | BERLIN |";}
         else if(i==23){str+="|  ";str+=s_PlacePlayer(4,true,player);str+="  |";str+=I2S(u_placeowner_changer(g.placeowner[4]));str+="|                 |___________________________________|                 |";str+=I2S(u_placeowner_changer(g.placeowner[23]));str+="|  ";str+=s_PlacePlayer(23,true,player);str+="  |";}
         else if(i==24){str+="|  ";str+=s_PlacePlayer(4,false,player);str+="  |";str+=I2S(g.placelevel[4]);str+="|                                                                       |";str+=I2S(g.placelevel[23]);str+="|  ";str+=s_PlacePlayer(23,false,player);str+="  |";}
         else if(i==25){str+="|________|_|                                                                       |_|________|";}
        else if(i==26){str+="| CAIRO  | |                                                                       | | SICILiA|";}
         else if(i==27){str+="|  ";str+=s_PlacePlayer(3,true,player);str+="  |";str+=I2S(u_placeowner_changer(g.placeowner[3]));str+="|                                                     __________        |";str+=I2S(u_placeowner_changer(g.placeowner[24]));str+="|  ";str+=s_PlacePlayer(24,true,player);str+="  |";}
         else if(i==28){str+="|  ";str+=s_PlacePlayer(3,false,player);str+="  |";str+=I2S(g.placelevel[3]);str+="|                                                    /    E    /)       |";str+=I2S(g.placelevel[24]);str+="|  ";str+=s_PlacePlayer(24,false,player);str+="  |";}
         else if(i==29){str+="|________|_|                                                   /    V    //        |_|________|";}
        else if(i==30){str+="| CASINO | |                                                  /    E    //         | |  PARIS |";}
         else if(i==31){str+="|  ";str+=s_PlacePlayer(2,true,player);str+="  | |                                                 /    N    //          |";str+=I2S(u_placeowner_changer(g.placeowner[25]));str+="|  ";str+=s_PlacePlayer(25,true,player);str+="  |";}
         else if(i==32){str+="|  ";str+=s_PlacePlayer(2,false,player);str+="  | |                                                /    T    //           |";str+=I2S(g.placelevel[25]);str+="|  ";str+=s_PlacePlayer(25,false,player);str+="  |";}
         else if(i==33){str+="|________|_|                                               /_________//            |_|________|";}
        else if(i==34){str+="| TUNIS  | |                                               \\\\\\\\\\\\\\\\\\\\/             | | LONDON |";}
         else if(i==35){str+="|  ";str+=s_PlacePlayer(1,true,player);str+="  |";str+=I2S(u_placeowner_changer(g.placeowner[1]));str+="|                                                                       |";str+=I2S(u_placeowner_changer(g.placeowner[26]));str+="|  ";str+=s_PlacePlayer(26,true,player);str+="  |";}
         else if(i==36){str+="|  ";str+=s_PlacePlayer(1,false,player);str+="  |";str+=I2S(g.placelevel[1]);str+="|                                                                       |";str+=I2S(g.placelevel[26]);str+="|  ";str+=s_PlacePlayer(26,false,player);str+="  |";}
         else if(i==37){str+="|________|_|_______________________________________________________________________|_|________|";}
        else if(i==38){str+="|          |__";str+=I2S(u_placeowner_changer(g.placeowner[35]));str+="__";str+=I2S(g.placelevel[35]);str+="__|________|__";str+=I2S(u_placeowner_changer(g.placeowner[33]));str+="__";str+=I2S(g.placelevel[33]);str+="__|________|__";str+=I2S(u_placeowner_changer(g.placeowner[31]));str+="__";str+=I2S(g.placelevel[31]);str+="__|__";str+=I2S(u_placeowner_changer(g.placeowner[30]));str+="__";str+=I2S(g.placelevel[30]);str+="__|________|__";str+=I2S(u_placeowner_changer(g.placeowner[28]));str+="__";str+=I2S(g.placelevel[28]);str+="__|          |";}
         else if(i==39){str+="|  START!  |  L.A.  |  TAX   |NEW YORK| EVENT  | SEOUL  | TOKYO  | CHANCE |BEIJING | AIRPORT! |";}
        else if(i==40){str+="|   ";str+=s_PlacePlayer(0,true,player);str+="   |  ";str+=s_PlacePlayer(35,true,player);str+="  |  ";str+=s_PlacePlayer(34,true,player);str+="  |  ";str+=s_PlacePlayer(33,true,player);str+="  |  ";str+=s_PlacePlayer(32,true,player);str+="  |  ";str+=s_PlacePlayer(31,true,player);str+="  |  ";str+=s_PlacePlayer(30,true,player);str+="  |  ";str+=s_PlacePlayer(29,true,player);str+="  |  ";str+=s_PlacePlayer(28,true,player);str+="  |   ";str+=s_PlacePlayer(27,true,player);str+="   |";}
         else if(i==41){str+="|   ";str+=s_PlacePlayer(0,false,player);str+="   |  ";str+=s_PlacePlayer(35,false,player);str+="  |  ";str+=s_PlacePlayer(34,false,player);str+="  |  ";str+=s_PlacePlayer(33,false,player);str+="  |  ";str+=s_PlacePlayer(32,false,player);str+="  |  ";str+=s_PlacePlayer(31,false,player);str+="  |  ";str+=s_PlacePlayer(30,false,player);str+="  |  ";str+=s_PlacePlayer(29,false,player);str+="  |  ";str+=s_PlacePlayer(28,false,player);str+="  |   ";str+=s_PlacePlayer(27,false,player);str+="   |";}
         else if(i==42){str+="|__________|________|________|________|________|________|________|________|________|__________|";}
        if(save==false){if(Animation==true){i++;cout<<str<<endl;str="";Sleep(d);}}
         else{i++;str+="\n";}
    }while(i<=42&&(Animation==true||save==true));
    return str;

}

double u_Round(double val){
    return ((double)((int)(val*100+0.5)/100.0));
}

void s_initializeData(GameData *g){

    //Place Type - 1.place 2.vacation 3.chance 4.event 5.special 6.casino 7.tax
    (*g).placetype[0]=5;
    (*g).placetype[1]=1;
    (*g).placetype[2]=6;
    (*g).placetype[3]=1;
    (*g).placetype[4]=2;
    (*g).placetype[5]=1;
    (*g).placetype[6]=3;
    (*g).placetype[7]=1;
    (*g).placetype[8]=1;
    (*g).placetype[9]=5;
    (*g).placetype[10]=1;
    (*g).placetype[11]=2;
    (*g).placetype[12]=1;
    (*g).placetype[13]=4;
    (*g).placetype[14]=1;
    (*g).placetype[15]=1;
    (*g).placetype[16]=3;
    (*g).placetype[17]=1;
    (*g).placetype[18]=5;
    (*g).placetype[19]=1;
    (*g).placetype[20]=2;
    (*g).placetype[21]=1;
    (*g).placetype[22]=4;
    (*g).placetype[23]=1;
    (*g).placetype[24]=2;
    (*g).placetype[25]=1;
    (*g).placetype[26]=1;
    (*g).placetype[27]=5;
    (*g).placetype[28]=1;
    (*g).placetype[29]=3;
    (*g).placetype[30]=1;
    (*g).placetype[31]=1;
    (*g).placetype[32]=4;
    (*g).placetype[33]=1;
    (*g).placetype[34]=7;
    (*g).placetype[35]=1;
    for(int i=0;i<36;i++){(*g).placeowner[i]=4;(*g).placelevel[i]=0;}
    //Price 0.buy 1.pay 2.sell 3.upgrade
    //sell is 180% of total upgrade fee
    //upgrade is 40% of current pay
    (*g).placeprice[0][0][0]=0;
    (*g).placeprice[0][0][1]=40;
    (*g).placeprice[0][0][2]=0;
    (*g).placeprice[0][0][3]=43;
    (*g).placeprice[0][0][4]=100;
    (*g).placeprice[0][0][5]=50;
    (*g).placeprice[0][0][6]=0;
    (*g).placeprice[0][0][7]=52;
    (*g).placeprice[0][0][8]=58;
    (*g).placeprice[0][0][9]=0;
    (*g).placeprice[0][0][10]=62;
    (*g).placeprice[0][0][11]=100;
    (*g).placeprice[0][0][12]=66;
    (*g).placeprice[0][0][13]=0;
    (*g).placeprice[0][0][14]=72;
    (*g).placeprice[0][0][15]=76;
    (*g).placeprice[0][0][16]=0;
    (*g).placeprice[0][0][17]=82;
    (*g).placeprice[0][0][18]=0;
    (*g).placeprice[0][0][19]=88;
    (*g).placeprice[0][0][20]=100;
    (*g).placeprice[0][0][21]=93;
    (*g).placeprice[0][0][22]=0;
    (*g).placeprice[0][0][23]=102;
    (*g).placeprice[0][0][24]=100;
    (*g).placeprice[0][0][25]=110;
    (*g).placeprice[0][0][26]=122;
    (*g).placeprice[0][0][27]=0;
    (*g).placeprice[0][0][28]=131;
    (*g).placeprice[0][0][29]=0;
    (*g).placeprice[0][0][30]=141;
    (*g).placeprice[0][0][31]=153;
    (*g).placeprice[0][0][32]=0;
    (*g).placeprice[0][0][33]=171;
    (*g).placeprice[0][0][34]=0;
    (*g).placeprice[0][0][35]=190;
    //Pay
    (*g).placeprice[1][1][0]=0;
    (*g).placeprice[1][1][1]=120;
    (*g).placeprice[1][1][2]=0;
    (*g).placeprice[1][1][3]=125;
    (*g).placeprice[1][1][4]=50;
    (*g).placeprice[1][1][5]=130;
    (*g).placeprice[1][1][6]=0;
    (*g).placeprice[1][1][7]=145;
    (*g).placeprice[1][1][8]=165;
    (*g).placeprice[1][1][9]=0;
    (*g).placeprice[1][1][10]=175;
    (*g).placeprice[1][1][11]=50;
    (*g).placeprice[1][1][12]=190;
    (*g).placeprice[1][1][13]=0;
    (*g).placeprice[1][1][14]=195;
    (*g).placeprice[1][1][15]=210;
    (*g).placeprice[1][1][16]=0;
    (*g).placeprice[1][1][17]=230;
    (*g).placeprice[1][1][18]=0;
    (*g).placeprice[1][1][19]=235;
    (*g).placeprice[1][1][20]=50;
    (*g).placeprice[1][1][21]=245;
    (*g).placeprice[1][1][22]=0;
    (*g).placeprice[1][1][23]=260;
    (*g).placeprice[1][1][24]=50;
    (*g).placeprice[1][1][25]=270;
    (*g).placeprice[1][1][26]=280;
    (*g).placeprice[1][1][27]=0;
    (*g).placeprice[1][1][28]=295;
    (*g).placeprice[1][1][29]=0;
    (*g).placeprice[1][1][30]=300;
    (*g).placeprice[1][1][31]=330;
    (*g).placeprice[1][1][32]=0;
    (*g).placeprice[1][1][33]=350;
    (*g).placeprice[1][1][34]=0;
    (*g).placeprice[1][1][35]=375;
    //Buy and upgrade
    for(int i=0;i<36;i++){
        (*g).placeprice[2][1][i]=u_Round((*g).placeprice[0][0][i]*1.8);//sell land
        (*g).placeprice[3][1][i]=u_Round((*g).placeprice[1][1][i]*0.4);//upgrade land to house
        (*g).placeprice[0][1][i]=u_Round((*g).placeprice[0][0][i]+(*g).placeprice[3][1][i]); //buy with house

        (*g).placeprice[1][2][i]=u_Round((*g).placeprice[1][1][i]*1.15);//pay house
        (*g).placeprice[2][2][i]=u_Round((*g).placeprice[0][1][i]*1.8);//sell house
        (*g).placeprice[3][2][i]=u_Round((*g).placeprice[1][2][i]*0.4);//upgrade house to inn
        (*g).placeprice[0][2][i]=u_Round((*g).placeprice[0][1][i]+(*g).placeprice[3][2][i]); //buy with inn

        (*g).placeprice[1][3][i]=u_Round((*g).placeprice[1][2][i]*1.4);//pay inn
        (*g).placeprice[2][3][i]=u_Round((*g).placeprice[0][2][i]*1.8);//sell inn
        (*g).placeprice[3][3][i]=u_Round((*g).placeprice[1][3][i]*0.4);//upgrade inn to hotel
        (*g).placeprice[0][3][i]=u_Round((*g).placeprice[0][2][i]+(*g).placeprice[3][3][i]); //buy with hotel

        (*g).placeprice[1][4][i]=u_Round((*g).placeprice[1][3][i]*1.7);//pay hotel
        (*g).placeprice[2][4][i]=u_Round((*g).placeprice[0][3][i]*1.8);//sell hotel
        (*g).placeprice[3][4][i]=u_Round((*g).placeprice[1][4][i]*0.4);//upgrade hotel to lm

        (*g).placeprice[1][5][i]=u_Round((*g).placeprice[1][4][i]*2.0);//pay landmark
        (*g).placeprice[3][5][i]=u_Round((*g).placeprice[1][5][i]*0.4);//upgrade landmark
    }
    //Buildings
    (*g).placename[0]="start";
    (*g).placename[1]="Tunis";
    (*g).placename[2]="Casino";
    (*g).placename[3]="Cairo";
    (*g).placename[4]="Guam";
    (*g).placename[5]="Bangkok";
    (*g).placename[6]="Chance";
    (*g).placename[7]="New Deli";
    (*g).placename[8]="Singarpore";
    (*g).placename[9]="Jail";
    (*g).placename[10]="Brasilia";
    (*g).placename[11]="Bali";
    (*g).placename[12]="Santiago";
    (*g).placename[13]="Event";
    (*g).placename[14]="Oslo";
    (*g).placename[15]="Stockholm";
    (*g).placename[16]="Chance";
    (*g).placename[17]="Moscow";
    (*g).placename[18]="Jackpot";
    (*g).placename[19]="Athens";
    (*g).placename[20]="Puerto Rico";
    (*g).placename[21]="Rome";
    (*g).placename[22]="Event";
    (*g).placename[23]="Berlin";
    (*g).placename[24]="Sicilia";
    (*g).placename[25]="Paris";
    (*g).placename[26]="London";
    (*g).placename[27]="Airport";
    (*g).placename[28]="Beijing";
    (*g).placename[29]="Chance";
    (*g).placename[30]="Tokyo";
    (*g).placename[31]="Seoul";
    (*g).placename[32]="Event";
    (*g).placename[33]="New York";
    (*g).placename[34]="Tax";
    (*g).placename[35]="Los Angeles";

    (*g).buildingname[0]="Unowned Land";
    (*g).buildingname[1]="Land";
    (*g).buildingname[2]="House";
    (*g).buildingname[3]="Inn";
    (*g).buildingname[4]="Hotel";
    (*g).buildingname[5]="Landmark";

    //cards 0-chance 1-event
    (*g).cardname[0][0][1]="Futures Trading";
    (*g).cardname[0][1][1]="When player visit and pay, player earn 150% from bank as player spend.";

    (*g).cardname[0][0][2]="Tax Evasion";
    (*g).cardname[0][1][2]="Player do not need to pay tax when player visit Tax Service.";

    (*g).cardname[0][0][3]="Jailbreak";
    (*g).cardname[0][1][3]="when player go to the jail with this card, player can come out from the jail immediately.";

    (*g).cardname[1][0][1]="Manipulation";
    (*g).cardname[1][1][1]="You have been accused of market manipulation. Go to jail.";

    (*g).cardname[1][0][2]="Lottery";
    (*g).cardname[1][1][2]="You win the lottery! Bank give u $400 immediately.";

    (*g).cardname[1][0][3]="Start Line";
    (*g).cardname[1][1][3]="Go to start line.";
    //letters
    (*g).letter[0][0][0]="          ";
    (*g).letter[0][0][1]="    /\\    ";
    (*g).letter[0][0][2]="   /  \\   ";
    (*g).letter[0][0][3]="  / /\\ \\  ";
    (*g).letter[0][0][4]=" / ____ \\ ";
    (*g).letter[0][0][5]="/_/    \\_\\";

    (*g).letter[0][1][0]=" ____  ";
    (*g).letter[0][1][1]="|  _ \\ ";
    (*g).letter[0][1][2]="| |_) |";
    (*g).letter[0][1][3]="|  _ < ";
    (*g).letter[0][1][4]="| |_) |";
    (*g).letter[0][1][5]="|____/ ";

    (*g).letter[0][2][0]="  _____ ";
    (*g).letter[0][2][1]=" / ____|";
    (*g).letter[0][2][2]="| |     ";
    (*g).letter[0][2][3]="| |     ";
    (*g).letter[0][2][4]="| |____ ";
    (*g).letter[0][2][5]=" \\_____|";

    (*g).letter[0][3][0]=" _____  ";
    (*g).letter[0][3][1]="|  __ \\ ";
    (*g).letter[0][3][2]="| |  | |";
    (*g).letter[0][3][3]="| |  | |";
    (*g).letter[0][3][4]="| |__| |";
    (*g).letter[0][3][5]="|_____/ ";

    (*g).letter[0][4][0]=" ______ ";
    (*g).letter[0][4][1]="|  ____|";
    (*g).letter[0][4][2]="| |__   ";
    (*g).letter[0][4][3]="|  __|  ";
    (*g).letter[0][4][4]="| |____ ";
    (*g).letter[0][4][5]="|______|";

    (*g).letter[0][5][0]=" ______ ";
    (*g).letter[0][5][1]="|  ____|";
    (*g).letter[0][5][2]="| |__   ";
    (*g).letter[0][5][3]="|  __|  ";
    (*g).letter[0][5][4]="| |     ";
    (*g).letter[0][5][5]="|_|     ";

    (*g).letter[0][6][0]="  _____ ";
    (*g).letter[0][6][1]=" / ____|";
    (*g).letter[0][6][2]="| |  __ ";
    (*g).letter[0][6][3]="| | |_ |";
    (*g).letter[0][6][4]="| |__| |";
    (*g).letter[0][6][5]=" \\_____|";

    (*g).letter[0][7][0]=" _    _ ";
    (*g).letter[0][7][1]="| |  | |";
    (*g).letter[0][7][2]="| |__| |";
    (*g).letter[0][7][3]="|  __  |";
    (*g).letter[0][7][4]="| |  | |";
    (*g).letter[0][7][5]="|_|  |_|";

    (*g).letter[0][8][0]=" _____ ";
    (*g).letter[0][8][1]="|_   _|";
    (*g).letter[0][8][2]="  | |  ";
    (*g).letter[0][8][3]="  | |  ";
    (*g).letter[0][8][4]=" _| |_ ";
    (*g).letter[0][8][5]="|_____|";

    (*g).letter[0][9][0]="      _ ";
    (*g).letter[0][9][1]="     | |";
    (*g).letter[0][9][2]="     | |";
    (*g).letter[0][9][3]=" _   | |";
    (*g).letter[0][9][4]="| |__| |";
    (*g).letter[0][9][5]=" \\____/ ";

    (*g).letter[0][10][0]=" _  __";
    (*g).letter[0][10][1]="| |/ /";
    (*g).letter[0][10][2]="| ' / ";
    (*g).letter[0][10][3]="|  <  ";
    (*g).letter[0][10][4]="| . \\ ";
    (*g).letter[0][10][5]="|_|\\_\\";

    (*g).letter[0][11][0]=" _      ";
    (*g).letter[0][11][1]="| |     ";
    (*g).letter[0][11][2]="| |     ";
    (*g).letter[0][11][3]="| |     ";
    (*g).letter[0][11][4]="| |____ ";
    (*g).letter[0][11][5]="|______|";

    (*g).letter[0][12][0]=" __  __ ";
    (*g).letter[0][12][1]="|  \\/  |";
    (*g).letter[0][12][2]="| \\  / |";
    (*g).letter[0][12][3]="| |\\/| |";
    (*g).letter[0][12][4]="| |  | |";
    (*g).letter[0][12][5]="|_|  |_|";

    (*g).letter[0][13][0]=" _   _ ";
    (*g).letter[0][13][1]="| \\ | |";
    (*g).letter[0][13][2]="|  \\| |";
    (*g).letter[0][13][3]="| . ` |";
    (*g).letter[0][13][4]="| |\\  |";
    (*g).letter[0][13][5]="|_| \\_|";

    (*g).letter[0][14][0]="  ____  ";
    (*g).letter[0][14][1]=" / __ \\ ";
    (*g).letter[0][14][2]="| |  | |";
    (*g).letter[0][14][3]="| |  | |";
    (*g).letter[0][14][4]="| |__| |";
    (*g).letter[0][14][5]=" \\____/ ";

    (*g).letter[0][15][0]=" _____  ";
    (*g).letter[0][15][1]="|  __ \\ ";
    (*g).letter[0][15][2]="| |__) |";
    (*g).letter[0][15][3]="|  ___/ ";
    (*g).letter[0][15][4]="| |     ";
    (*g).letter[0][15][5]="|_|     ";

    (*g).letter[0][16][0]="  ____  ";
    (*g).letter[0][16][1]=" / __ \\ ";
    (*g).letter[0][16][2]="| |  | |";
    (*g).letter[0][16][3]="| |  | |";
    (*g).letter[0][16][4]="| |__| |";
    (*g).letter[0][16][5]=" \\___\\_\\";

    (*g).letter[0][17][0]=" _____  ";
    (*g).letter[0][17][1]="|  __ \\ ";
    (*g).letter[0][17][2]="| |__) |";
    (*g).letter[0][17][3]="|  _  / ";
    (*g).letter[0][17][4]="| | \\ \\ ";
    (*g).letter[0][17][5]="|_|  \\_\\";

    (*g).letter[0][18][0]="  _____ ";
    (*g).letter[0][18][1]=" / ____|";
    (*g).letter[0][18][2]="| (___  ";
    (*g).letter[0][18][3]=" \\___ \\ ";
    (*g).letter[0][18][4]=" ____) |";
    (*g).letter[0][18][5]="|_____/ ";

    (*g).letter[0][19][0]=" _______ ";
    (*g).letter[0][19][1]="|__   __|";
    (*g).letter[0][19][2]="   | |   ";
    (*g).letter[0][19][3]="   | |   ";
    (*g).letter[0][19][4]="   | |   ";
    (*g).letter[0][19][5]="   |_|   ";

    (*g).letter[0][20][0]=" _    _ ";
    (*g).letter[0][20][1]="| |  | |";
    (*g).letter[0][20][2]="| |  | |";
    (*g).letter[0][20][3]="| |  | |";
    (*g).letter[0][20][4]="| |__| |";
    (*g).letter[0][20][5]=" \\____/ ";

    (*g).letter[0][21][0]="__      __";
    (*g).letter[0][21][1]="\\ \\    / /";
    (*g).letter[0][21][2]=" \\ \\  / / ";
    (*g).letter[0][21][3]="  \\ \\/ /  ";
    (*g).letter[0][21][4]="   \\  /   ";
    (*g).letter[0][21][5]="    \\/    ";

    (*g).letter[0][22][0]="__          __";
    (*g).letter[0][22][1]="\\ \\        / /";
    (*g).letter[0][22][2]=" \\ \\  /\\  / / ";
    (*g).letter[0][22][3]="  \\ \\/  \\/ /  ";
    (*g).letter[0][22][4]="   \\  /\\  /   ";
    (*g).letter[0][22][5]="    \\/  \\/    ";

    (*g).letter[0][23][0]="__   __";
    (*g).letter[0][23][1]="\\ \\ / /";
    (*g).letter[0][23][2]=" \\ V / ";
    (*g).letter[0][23][3]="  > <  ";
    (*g).letter[0][23][4]=" / . \\ ";
    (*g).letter[0][23][5]="/_/ \\_\\";

    (*g).letter[0][24][0]="__     __";
    (*g).letter[0][24][1]="\\ \\   / /";
    (*g).letter[0][24][2]=" \\ \\_/ / ";
    (*g).letter[0][24][3]="  \\   /  ";
    (*g).letter[0][24][4]="   | |   ";
    (*g).letter[0][24][5]="   |_|   ";

    (*g).letter[0][25][0]=" ______";
    (*g).letter[0][25][1]="|___  /";
    (*g).letter[0][25][2]="   / / ";
    (*g).letter[0][25][3]="  / /  ";
    (*g).letter[0][25][4]=" / /__ ";
    (*g).letter[0][25][5]="/_____|";

    (*g).letter[1][0][0]="       ";
    (*g).letter[1][0][1]="       ";
    (*g).letter[1][0][2]="  __ _ ";
    (*g).letter[1][0][3]=" / _` |";
    (*g).letter[1][0][4]="| (_| |";
    (*g).letter[1][0][5]=" \\__,_|";

    (*g).letter[1][1][0]=" _     ";
    (*g).letter[1][1][1]="| |    ";
    (*g).letter[1][1][2]="| |__  ";
    (*g).letter[1][1][3]="| '_ \\ ";
    (*g).letter[1][1][4]="| |_) |";
    (*g).letter[1][1][5]="|_.__/ ";

    (*g).letter[1][2][0]="      ";
    (*g).letter[1][2][1]="      ";
    (*g).letter[1][2][2]="  ___ ";
    (*g).letter[1][2][3]=" / __|";
    (*g).letter[1][2][4]="| (__ ";
    (*g).letter[1][2][5]=" \\___|";

    (*g).letter[1][3][0]="     _ ";
    (*g).letter[1][3][1]="    | |";
    (*g).letter[1][3][2]="  __| |";
    (*g).letter[1][3][3]=" / _` |";
    (*g).letter[1][3][4]="| (_| |";
    (*g).letter[1][3][5]=" \\__,_|";

    (*g).letter[1][4][0]="      ";
    (*g).letter[1][4][1]="      ";
    (*g).letter[1][4][2]="  ___ ";
    (*g).letter[1][4][3]=" / _ \\";
    (*g).letter[1][4][4]="|  __/";
    (*g).letter[1][4][5]=" \\___|";

    (*g).letter[1][5][0]="  __ ";
    (*g).letter[1][5][1]=" / _|";
    (*g).letter[1][5][2]="| |_ ";
    (*g).letter[1][5][3]="|  _|";
    (*g).letter[1][5][4]="| |  ";
    (*g).letter[1][5][5]="|_|  ";

    (*g).letter[1][6][0]="  __ _ ";
    (*g).letter[1][6][1]=" / _` |";
    (*g).letter[1][6][2]="| (_| |";
    (*g).letter[1][6][3]=" \\__, |";
    (*g).letter[1][6][4]="  __/ |";
    (*g).letter[1][6][5]=" |___/ ";

    (*g).letter[1][7][0]=" _     ";
    (*g).letter[1][7][1]="| |    ";
    (*g).letter[1][7][2]="| |__  ";
    (*g).letter[1][7][3]="| '_ \\ ";
    (*g).letter[1][7][4]="| | | |";
    (*g).letter[1][7][5]="|_| |_|";

    (*g).letter[1][8][0]=" _ ";
    (*g).letter[1][8][1]="(_)";
    (*g).letter[1][8][2]=" _ ";
    (*g).letter[1][8][3]="| |";
    (*g).letter[1][8][4]="| |";
    (*g).letter[1][8][5]="|_|";

    (*g).letter[1][9][0]="    _ ";
    (*g).letter[1][9][1]="   (_)";
    (*g).letter[1][9][2]="    _ ";
    (*g).letter[1][9][3]="   | |";
    (*g).letter[1][9][4]=" __/ |";
    (*g).letter[1][9][5]="|___/ ";

    (*g).letter[1][10][0]=" _    ";
    (*g).letter[1][10][1]="| |   ";
    (*g).letter[1][10][2]="| | __";
    (*g).letter[1][10][3]="| |/ /";
    (*g).letter[1][10][4]="|   < ";
    (*g).letter[1][10][5]="|_|\\_\\";

    (*g).letter[1][11][0]=" _ ";
    (*g).letter[1][11][1]="| |";
    (*g).letter[1][11][2]="| |";
    (*g).letter[1][11][3]="| |";
    (*g).letter[1][11][4]="| |";
    (*g).letter[1][11][5]="|_|";

    (*g).letter[1][12][0]="           ";
    (*g).letter[1][12][1]="           ";
    (*g).letter[1][12][2]=" _ __ ___  ";
    (*g).letter[1][12][3]="| '_ ` _ \\ ";
    (*g).letter[1][12][4]="| | | | | |";
    (*g).letter[1][12][5]="|_| |_| |_|";

    (*g).letter[1][13][0]="       ";
    (*g).letter[1][13][1]="       ";
    (*g).letter[1][13][2]=" _ __  ";
    (*g).letter[1][13][3]="| '_ \\ ";
    (*g).letter[1][13][4]="| | | |";
    (*g).letter[1][13][5]="|_| |_|";

    (*g).letter[1][14][0]="       ";
    (*g).letter[1][14][1]="       ";
    (*g).letter[1][14][2]="  ___  ";
    (*g).letter[1][14][3]=" / _ \\ ";
    (*g).letter[1][14][4]="| (_) |";
    (*g).letter[1][14][5]=" \\___/ ";

    (*g).letter[1][15][0]=" _ __  ";
    (*g).letter[1][15][1]="| '_ \\ ";
    (*g).letter[1][15][2]="| |_) |";
    (*g).letter[1][15][3]="| .__/ ";
    (*g).letter[1][15][4]="| |    ";
    (*g).letter[1][15][5]="|_|    ";

    (*g).letter[1][16][0]="  __ _ ";
    (*g).letter[1][16][1]=" / _` |";
    (*g).letter[1][16][2]="| (_| |";
    (*g).letter[1][16][3]=" \\__, |";
    (*g).letter[1][16][4]="    | |";
    (*g).letter[1][16][5]="    |_|";

    (*g).letter[1][17][0]="      ";
    (*g).letter[1][17][1]="      ";
    (*g).letter[1][17][2]=" _ __ ";
    (*g).letter[1][17][3]="| '__|";
    (*g).letter[1][17][4]="| |   ";
    (*g).letter[1][17][5]="|_|   ";

    (*g).letter[1][18][0]="     ";
    (*g).letter[1][18][1]="     ";
    (*g).letter[1][18][2]=" ___ ";
    (*g).letter[1][18][3]="/ __|";
    (*g).letter[1][18][4]="\\__ \\";
    (*g).letter[1][18][5]="|___/";

    (*g).letter[1][19][0]=" _   ";
    (*g).letter[1][19][1]="| |  ";
    (*g).letter[1][19][2]="| |_ ";
    (*g).letter[1][19][3]="| __|";
    (*g).letter[1][19][4]="| |_ ";
    (*g).letter[1][19][5]=" \\__|";

    (*g).letter[1][20][0]="       ";
    (*g).letter[1][20][1]="       ";
    (*g).letter[1][20][2]=" _   _ ";
    (*g).letter[1][20][3]="| | | |";
    (*g).letter[1][20][4]="| |_| |";
    (*g).letter[1][20][5]=" \\__,_|";

    (*g).letter[1][21][0]="       ";
    (*g).letter[1][21][1]="       ";
    (*g).letter[1][21][2]="__   __";
    (*g).letter[1][21][3]="\\ \\ / /";
    (*g).letter[1][21][4]=" \\ V / ";
    (*g).letter[1][21][5]="  \\_/  ";

    (*g).letter[1][22][0]="          ";
    (*g).letter[1][22][1]="          ";
    (*g).letter[1][22][2]="__      __";
    (*g).letter[1][22][3]="\\ \\ /\\ / /";
    (*g).letter[1][22][4]=" \\ V  V / ";
    (*g).letter[1][22][5]="  \\_/\\_/  ";

    (*g).letter[1][23][0]="      ";
    (*g).letter[1][23][1]="      ";
    (*g).letter[1][23][2]="__  __";
    (*g).letter[1][23][3]="\\ \\/ /";
    (*g).letter[1][23][4]=" >  < ";
    (*g).letter[1][23][5]="/_/\\_\\";

    (*g).letter[1][24][0]=" _   _ ";
    (*g).letter[1][24][1]="| | | |";
    (*g).letter[1][24][2]="| |_| |";
    (*g).letter[1][24][3]=" \\__, |";
    (*g).letter[1][24][4]="  __/ |";
    (*g).letter[1][24][5]=" |___/ ";

    (*g).letter[1][25][0]="     ";
    (*g).letter[1][25][1]="     ";
    (*g).letter[1][25][2]=" ____";
    (*g).letter[1][25][3]="|_  /";
    (*g).letter[1][25][4]=" / / ";
    (*g).letter[1][25][5]="/___|";

    (*g).letter[2][1][0]=" __ ";
    (*g).letter[2][1][1]="/_ |";
    (*g).letter[2][1][2]=" | |";
    (*g).letter[2][1][3]=" | |";
    (*g).letter[2][1][4]=" | |";
    (*g).letter[2][1][5]=" |_|";

    (*g).letter[2][2][0]=" ___  ";
    (*g).letter[2][2][1]="|__ \\ ";
    (*g).letter[2][2][2]="   ) |";
    (*g).letter[2][2][3]="  / / ";
    (*g).letter[2][2][4]=" / /_ ";
    (*g).letter[2][2][5]="|____|";

    (*g).letter[2][3][0]=" ____  ";
    (*g).letter[2][3][1]="|___ \\ ";
    (*g).letter[2][3][2]="  __) |";
    (*g).letter[2][3][3]=" |__ < ";
    (*g).letter[2][3][4]=" ___) |";
    (*g).letter[2][3][5]="|____/ ";

    (*g).letter[2][4][0]=" _  _   ";
    (*g).letter[2][4][1]="| || |  ";
    (*g).letter[2][4][2]="| || |_ ";
    (*g).letter[2][4][3]="|__   _|";
    (*g).letter[2][4][4]="   | |  ";
    (*g).letter[2][4][5]="   |_|  ";

    (*g).letter[2][5][0]=" _____ ";
    (*g).letter[2][5][1]="| ____|";
    (*g).letter[2][5][2]="| |__  ";
    (*g).letter[2][5][3]="|___ \\ ";
    (*g).letter[2][5][4]=" ___) |";
    (*g).letter[2][5][5]="|____/ ";

    (*g).letter[2][6][0]="   __  ";
    (*g).letter[2][6][1]="  / /  ";
    (*g).letter[2][6][2]=" / /_  ";
    (*g).letter[2][6][3]="| '_ \\ ";
    (*g).letter[2][6][4]="| (_) |";
    (*g).letter[2][6][5]=" \\___/ ";

    (*g).letter[2][7][0]=" ______ ";
    (*g).letter[2][7][1]="|____  |";
    (*g).letter[2][7][2]="    / / ";
    (*g).letter[2][7][3]="   / /  ";
    (*g).letter[2][7][4]="  / /   ";
    (*g).letter[2][7][5]=" /_/    ";

    (*g).letter[2][8][0]="  ___  ";
    (*g).letter[2][8][1]=" / _ \\ ";
    (*g).letter[2][8][2]="| (_) |";
    (*g).letter[2][8][3]=" > _ < ";
    (*g).letter[2][8][4]="| (_) |";
    (*g).letter[2][8][5]=" \\___/ ";

    (*g).letter[2][9][0]="  ___  ";
    (*g).letter[2][9][1]=" / _ \\ ";
    (*g).letter[2][9][2]="| (_) |";
    (*g).letter[2][9][3]=" \\__, |";
    (*g).letter[2][9][4]="   / / ";
    (*g).letter[2][9][5]="  /_/  ";

    (*g).letter[2][0][0]="  ___  ";
    (*g).letter[2][0][1]=" / _ \\ ";
    (*g).letter[2][0][2]="| | | |";
    (*g).letter[2][0][3]="| | | |";
    (*g).letter[2][0][4]="| |_| |";
    (*g).letter[2][0][5]=" \\___/ ";

    (*g).letter[3][0][0]="     ";
    (*g).letter[3][0][1]="     ";
    (*g).letter[3][0][2]="     ";
    (*g).letter[3][0][3]="     ";
    (*g).letter[3][0][4]="     ";
    (*g).letter[3][0][5]="     ";


    //Image
    (*g).buildingimage[0][0]="|                                        _     |";
    (*g).buildingimage[0][1]="|                                       (_)    |";
    (*g).buildingimage[0][2]="|                                              |";
    (*g).buildingimage[0][3]="|                                              |";
    (*g).buildingimage[0][4]="|                                              |";
    (*g).buildingimage[0][5]="|                                              |";
    (*g).buildingimage[0][6]="|                                              |";
    (*g).buildingimage[0][7]="|                                              |";
    (*g).buildingimage[0][8]="|______________________________________________|";
    (*g).buildingimage[0][9]="|                                              |";


    (*g).buildingimage[1][0]="|                                              |";
    (*g).buildingimage[1][1]="|                      |                       |";
    (*g).buildingimage[1][2]="|                    \\ _ /                     |";
    (*g).buildingimage[1][3]="|                  -= (_) =-                   |";
    (*g).buildingimage[1][4]="|                    /   \\         _\\/_        |";
    (*g).buildingimage[1][5]="|                      |           //o\\  _\\/_  |";
    (*g).buildingimage[1][6]="| __ ____ _ ___ _____ _ __ __ ____ _ | __/o\\\\ _|";
    (*g).buildingimage[1][7]="| _ -==- __=- =-=-_-__=_-= _=_=-=_,-'|\"'\"\"-|-,_|";
    (*g).buildingimage[1][8]="| =- _=- -=-=- =- _=-=- -_=-=_,-\"          |   |";
    (*g).buildingimage[1][9]="| - -= =- =- -=- =- =- -=.--\"                  |";


    (*g).buildingimage[2][0]="|                                              |";
    (*g).buildingimage[2][1]="|              ____________________            |";
    (*g).buildingimage[2][2]="|             /                    \\           |";
    (*g).buildingimage[2][3]="|            /           /_\\        \\          |";
    (*g).buildingimage[2][4]="|           /_ _________//_\\\\______ _\\         |";
    (*g).buildingimage[2][5]="|             |        ___    ___  |           |";
    (*g).buildingimage[2][6]="|             |  __   |_|_|  |_|_| |           |";
    (*g).buildingimage[2][7]="|             | |  |  |_|_|  |_|_| |           |";
    (*g).buildingimage[2][8]="|             | |. |               |           |";
    (*g).buildingimage[2][9]="|_____________|_|__|_______________|___________|";

    (*g).buildingimage[3][0]="|                                              |";
    (*g).buildingimage[3][1]="|   _+___+___+___+___+___+___+___+___+___+___  |";
    (*g).buildingimage[3][2]="|  |  ___       ___       ___       ___      | |";
    (*g).buildingimage[3][3]="|  | |_|_|  _  |_|_|  _  |_|_|  _  |_|_|  _  | |";
    (*g).buildingimage[3][4]="|  | |_|_| |.| |_|_| |.| |_|_| |.| |_|_| |.| | |";
    (*g).buildingimage[3][5]="|  |_______|_|_______|_|_______|_|_______|_|_| |";
    (*g).buildingimage[3][6]="|  |  ___       ___       ___    \\_\\_        | |";
    (*g).buildingimage[3][7]="|  | |_|_|  _  |_|_|  _  |_|_|  _  \\_\\_      | |";
    (*g).buildingimage[3][8]="|  | |_|_| |.| |_|_| |.| |_|_| |.|   \\_\\_    | |";
    (*g).buildingimage[3][9]="|__|_______|_|_______|_|_______|_|_____\\_\\__ |_|";

    (*g).buildingimage[4][0]="|   _____        ____|__ |__||__||__________   |";
    (*g).buildingimage[4][1]="|  | ___ |      | _ _ _ ||__||__|| _      _ |  |";
    (*g).buildingimage[4][2]="|  ||___||___   ||_|_|_|| __  __ ||_| ___|_||__|";
    (*g).buildingimage[4][3]="|  | ___ | _ |  ||_|_|_|||__||__|| _ | _ __  _ |";
    (*g).buildingimage[4][4]="|  ||___|||_||  |  _____||__||__|||_|||_|__||_||";
    (*g).buildingimage[4][5]="|  | ___ ||_||  | | _  _  _ ||__|| _ | __  _ _ |";
    (*g).buildingimage[4][6]="|  ||___|||_||  | ||_||_||_|| __ ||_|||__||_|_||";
    (*g).buildingimage[4][7]="|  | ___ ||_||__| | _  _  _ ||__|| _ | _  _  _ |";
    (*g).buildingimage[4][8]="|  ||___|||_||  | ||_||_||_|||__|||_|||_||_||_||";
    (*g).buildingimage[4][9]="|__|_____|___|__|_|_________|____|___|_________|";

    (*g).buildingimage[5][0]="| :_\\/_:   .    .:.*_\\/_*   : /\\ :  .'.:.'.    |";
    (*g).buildingimage[5][1]="|.: /\\ : _\\(/_  ':'* /\\ *  : '..'.  -=:o:=-    |";
    (*g).buildingimage[5][2]="|_:'.:::. /)\\*''*  .|.* '.\\'/.'_\\(/_'.':'.'    |";
    (*g).buildingimage[5][3]="| : :::::  '*_\\/_* | |  -= o =- /)\\    '  *    |";
    (*g).buildingimage[5][4]="|'  ':::'   * /\\ * |'|  .'/.\\'.  '._____       |";
    (*g).buildingimage[5][5]="| *        __*..* |  |     :      |.   |' .---\"|";
    (*g).buildingimage[5][6]="|  _*   .-'   '-. |  |     .--'|  ||   | _|    |";
    (*g).buildingimage[5][7]="|-'|  _.|  |    ||   '-__  |   |  |    ||      |";
    (*g).buildingimage[5][8]="|' | |.    |    ||       | |   |  |    ||      |";
    (*g).buildingimage[5][9]="|  '-'     '    \"\"       '-'   '-.'    '`      |";
}




/*
 *
string[3][26][6]
    letter[0][0][0]="           ";
    letter[0][0][1]="     /\    ";
    letter[0][0][2]="    /  \   ";
    letter[0][0][3]="   / /\ \  ";
    letter[0][0][4]="  / ____ \ ";
    letter[0][0][5]=" /_/    \_\";

    letter[0][1][0]="  ____  ";
    letter[0][1][1]=" |  _ \ ";
    letter[0][1][2]=" | |_) |";
    letter[0][1][3]=" |  _ < ";
    letter[0][1][4]=" | |_) |";
    letter[0][1][5]=" |____/ ";

    letter[0][2][0]="   _____ ";
    letter[0][2][1]="  / ____|";
    letter[0][2][2]=" | |     ";
    letter[0][2][3]=" | |     ";
    letter[0][2][4]=" | |____ ";
    letter[0][2][5]="  \_____|";

    letter[0][3][0]="  _____  ";
    letter[0][3][1]=" |  __ \ ";
    letter[0][3][2]=" | |  | |";
    letter[0][3][3]=" | |  | |";
    letter[0][3][4]=" | |__| |";
    letter[0][3][5]=" |_____/ ";

    letter[0][4][0]="  ______ ";
    letter[0][4][1]=" |  ____|";
    letter[0][4][2]=" | |__   ";
    letter[0][4][3]=" |  __|  ";
    letter[0][4][4]=" | |____ ";
    letter[0][4][5]=" |______|";

    letter[0][5][0]="  ______ ";
    letter[0][5][1]=" |  ____|";
    letter[0][5][2]=" | |__   ";
    letter[0][5][3]=" |  __|  ";
    letter[0][5][4]=" | |     ";
    letter[0][5][5]=" |_|     ";

    letter[0][6][0]="   _____ ";
    letter[0][6][1]="  / ____|";
    letter[0][6][2]=" | |  __ ";
    letter[0][6][3]=" | | |_ |";
    letter[0][6][4]=" | |__| |";
    letter[0][6][5]="  \_____|";

    letter[0][7][0]="  _    _ ";
    letter[0][7][1]=" | |  | |";
    letter[0][7][2]=" | |__| |";
    letter[0][7][3]=" |  __  |";
    letter[0][7][4]=" | |  | |";
    letter[0][7][5]=" |_|  |_|";

    letter[0][8][0]="  _____ ";
    letter[0][8][1]=" |_   _|";
    letter[0][8][2]="   | |  ";
    letter[0][8][3]="   | |  ";
    letter[0][8][4]="  _| |_ ";
    letter[0][8][5]=" |_____|";

    letter[0][9][0]="       _ ";
    letter[0][9][1]="      | |";
    letter[0][9][2]="      | |";
    letter[0][9][3]="  _   | |";
    letter[0][9][4]=" | |__| |";
    letter[0][9][5]="  \____/ ";

    letter[0][10][0]="  _  __";
    letter[0][10][1]=" | |/ /";
    letter[0][10][2]=" | ' / ";
    letter[0][10][3]=" |  <  ";
    letter[0][10][4]=" | . \ ";
    letter[0][10][5]=" |_|\_\";

    letter[0][11][0]="  _      ";
    letter[0][11][1]=" | |     ";
    letter[0][11][2]=" | |     ";
    letter[0][11][3]=" | |     ";
    letter[0][11][4]=" | |____ ";
    letter[0][11][5]=" |______|";

    letter[0][12][0]="  __  __ ";
    letter[0][12][1]=" |  \/  |";
    letter[0][12][2]=" | \  / |";
    letter[0][12][3]=" | |\/| |";
    letter[0][12][4]=" | |  | |";
    letter[0][12][5]=" |_|  |_|";

    letter[0][13][0]="  _   _ ";
    letter[0][13][1]=" | \ | |";
    letter[0][13][2]=" |  \| |";
    letter[0][13][3]=" | . ` |";
    letter[0][13][4]=" | |\  |";
    letter[0][13][5]=" |_| \_|";

    letter[0][14][0]="   ____  ";
    letter[0][14][1]="  / __ \ ";
    letter[0][14][2]=" | |  | |";
    letter[0][14][3]=" | |  | |";
    letter[0][14][4]=" | |__| |";
    letter[0][14][5]="  \____/ ";

    letter[0][15][0]="  _____  ";
    letter[0][15][1]=" |  __ \ ";
    letter[0][15][2]=" | |__) |";
    letter[0][15][3]=" |  ___/ ";
    letter[0][15][4]=" | |     ";
    letter[0][15][5]=" |_|     ";

    letter[0][16][0]="   ____  ";
    letter[0][16][1]="  / __ \ ";
    letter[0][16][2]=" | |  | |";
    letter[0][16][3]=" | |  | |";
    letter[0][16][4]=" | |__| |";
    letter[0][16][5]="  \___\_\";

    letter[0][17][0]="  _____  ";
    letter[0][17][1]=" |  __ \ ";
    letter[0][17][2]=" | |__) |";
    letter[0][17][3]=" |  _  / ";
    letter[0][17][4]=" | | \ \ ";
    letter[0][17][5]=" |_|  \_\";

    letter[0][18][0]="   _____ ";
    letter[0][18][1]="  / ____|";
    letter[0][18][2]=" | (___  ";
    letter[0][18][3]="  \___ \ ";
    letter[0][18][4]="  ____) |";
    letter[0][18][5]=" |_____/ ";

    letter[0][19][0]="  _______ ";
    letter[0][19][1]=" |__   __|";
    letter[0][19][2]="    | |   ";
    letter[0][19][3]="    | |   ";
    letter[0][19][4]="    | |   ";
    letter[0][19][5]="    |_|   ";

    letter[0][20][0]="  _    _ ";
    letter[0][20][1]=" | |  | |";
    letter[0][20][2]=" | |  | |";
    letter[0][20][3]=" | |  | |";
    letter[0][20][4]=" | |__| |";
    letter[0][20][5]="  \____/ ";

    letter[0][21][0]=" __      __";
    letter[0][21][1]=" \ \    / /";
    letter[0][21][2]="  \ \  / / ";
    letter[0][21][3]="   \ \/ /  ";
    letter[0][21][4]="    \  /   ";
    letter[0][21][5]="     \/    ";

    letter[0][22][0]=" __          __";
    letter[0][22][1]=" \ \        / /";
    letter[0][22][2]="  \ \  /\  / / ";
    letter[0][22][3]="   \ \/  \/ /  ";
    letter[0][22][4]="    \  /\  /   ";
    letter[0][22][5]="     \/  \/    ";

    letter[0][23][0]=" __   __";
    letter[0][23][1]=" \ \ / /";
    letter[0][23][2]="  \ V / ";
    letter[0][23][3]="   > <  ";
    letter[0][23][4]="  / . \ ";
    letter[0][23][5]=" /_/ \_\";

    letter[0][24][0]=" __     __";
    letter[0][24][1]=" \ \   / /";
    letter[0][24][2]="  \ \_/ / ";
    letter[0][24][3]="   \   /  ";
    letter[0][24][4]="    | |   ";
    letter[0][24][5]="    |_|   ";

    letter[0][25][0]="  ______";
    letter[0][25][1]=" |___  /";
    letter[0][25][2]="    / / ";
    letter[0][25][3]="   / /  ";
    letter[0][25][4]="  / /__ ";
    letter[0][25][5]=" /_____|";

    letter[1][0][0]="        ";
    letter[1][0][1]="        ";
    letter[1][0][2]="   __ _ ";
    letter[1][0][3]="  / _` |";
    letter[1][0][4]=" | (_| |";
    letter[1][0][5]="  \__,_|";

    letter[1][1][0]="  _     ";
    letter[1][1][1]=" | |    ";
    letter[1][1][2]=" | |__  ";
    letter[1][1][3]=" | '_ \ ";
    letter[1][1][4]=" | |_) |";
    letter[1][1][5]=" |_.__/ ";

    letter[1][2][0]="       ";
    letter[1][2][1]="       ";
    letter[1][2][2]="   ___ ";
    letter[1][2][3]="  / __|";
    letter[1][2][4]=" | (__ ";
    letter[1][2][5]="  \___|";

    letter[1][3][0]="      _ ";
    letter[1][3][1]="     | |";
    letter[1][3][2]="   __| |";
    letter[1][3][3]="  / _` |";
    letter[1][3][4]=" | (_| |";
    letter[1][3][5]="  \__,_|";

    letter[1][4][0]="       ";
    letter[1][4][1]="       ";
    letter[1][4][2]="   ___ ";
    letter[1][4][3]="  / _ \";
    letter[1][4][4]=" |  __/";
    letter[1][4][5]="  \___|";

    letter[1][5][0]="   __ ";
    letter[1][5][1]="  / _|";
    letter[1][5][2]=" | |_ ";
    letter[1][5][3]=" |  _|";
    letter[1][5][4]=" | |  ";
    letter[1][5][5]=" |_|  ";

    letter[1][6][0]="   __ _ ";
    letter[1][6][1]="  / _` |";
    letter[1][6][2]=" | (_| |";
    letter[1][6][3]="  \__, |";
    letter[1][6][4]="   __/ |";
    letter[1][6][5]="  |___/ ";

    letter[1][7][0]="  _     ";
    letter[1][7][1]=" | |    ";
    letter[1][7][2]=" | |__  ";
    letter[1][7][3]=" | '_ \ ";
    letter[1][7][4]=" | | | |";
    letter[1][7][5]=" |_| |_|";

    letter[1][8][0]="  _ ";
    letter[1][8][1]=" (_)";
    letter[1][8][2]="  _ ";
    letter[1][8][3]=" | |";
    letter[1][8][4]=" | |";
    letter[1][8][5]=" |_|";

    letter[1][9][0]="     _ ";
    letter[1][9][1]="    (_)";
    letter[1][9][2]="     _ ";
    letter[1][9][3]="    | |";
    letter[1][9][4]="  __/ |";
    letter[1][9][5]=" |___/ ";

    letter[1][10][0]="  _    ";
    letter[1][10][1]=" | |   ";
    letter[1][10][2]=" | | __";
    letter[1][10][3]=" | |/ /";
    letter[1][10][4]=" |   < ";
    letter[1][10][5]=" |_|\_\";

    letter[1][11][0]="  _ ";
    letter[1][11][1]=" | |";
    letter[1][11][2]=" | |";
    letter[1][11][3]=" | |";
    letter[1][11][4]=" | |";
    letter[1][11][5]=" |_|";

    letter[1][12][0]="            ";
    letter[1][12][1]="            ";
    letter[1][12][2]="  _ __ ___  ";
    letter[1][12][3]=" | '_ ` _ \ ";
    letter[1][12][4]=" | | | | | |";
    letter[1][12][5]=" |_| |_| |_|";

    letter[1][13][0]="        ";
    letter[1][13][1]="        ";
    letter[1][13][2]="  _ __  ";
    letter[1][13][3]=" | '_ \ ";
    letter[1][13][4]=" | | | |";
    letter[1][13][5]=" |_| |_|";

    letter[1][14][0]="        ";
    letter[1][14][1]="        ";
    letter[1][14][2]="   ___  ";
    letter[1][14][3]="  / _ \ ";
    letter[1][14][4]=" | (_) |";
    letter[1][14][5]="  \___/ ";

    letter[1][15][0]="  _ __  ";
    letter[1][15][1]=" | '_ \ ";
    letter[1][15][2]=" | |_) |";
    letter[1][15][3]=" | .__/ ";
    letter[1][15][4]=" | |    ";
    letter[1][15][5]=" |_|    ";

    letter[1][16][0]="   __ _ ";
    letter[1][16][1]="  / _` |";
    letter[1][16][2]=" | (_| |";
    letter[1][16][3]="  \__, |";
    letter[1][16][4]="     | |";
    letter[1][16][5]="     |_|";

    letter[1][17][0]="       ";
    letter[1][17][1]="       ";
    letter[1][17][2]="  _ __ ";
    letter[1][17][3]=" | '__|";
    letter[1][17][4]=" | |   ";
    letter[1][17][5]=" |_|   ";

    letter[1][18][0]="      ";
    letter[1][18][1]="      ";
    letter[1][18][2]="  ___ ";
    letter[1][18][3]=" / __|";
    letter[1][18][4]=" \__ \";
    letter[1][18][5]=" |___/";

    letter[1][19][0]="  _   ";
    letter[1][19][1]=" | |  ";
    letter[1][19][2]=" | |_ ";
    letter[1][19][3]=" | __|";
    letter[1][19][4]=" | |_ ";
    letter[1][19][5]="  \__|";

    letter[1][20][0]="        ";
    letter[1][20][1]="        ";
    letter[1][20][2]="  _   _ ";
    letter[1][20][3]=" | | | |";
    letter[1][20][4]=" | |_| |";
    letter[1][20][5]="  \__,_|";

    letter[1][21][0]="        ";
    letter[1][21][1]="        ";
    letter[1][21][2]=" __   __";
    letter[1][21][3]=" \ \ / /";
    letter[1][21][4]="  \ V / ";
    letter[1][21][5]="   \_/  ";

    letter[1][22][0]="           ";
    letter[1][22][1]="           ";
    letter[1][22][2]=" __      __";
    letter[1][22][3]=" \ \ /\ / /";
    letter[1][22][4]="  \ V  V / ";
    letter[1][22][5]="   \_/\_/  ";

    letter[1][23][0]="       ";
    letter[1][23][1]="       ";
    letter[1][23][2]=" __  __";
    letter[1][23][3]=" \ \/ /";
    letter[1][23][4]="  >  < ";
    letter[1][23][5]=" /_/\_\";

    letter[0][24][0]="  _   _ ";
    letter[0][24][1]=" | | | |";
    letter[0][24][2]=" | |_| |";
    letter[0][24][3]="  \__, |";
    letter[0][24][4]="   __/ |";
    letter[0][24][5]="  |___/ ";

    letter[0][25][0]="      ";
    letter[0][25][1]="      ";
    letter[0][25][2]="  ____";
    letter[0][25][3]=" |_  /";
    letter[0][25][4]="  / / ";
    letter[0][25][5]=" /___|";

    letter[2][0][0]="  __ ";
    letter[2][0][1]=" /_ |";
    letter[2][0][2]="  | |";
    letter[2][0][3]="  | |";
    letter[2][0][4]="  | |";
    letter[2][0][5]="  |_|";

    letter[2][1][0]="  ___  ";
    letter[2][1][1]=" |__ \ ";
    letter[2][1][2]="    ) |";
    letter[2][1][3]="   / / ";
    letter[2][1][4]="  / /_ ";
    letter[2][1][5]=" |____|";

    letter[2][2][0]="  ____  ";
    letter[2][2][1]=" |___ \ ";
    letter[2][2][2]="   __) |";
    letter[2][2][3]="  |__ < ";
    letter[2][2][4]="  ___) |";
    letter[2][2][5]=" |____/ ";

    letter[2][3][0]="  _  _   ";
    letter[2][3][1]=" | || |  ";
    letter[2][3][2]=" | || |_ ";
    letter[2][3][3]=" |__   _|";
    letter[2][3][4]="    | |  ";
    letter[2][3][5]="    |_|  ";

    letter[2][4][0]="  _____ ";
    letter[2][4][1]=" | ____|";
    letter[2][4][2]=" | |__  ";
    letter[2][4][3]=" |___ \ ";
    letter[2][4][4]="  ___) |";
    letter[2][4][5]=" |____/ ";

    letter[2][5][0]="    __  ";
    letter[2][5][1]="   / /  ";
    letter[2][5][2]="  / /_  ";
    letter[2][5][3]=" | '_ \ ";
    letter[2][5][4]=" | (_) |";
    letter[2][5][5]="  \___/ ";

    letter[2][6][0]="  ______ ";
    letter[2][6][1]=" |____  |";
    letter[2][6][2]="     / / ";
    letter[2][6][3]="    / /  ";
    letter[2][6][4]="   / /   ";
    letter[2][6][5]="  /_/    ";

    letter[2][7][0]="   ___  ";
    letter[2][7][1]="  / _ \ ";
    letter[2][7][2]=" | (_) |";
    letter[2][7][3]="  > _ < ";
    letter[2][7][4]=" | (_) |";
    letter[2][7][5]="  \___/ ";

    letter[2][8][0]="   ___  ";
    letter[2][8][1]="  / _ \ ";
    letter[2][8][2]=" | (_) |";
    letter[2][8][3]="  \__, |";
    letter[2][8][4]="    / / ";
    letter[2][8][5]="   /_/  ";

    letter[2][9][0]="   ___  ";
    letter[2][9][1]="  / _ \ ";
    letter[2][9][2]=" | | | |";
    letter[2][9][3]=" | | | |";
    letter[2][9][4]=" | |_| |";
    letter[2][9][5]="  \___/ ";


 Place[place36][order]

 order 1 = place name
 order 2 = place type
  order 3 = place owner
 order 4 = building level & price & selling price
 order 5 = place special effect
 order 6 =

 Player[player4][order]

 order 1 = where is player
 order 2 = which lands player has & buliding level - pointer points
  order 3 = how much money player has
 order 4 = which chance card player has now
             if(i==0)str+= " _____________________________________________________________________________________________ ";
         else if(i==1)str+= "|          | B.SILIA|  BALI  |SANTIAGO| EVENT  |  OSLO  | S.HOLM | CHANCE | MOSCOW |          |";
        else if(i==2)str+= "|   JAIL   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   | JACKPOT! |";
         else if(i==3)str+= "|    "PlayerPlace1"    |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |    "PlayerPlace1"    |";
         else if(i==4)str+= "|    "PlayerPlace2"    |________|________|________|________|________|________|________|________|    "PlayerPlace2"    |";
        else if(i==5)str+= "|__________|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__________|";
         else if(i==6)str+= "| S.PORE | |                                                                       | | ATHENS |";
        else if(i==7)str+= "|   "PlayerPlace1"   |"B_Level"|                                                                       |"B_Level"|   "PlayerPlace1"   |";
         else if(i==8)str+= "|   "PlayerPlace2"   |"B_Level"|         __________                                                    |"B_Level"|   "PlayerPlace2"   |";
        else if(i==9)str+= "|________|_|        /    C    /)                                                   |_|________|";
         else if(i==10)str+="| NEWDELI| |       /    H    //                                                    | | P.RICO |";
        else if(i==11)str+="|   "PlayerPlace1"   |"B_Level"|      /    A    //                                                     |"B_Level"|   "PlayerPlace1"   |";
         else if(i=="PlayerPlace1")str+="|   "PlayerPlace2"   |"B_Level"|     /    N    //                                                      |"B_Level"|   "PlayerPlace2"   |";
         else if(i==13)str+="|________|_|    /    G    //                                                       |_|________|";
        else if(i==14)str+="| CHANCE | |   /____E____//                                                        | |  ROME  |";
         else if(i==15)str+="|   "PlayerPlace1"   |"B_Level"|   |_________/                                                         |"B_Level"|   "PlayerPlace1"   |";
        else if(i==16)str+="|   "PlayerPlace2"   |"B_Level"|                                                                       |"B_Level"|   "PlayerPlace2"   |";
         else if(i==17)str+="|________|_|                           _________________                           |_|________|";
        else if(i==18)str+="| BANGKOK| |                          |                 |                          | | EVENT  |";
         else if(i==19)str+="|   "PlayerPlace1"   |"B_Level"|                          |  J A C K P O T  |                          |"B_Level"|   "PlayerPlace1"   |";
        else if(i==20)str+="|   "PlayerPlace2"   |"B_Level"|                  ________|_________________|________                  |"B_Level"|   "PlayerPlace2"   |";
         else if(i==21)str+="|________|_|                 |                                   |                 |_|________|";
        else if(i==22)str+="|  GUAM  | |                 | $ "JPD"   |                 | | BERLIN |";
         else if(i==23)str+="|   "PlayerPlace1"   |"B_Level"|                 |___________________________________|                 |"B_Level"|   "PlayerPlace1"   |";
        else if(i==24)str+="|   "PlayerPlace2"   |"B_Level"|                                                                       |"B_Level"|   "PlayerPlace2"   |";
         else if(i==25)str+="|________|_|                                                                       |_|________|";
        else if(i==26)str+="| CAIRO  | |                                                                       | | SICILiA|";
         else if(i==27)str+="|   "PlayerPlace1"   |"B_Level"|                                                     __________        |"B_Level"|   "PlayerPlace1"   |";
        else if(i==28)str+="|   "PlayerPlace2"   |"B_Level"|                                                    /    E    /)       |"B_Level"|   "PlayerPlace2"   |";
         else if(i==29)str+="|________|_|                                                   /    V    //        |_|________|";
        else if(i==30)str+="| CASINO | |                                                  /    E    //         | |  PARI  |";
         else if(i==31)str+="|   "PlayerPlace1"   |"B_Level"|                                                 /    N    //          |"B_Level"|   "PlayerPlace1"   |";
        else if(i==32)str+="|   "PlayerPlace2"   |"B_Level"|                                                /    T    //           |"B_Level"|   "PlayerPlace2"   |";
         else if(i==33)str+="|________|_|                                               /_________//            |_|________|";
        else if(i=="PlayerPlace2")str+="| TUNIS  | |                                               |_________/             | | LONDON |";
         else if(i==35)str+="|   "PlayerPlace1"   |"B_Level"|                                                                       |"B_Level"|   "PlayerPlace1"   |";
        else if(i==36)str+="|   "PlayerPlace2"   |"B_Level"|                                                                       |"B_Level"|   "PlayerPlace2"   |";
         else if(i==37)str+="|________|_|_______________________________________________________________________|_|________|";
        else if(i==38)str+="|          |__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|__"B_Level"__"B_Level"__|          |";
         else if(i==39)str+="|  START!  |  L.A.  |  TAX   |NEW YORK| EVENT  | SEOUL  | TOKYO  | CHANCE |BEIJING | AIRPORT! |";
        else if(i==40)str+="|    "PlayerPlace1"    |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |   "PlayerPlace1"   |    "PlayerPlace1"    |";
         else if(i==41)str+="|    "PlayerPlace2"    |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |   "PlayerPlace2"   |    "PlayerPlace2"    |";
         else if(i==42)str+="|__________|________|________|________|________|________|________|________|________|__________|";
        */
