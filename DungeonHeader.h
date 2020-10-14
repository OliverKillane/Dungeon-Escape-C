//
// Created by olive on 29/05/2020.
//

#ifndef DUNGEON_ESCAPE_DUNGEONHEADER_H
#define DUNGEON_ESCAPE_DUNGEONHEADER_H

#endif //DUNGEON_ESCAPE_DUNGEONHEADER_H

// Utility functions
int randomnum(int min, int max);

// Scores functions:
void displayScores(void);
void writeScore(char name[8], char date[11], int score);

// Structures required
typedef struct Actions{
    char description[1000];
    int availablereq;
    int inventoryreq;
    char result;
} Action;

typedef struct Players {
    char name[8];
    int score;
    int health;
    char attrs[12];
    char bosses[4];
    int currentroom;
    int prevroom;
    char visitedrooms[20];
} Player;

// Game critical functions:
void playGame(void);
char actionSelection(Action actions[],int optionum, Player *player);
void displayStatus(Player *player);
void displayMap(Player *player);

//Battle functionality
typedef struct Monsters{
    char name[100];
    int health;
    int id;
} Monster;

typedef struct Attacks{
    char name [100];
    char description[1000];
    int itemreq;
    int disposable;
    int offence;
    int value;
} Attack;

typedef struct OpponentAttacks {
    char name[100];
    int damage;
    int chance;
} OpponentAttack;

void Battle(Player *player, Monster monster);
void Playermove(Player *player, Monster *monster);

// Opponent Utility
void MonsterMove(Player *player);
void WizardMove(Player *player);
void ReaperMove(Player *player);
void GoulMove(Player *player);

// Rooms:
int A(Player *player);
int B(Player *player);
int C(Player *player);
int D(Player *player);
int E(Player *player);
int F(Player *player);
int G(Player *player);
int H(Player *player);
int I(Player *player);
int J(Player *player);
