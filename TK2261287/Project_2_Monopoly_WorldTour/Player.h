#ifndef PLAYER_H
#define PLAYER_H

struct P{
    bool status[4];
    string name[4];
    int position[4];
    int specialEvent[4];
    int event[4];
    int chance[4];
    int order[4];
    int dice[4][2];
    int jail[4];
    int turn[4];
    double money[4];
    double jackpot;
};

struct GameData{
    string letter[4][26][6];
    string placename[36];
    string buildingname[6];
    string buildingimage[6][10];
    string cardname[2][2][10];
    int placetype[36];
    int placeowner[36];
    int placelevel[36];
    double placeprice[4][6][36];
};

#endif // PLAYER_H
