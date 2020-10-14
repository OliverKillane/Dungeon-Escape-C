#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <wctype.h>
#include "DungeonHeader.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

static char gamemap[30][100] = {"       ╔═════╗╔═╗                         ",
                                " ╔═══╗ ║     ╚╝ ║                         ",
                                " ║   ║ ║     ╔══╝                         ",
                                " ╚╗B╔╝ ╚═╗G╔═╝                            ",
                                "  ║ ║    ║ ║                              ",
                                "╔═╝B╚═╗╔═╝G╚═╗╔════════════╗              ",
                                "║     ╚╝     ║║           W╚              ",
                                "║     ╔╗R  BK╚╝            ╔              ",
                                "╚═╗Y╔═╝║     ╔╗B           ║              ",
                                "  ║ ║  ╚═╗B╔═╝╚═╗O╔════════╝              ",
                                "  ║X║    ║ ║    ║ ║                       ",
                                "  ║X║  ╔═╝B╚═╗╔═╝O╚═╗                     ",
                                "  ║X║  ║     ║║    B╚════╗                ",
                                "  ║X║  ║     ║║     ╔══╗ ║                ",
                                "  ║ ║  ║M╔═══╝╚═════╝  ║ ║                ",
                                "╔═╝ ╚═╗║M║     ╔═══╗ ╔═╝B╚═╗╔═════╗       ",
                                "║    B╚╝B║     ║  Y╚═╝     ╚╝     ║       ",
                                "║     ╔══╝     ║   ╔═╗Y   R╔╗R    ║       ",
                                "╚═════╝        ╚╗R╔╝ ║     ║╚═╗S╔═╝       ",
                                "                ║ ║  ╚═════╝  ║ ║         ",
                                "       ╔═════╗╔═╝R╚═╗╔═════╗  ║ ║  ╔═╗    ",
                                "       ║    B╚╝     ║║    G╚══╝S╚══╝O║    ",
                                "       ║     ╔╗B   M╚╝M    ╔╗G   O╔══╝    ",
                                "       ╚═╗G╔═╝║     ╔═╗B╔══╝╚═════╝       ",
                                "         ║ ║  ╚═╗Y╔═╝ ║ ║                 ",
                                "         ║ ║  ╔═╝Y╚═╗                     ",
                                "         ║ ╚══╝     ║                     ",
                                "         ╚════╗G    ║                     ",
                                "              ║     ║                     ",
                                "              ╚╗SH╔═╝                     ",
};

static int sectormap[6][6] = {{2,  0,  1,  -1, -1, -1},
                              {3,  4,  5,  5,  -1, -1},
                              {7,  6,  9,  11, -1, -1},
                              {7,  8,  10, 11, 12, -1},
                              {-1, 13, 14, 15, 16, 19},
                              {-1, 13, -1, -1, -1, -1}
};

int main() {
    int userselection = 0;
    printf("██████╗ ██╗   ██╗███╗   ██╗ ██████╗ ███████╗ ██████╗ ███╗   ██╗    ███████╗███████╗ ██████╗ █████╗ ██████╗ ███████╗\n");
    printf("██╔══██╗██║   ██║████╗  ██║██╔════╝ ██╔════╝██╔═══██╗████╗  ██║    ██╔════╝██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝\n");
    printf("██║  ██║██║   ██║██╔██╗ ██║██║  ███╗█████╗  ██║   ██║██╔██╗ ██║    █████╗  ███████╗██║     ███████║██████╔╝█████╗  \n");
    printf("██║  ██║██║   ██║██║╚██╗██║██║   ██║██╔══╝  ██║   ██║██║╚██╗██║    ██╔══╝  ╚════██║██║     ██╔══██║██╔═══╝ ██╔══╝  \n");
    printf("██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████╗╚██████╔╝██║ ╚████║    ███████╗███████║╚██████╗██║  ██║██║     ███████╗\n");
    printf("╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝    ╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝     ╚══════╝\n");
    for (;;) {
        printf("PLEASE SELECT AN OPTION:\n(1) - TUTORIAL\n(2) - SCORES\n(3) - PLAY GAME\n(4) - CREDITS\n(5) - EXIT\nSELECT:  ");
        scanf("%i", &userselection);
        switch (userselection) {
            case 1 :
                printf("In this game you must escape the dungeon by typing in commands to; move, gather items, and perform actions.\n");
                break;
            case 2 :
                displayScores();
                break;
            case 3 :
                playGame();
                break;
            case 4 :
                printf("This game was a collaboration between Jon Snedden and Oliver Killane, and storyline development guidance from Evrim Muharrem.\n");
                break;
            case 5 :
                printf("Goodbye - hope you come and play again soon!");
                break;
            default :
                printf("Please enter an option from 1-4.");
        }
        if (userselection == 5) {
            break;
        }
        printf("\n\n");
    }
    return 0;
}

// Utility Functions
int randomnum(int min, int max) {
    srand(time(0));
    return (rand() % (max - min + 1)) + min;
}

// For scorekeeping:
void displayScores(void) {
    //display scores from file to the user.
}

void writeScore(char name[8], char date[11], int score) {
    // take a users score, deposit in the file.
}

// Game utilities
char actionSelection(Action actions[], int optionnum, Player *player) {
    int actionlength = optionnum;
    Action allowedactions[10];
    int allowedlength = 0;
    int availablereq;
    int inventoryreq;
    int userselection;
    char userrequest[100];

    for (int actionindex = 0; actionindex < actionlength; actionindex++) {
        availablereq = actions[actionindex].availablereq;
        inventoryreq = actions[actionindex].inventoryreq;

        if (availablereq != -1) {
            if (player->attrs[availablereq] != 'A') {
                continue;
            }
        }

        if (inventoryreq != -1) {
            if (player->attrs[inventoryreq] != 'I') {
                continue;
            }
        }

        allowedactions[allowedlength] = actions[actionindex];
        allowedlength++;
    }

    displayoptions:

    for (int allowedindex = 0; allowedindex < allowedlength; allowedindex++) {
        printf("\n(%d) - %s", allowedindex + 1, allowedactions[allowedindex].description);
    }

    printf("\n(S) - For status.\n(M) - For map.");

    getoption:

    printf("\nSELECT OPTION:    ");
    scanf("%s", &userrequest);

    if (userrequest[0] == 'M') {
        displayMap(player);

        goto displayoptions;
    } else if (userrequest[0] == 'S') {
        displayStatus(player);

        goto displayoptions;
    } else {
        userselection = userrequest[0] - '0';
        if (userselection >= 1 && userselection <= allowedlength) {
            return allowedactions[userselection - 1].result;
        } else {
            goto getoption;
        }
    }
}

void displayStatus(Player *player) {
    int itemno = 0;
    char itemname[100];
    printf("\nINVENTORY:");
    for (int item = 0; item < 11; item++) {
        if (player->attrs[item] == 'I') {
            switch (item) {
                case 0 :
                    strcpy(itemname, "OLD SOCK");
                    break;
                case 1 :
                    strcpy(itemname, "DELICIOUS BACON");
                    break;
                case 2 :
                    strcpy(itemname, "FABULOUS FEAST");
                    break;
                case 3 :
                    strcpy(itemname, "MAGICAL POTION");
                    break;
                case 4 :
                    strcpy(itemname, "BLACK KEY");
                    break;
                case 5 :
                    strcpy(itemname, "SHARP AXE");
                    break;
                case 6 :
                    strcpy(itemname, "SHINY SWORD");
                    break;
                case 7 :
                    strcpy(itemname, "POISONOUS DAGGER");
                    break;
                case 8 :
                    strcpy(itemname, "ORANGE KEY");
                    break;
                case 9 :
                    strcpy(itemname, "SALTY PORK");
                    break;
                case 10 :
                    strcpy(itemname, "POTION OF DEATH");
                    break;
                case 11 :
                    strcpy(itemname, "SHINY KEY");
                    break;
            }
            itemno++;
            printf("\n(%d) - %s", itemno, itemname);
        }
    }

    if (itemno == 0) {
        printf("\n(EMPTY)");
    }

    printf("\nHEALTH:    %d%%\n", player->health);

}

void displayMap(Player *player) {

}

// Monster battle functionality
void Battle(Player *player, Monster monster) {
    for (;;) {
        Playermove(player, &monster);
        switch (monster.id) {
            case 0 :
                MonsterMove(player);
                break;
            case 1 :
                GoulMove(player);
                break;
            case 2 :
                WizardMove(player);
                break;
            case 3 :
                ReaperMove(player);
                break;
        }
        if (monster.health == 0) {
            player->bosses[monster.id] = 'V';
            break;
        }
    }
}

void Playermove(Player *player, Monster *monster) {
    static Attack attacklist[11];
    static int playeroptionsfilled = 0;

    if (playeroptionsfilled == 0) {
        // Axe swing
        strcpy(attacklist[0].name, "AXE SWING");
        strcpy(attacklist[0].description, "Swing your mighty sharp axe at the beast.");
        attacklist[0].itemreq = 5;
        attacklist[0].disposable = 0;
        attacklist[0].offence = 1;
        attacklist[0].value = 30;

        strcpy(attacklist[1].name, "SOCK SMASH");
        strcpy(attacklist[1].description, "Attack the beast with a mysterious sock.");
        attacklist[1].itemreq = 0;
        attacklist[1].disposable = 0;
        attacklist[1].offence = 1;
        attacklist[1].value = 20;


        strcpy(attacklist[2].name, "BLACK KEY STAB");
        strcpy(attacklist[2].description, "Thrust the black key into the monster's underside.");
        attacklist[2].itemreq = 4;
        attacklist[2].disposable = 0;
        attacklist[2].offence = 1;
        attacklist[2].value = 15;

        strcpy(attacklist[3].name, "BACON BREAKFAST");
        strcpy(attacklist[3].description, "Consume the bacon to gain health.");
        attacklist[3].itemreq = 1;
        attacklist[3].disposable = 1;
        attacklist[3].offence = 0;
        attacklist[3].value = 20;

        strcpy(attacklist[4].name, "MAGICAL MEDICINE");
        strcpy(attacklist[4].description, "Drink your magical potion to heal.");
        attacklist[4].itemreq = 3;
        attacklist[4].disposable = 1;
        attacklist[4].offence = 0;
        attacklist[4].value = 40;

        strcpy(attacklist[5].name, "VORATIOUS VOMIT");
        strcpy(attacklist[5].description, "Unconsume your previous feast.");
        attacklist[5].itemreq = 2;
        attacklist[5].disposable = 1;
        attacklist[5].offence = 1;
        attacklist[5].value = 15;

        strcpy(attacklist[6].name, "POISONOUS DAGGER");
        strcpy(attacklist[6].description, "Cut the enemy with your poison laced dagger.");
        attacklist[6].itemreq = 7;
        attacklist[6].disposable = 0;
        attacklist[6].offence = 1;
        attacklist[6].value = 30;

        strcpy(attacklist[7].name, "ORANGE KEY STAB");
        strcpy(attacklist[7].description, "Thrust the orange key into the monster's underside.");
        attacklist[7].itemreq = 8;
        attacklist[7].disposable = 0;
        attacklist[7].offence = 1;
        attacklist[7].value = 15;

        strcpy(attacklist[8].name, "SALTY PORK");
        strcpy(attacklist[8].description, "Eat the pork to gain health.");
        attacklist[8].itemreq = 9;
        attacklist[8].disposable = 1;
        attacklist[8].offence = 0;
        attacklist[8].value = -20;

        strcpy(attacklist[9].name, "SHINY KEY STAB");
        strcpy(attacklist[9].description, "Thrust the shiny key into the monster's underside.");
        attacklist[9].itemreq = 11;
        attacklist[9].disposable = 0;
        attacklist[9].offence = 1;
        attacklist[9].value = 20;

        strcpy(attacklist[10].name, "POTION OF DEATH");
        strcpy(attacklist[10].description, "Cover the opponent in the deathly potion.");
        attacklist[10].itemreq = 10;
        attacklist[10].disposable = 1;
        attacklist[10].offence = 1;
        attacklist[10].value = 40;

        playeroptionsfilled = 1;
    }

    Attack allowedattacks[11];
    int allowedlength = 0;
    char userrequest[100];
    int userselection;


    for (int attackindex = 0; attackindex < 11; attackindex++) {
        if (player->attrs[attacklist[attackindex].itemreq] == 'I') {
            allowedattacks[allowedlength] = attacklist[attackindex];
            allowedlength++;
        }
    }

    printf("\nHOW WILL YOU MOVE AGAINST %s?\nATTACKS:", monster->name);

    for (int attackindex = 0; attackindex < allowedlength; attackindex++) {
        printf("\n(%d) - %s \t\t %s", attackindex + 1, allowedattacks[attackindex].name,
               allowedattacks[attackindex].description);
    }

    printf("\n(S) - For status.\n(M) - For map.");

    getoption:

    printf("\nSELECT OPTION:    ");
    scanf("%s", &userrequest);

    if (userrequest[0] == 'S') {
        displayStatus(player);

        goto getoption;
    } else if (userrequest[0] == 'R') {
        displayMap(player);

        goto getoption;
    } else {
        userselection = userrequest[0] - '0';
        if (userselection >= 1 && userselection <= allowedlength) {
            userselection--;

            // attack routine
            printf("YOU USE %s!", allowedattacks[userselection].name);

            // TODO: Add randomnum element later on using srand(time0))

            if (allowedattacks[userselection].offence == 0) {
                if (player->health + allowedattacks[userselection].value > 100) {
                    printf("YOU HEAL BY %d%%", 100 - player->health);
                    player->health = 100;
                } else {
                    printf("YOU HEAL BY %d%%", allowedattacks[userselection].value);
                    player->health += allowedattacks[userselection].value;
                }
            } else {
                if (monster->health - allowedattacks[userselection].value < 0) {
                    printf("YOU KILLED THE %s!", monster->name);
                    monster->health = 0;
                } else {
                    printf("YOU DEALT %d%% DAMAGE TO THE %s!", allowedattacks[userselection].value, monster->name);
                    monster->health -= allowedattacks[userselection].value;
                }
            }
        } else {
            goto getoption;
        }
    }
}

void MonsterMove(Player *player) {
    static OpponentAttack attackoptions[4];
    static int attackoptionsfilled = 0;
    int chancevalue;
    int chosenmove;
    int accumulatedchance = 0;

    if (attackoptionsfilled == 0) {
        strcpy(attackoptions[0].name, "BITE");
        attackoptions[0].damage = 30;
        attackoptions[0].chance = 15;

        strcpy(attackoptions[1].name, "HARD SHOVE");
        attackoptions[1].damage = 10;
        attackoptions[1].chance = 40;

        strcpy(attackoptions[2].name, "CLAW SWIPE");
        attackoptions[2].damage = 25;
        attackoptions[2].chance = 25;

        strcpy(attackoptions[3].name, "ACID SPIT");
        attackoptions[3].damage = 30;
        attackoptions[3].chance = 15;
    }

    chancevalue = randomnum(0, 100);
    for (int index = 0; index < 4; index++) {
        accumulatedchance += attackoptions[index].chance;
        if (chancevalue <= accumulatedchance) {
            chosenmove = index;
            break;
        }
    }


    if (player->health < attackoptions[chosenmove].damage) {
        printf("\nMONSTER USES %s to deal %d%% DAMAGE", attackoptions[chosenmove].name, player->health);
        player->health = 0;
    } else {
        printf("\nMONSTER USES %s to deal %d%% DAMAGE", attackoptions[chosenmove].name,
               attackoptions[chosenmove].damage);
        player->health -= attackoptions[chosenmove].damage;
    }
}

void WizardMove(Player *player) {
    static OpponentAttack attackoptions[3];
    static int attackoptionsfilled = 0;
    int chancevalue;
    int chosenmove;
    int accumulatedchance = 0;

    if (attackoptionsfilled == 0) {
        strcpy(attackoptions[0].name, "HARMFUL SPELL");
        attackoptions[0].damage = 20;
        attackoptions[0].chance = 40;

        strcpy(attackoptions[1].name, "STICK WHACK");
        attackoptions[1].damage = 15;
        attackoptions[1].chance = 45;

        strcpy(attackoptions[2].name, "FLAMING BALLS");
        attackoptions[2].damage = 30;
        attackoptions[2].chance = 15;

    }

    chancevalue = randomnum(0, 100);
    for (int index = 0; index < 3; index++) {
        accumulatedchance += attackoptions[index].chance;
        if (chancevalue <= accumulatedchance) {
            chosenmove = index;
            break;
        }
    }


    if (player->health < attackoptions[chosenmove].damage) {
        printf("\nWIZARD USES %s to deal %d%% DAMAGE", attackoptions[chosenmove].name, player->health);
        player->health = 0;
    } else {
        printf("\nWIZARD USES %s to deal %d%% DAMAGE", attackoptions[chosenmove].name,
               attackoptions[chosenmove].damage);
        player->health -= attackoptions[chosenmove].damage;
    }
}

void ReaperMove(Player *player) {
    static OpponentAttack attackoptions[3];
    static int attackoptionsfilled = 0;
    int chancevalue;
    int chosenmove;
    int accumulatedchance = 0;

    if (attackoptionsfilled == 0) {
        strcpy(attackoptions[0].name, "GHOSTLY GRAPPLE");
        attackoptions[0].damage = 30;
        attackoptions[0].chance = 25;

        strcpy(attackoptions[1].name, "REAPER'S REVENGE");
        attackoptions[1].damage = 40;
        attackoptions[1].chance = 25;

        strcpy(attackoptions[2].name, "SCYTHE SWIPE");
        attackoptions[2].damage = 20;
        attackoptions[2].chance = 50;

    }

    chancevalue = randomnum(0, 100);
    for (int index = 0; index < 3; index++) {
        accumulatedchance += attackoptions[index].chance;
        if (chancevalue <= accumulatedchance) {
            chosenmove = index;
            break;
        }
    }


    if (player->health < attackoptions[chosenmove].damage) {
        printf("\nREAPER USES %s to deal %d%% DAMAGE", attackoptions[chosenmove].name, player->health);
        player->health = 0;
    } else {
        printf("\nREAPER USES %s to deal %d%% DAMAGE", attackoptions[chosenmove].name,
               attackoptions[chosenmove].damage);
        player->health -= attackoptions[chosenmove].damage;
    }
}

void GoulMove(Player *player) {
    static OpponentAttack attackoptions[4];
    static int attackoptionsfilled = 0;
    int chancevalue;
    int chosenmove;
    int accumulatedchance = 0;

    if (attackoptionsfilled == 0) {
        strcpy(attackoptions[0].name, "PARANORMAL PUNCH");
        attackoptions[0].damage = 40;
        attackoptions[0].chance = 10;

        strcpy(attackoptions[1].name, "SLY SLAP");
        attackoptions[1].damage = 20;
        attackoptions[1].chance = 40;

        strcpy(attackoptions[2].name, "SLITHERING SLASH");
        attackoptions[2].damage = 30;
        attackoptions[2].chance = 30;

        strcpy(attackoptions[3].name, "SHIVER SIDESWIPE");
        attackoptions[3].damage = 35;
        attackoptions[3].chance = 25;
    }

    chancevalue = randomnum(0, 100);
    for (int index = 0; index < 4; index++) {
        accumulatedchance += attackoptions[index].chance;
        if (chancevalue <= accumulatedchance) {
            chosenmove = index;
            break;
        }
    }


    if (player->health < attackoptions[chosenmove].damage) {
        printf("\nGOUL USES %s to deal %d%% DAMAGE", attackoptions[chosenmove].name, player->health);
        player->health = 0;
    } else {
        printf("\nGOUL USES %s to deal %d%% DAMAGE", attackoptions[chosenmove].name, attackoptions[chosenmove].damage);
        player->health -= attackoptions[chosenmove].damage;
    }
}

// For the game:
void playGame(void) {

    // Create player structure.
    Player player;

    // Create player name.
    printf("Enter Player Name:   ");
    scanf("%s", &player.name);

    //create player attributes
    player.health = 100;
    player.currentroom = 0;

    strcpy(player.attrs, "AAAAAAAAAAAA");
    strcpy(player.visitedrooms, "NNNNNNNNNNNNNNNNNNN");
    strcpy(player.bosses, "NNNN");

    for (;;) {
        if (player.health <= 0) {
            //death message
            break;
        } else if (player.currentroom == 18) {
            //you win message
            break;
        }

        player.prevroom = player.currentroom;

        switch (player.currentroom) {
            case 0 :
                player.currentroom = A(&player);
                break;
            case 1 :
                player.currentroom = B(&player);
                break;
            case 2 :
                player.currentroom = C(&player);
                break;
            case 3 :
                player.currentroom = D(&player);
                break;
            case 4 :
                player.currentroom = E(&player);
                break;
            case 5 :
                player.currentroom = F(&player);
                break;
        }

        player.visitedrooms[player.prevroom] = 'V';
    }
}

// Rooms:

// The first room.
int A(Player *player) {
    Action actions[3];
    char result;

    // Pick up sword action
    strcpy(actions[0].description, "Pick up the sword.");
    actions[0].availablereq = 6;
    actions[0].inventoryreq = -1;
    actions[0].result = '1';

    //Go out the green door action
    strcpy(actions[1].description, "Go out the green door.");
    actions[1].availablereq = -1;
    actions[1].inventoryreq = -1;
    actions[1].result = 'E';

    //Open dark cupboard action
    strcpy(actions[2].description, "Open the dark cupboard in the corner of the room.");
    actions[2].availablereq = -1;
    actions[2].inventoryreq = -1;
    actions[2].result = 'B';


    if (player->visitedrooms[0] == 'V') {
        printf("\nYou look about the cold dark room you started in.");
    } else {
        printf("\nYou wake up, cold and disoriented in a dark room.");
    }
    if (player->attrs[6] == 'A') {
        printf("\nThere is a large broadsword on the floor");
    }
    printf("\nTo your right is a cupboard, to the left an old green door.");

    for (;;) {
        result = actionSelection(actions, 3, player);
        switch (result) {
            case '1' :
                player->attrs[6] = 'I';
                break;
            case 'E':
                return 4;
            case 'B':
                return 1;
        }
    }
}

// The cupboard adjacent to the first room.
int B(Player *player) {
    Action actions[2];
    char result;

    // Close cupboard option
    strcpy(actions[0].description, "Close the cupboard.");
    actions[0].availablereq = -1;
    actions[0].inventoryreq = -1;
    actions[0].result = 'A';

    // Take sock option
    strcpy(actions[1].description, "Take the old sock.");
    actions[1].availablereq = 0;
    actions[1].inventoryreq = -1;
    actions[1].result = '1';

    printf("\nYou open the cupboard.");
    if (player->attrs[0] != 'A') {
        printf("\nIt smells as if it once contained an old sock");
    } else {
        printf("\nIt contains an old sock");
    }

    if (player->visitedrooms[1] == 'V') {
        printf("\nYou nostalgise about how great this cupboard was last time you opened it.");
    }

    for (;;) {
        result = actionSelection(actions, 2, player);
        switch (result) {
            case '1' :
                player->attrs[0] = 'I';
                break;
            case 'A':
                return 0;
        }
    }
}

int C(Player *player) {
    Action actions[2];
    char result;

    // Take axe option
    strcpy(actions[0].description, "Take the axe.");
    actions[0].availablereq = 5;
    actions[0].inventoryreq = -1;
    actions[0].result = '1';

    // Exit by door option
    strcpy(actions[1].description, "Exit by the door.");
    actions[1].availablereq = -1;
    actions[1].inventoryreq = -1;
    actions[1].result = 'D';

    printf("\nYou enter a dingey room with a single door.");
    if (player->visitedrooms[2] == 'V') {
        printf("\nYou can remember a being in a room like this previously.");
    }
    if (player->attrs[5] == 'A') {
        printf("\nThere is an axe resting against one wall of the room, even better its been sharpened");
    }

    for (;;) {
        result = actionSelection(actions, 2, player);
        switch (result) {
            case '1' :
                player->attrs[5] = 'I';
                break;
            case 'D':
                return 3;
        }
    }
}

int D(Player *player) {
    Action actions[4];
    char result;

    // Take the bacon option.
    strcpy(actions[0].description, "Take the bacon.");
    actions[0].availablereq = 1;
    actions[0].inventoryreq = -1;
    actions[0].result = '1';

    // Open the red door option.
    strcpy(actions[1].description, "Open the red door");
    actions[1].availablereq = -1;
    actions[1].inventoryreq = -1;
    actions[1].result = 'E';


    // Open the brown door option.
    strcpy(actions[2].description, "Open the brown door.");
    actions[2].availablereq = -1;
    actions[2].inventoryreq = -1;
    actions[2].result = 'C';

    // Open the yellow door option.
    strcpy(actions[3].description, "Open the yellow door.");
    actions[3].availablereq = -1;
    actions[3].inventoryreq = -1;
    actions[3].result = 'H';

    if (player->visitedrooms[3] == 'V') {
        printf("\nYou enter a bacon smelling room, you have been here before.");
    } else {
        printf("\nThere is a delicious piece of bacon hanging from a string from the ceiling.");
    }

    printf("\nThere are 3 doors leading in and out of the room, one red, one brown and one yellow");

    for (;;) {
        result = actionSelection(actions, 4, player);
        switch (result) {
            case '1' :
                player->attrs[1] = 'I';
                break;
            case 'E':
                return 4;
            case 'C':
                return 2;
            case 'H':
                printf("\nAs you enter the door you fall down a long slide, crashing throught the door onto the floor of the next room. \nThe door mysteriously slams shut behind you.");
                return 7;
        }
    }
}

// Room adjacent to the starting room
int E(Player *player) {
    Action actions[4];
    char result;

    // Open the green door option.
    strcpy(actions[0].description, "Open the green door");
    actions[0].availablereq = -1;
    actions[0].inventoryreq = -1;
    actions[0].result = 'A';

    // Open the red door option.
    strcpy(actions[1].description, "Open the red door");
    actions[1].availablereq = -1;
    actions[1].inventoryreq = -1;
    actions[1].result = 'D';


    // Open the brown door option.
    strcpy(actions[2].description, "Open the blue door.");
    actions[2].availablereq = -1;
    actions[2].inventoryreq = -1;
    actions[2].result = 'G';

    // Open the black door option.
    strcpy(actions[3].description, "Open the black door with the black key.");
    actions[3].availablereq = -1;
    actions[3].inventoryreq = 4;
    actions[3].result = 'F';

    if (player->visitedrooms[4] == 'V') {
        printf("\nYou re-enter the room adjacent to the dark room you started in.");
    } else {
        printf("\nYou enter another dark room - and hear a noise somewhere beyond.");
    }
    printf("\nThere is a door on each of the four sides, one green, one red, one blue and one black.");
    if (player->attrs[4] == 'I') {
        printf("\nYou have the key to the black door, and all the others are unlocked");
    } else {
        printf("You try the handle of each door, all are unlocked, except for the black door");
    }

    for (;;) {
        result = actionSelection(actions, 4, player);
        switch (result) {
            case 'A' :
                return 0;
            case 'D':
                return 3;
            case 'G':
                return 6;
            case 'F' :
                return 5;
        }
    }
}

int F(Player *player) {
    // Room options setup
    Action actions[4];
    char result;

    //take the feast action
    strcpy(actions[0].description, "Feast on the food.");
    actions[0].availablereq = 2;
    actions[0].inventoryreq = -1;
    actions[0].result = '1';

    // open the white door action
    strcpy(actions[1].description, "Open the white door");
    actions[1].availablereq = -1;
    actions[1].inventoryreq = -1;
    actions[1].result = '2';

    //open the orange door option
    strcpy(actions[2].description, "Open the orange door");
    actions[2].availablereq = -1;
    actions[2].inventoryreq = -1;
    actions[2].result = 'J';

    //open the black door option
    strcpy(actions[3].description, "Open the black door.");
    actions[3].availablereq = -1;
    actions[3].inventoryreq = -1;
    actions[3].result = 'E';


    // Monster battle setup
    Monster monster;
    monster.health = 100;
    strcpy(monster.name, "UGLY MONSTER");
    monster.id = 0;


    if (player->bosses[0] == "N"){
        printf("You enter a larger castle dining hall, with tables all set prepared for a feast and every candles lit.\nIt almost looks idilic, provided you ignore the monster eyeing up your flesh from the throne.");
        Battle(player, monster);
        if (player->health > 0){
            printf("Having vanquished the beast you feel fufilled in life. However you are hungry");
        }
         //TODO: Death program flow, back to main switch? and then sort there?
    }

    printf("You enter the dining hall of what you now presume is some sort of subterrainian castle. \n");
    if (player->visitedrooms[5] == 'V'){
        printf("You've been here before.\n");
    }
    printf("There is a black door, a large orange door, and a small white door.");

    for(;;){
        result = actionSelection(actions, 4, player);
        switch(result){
            case '1' :
                if (player->health < 20){
                    printf("You over-eat and die as a result.");
                    player->health = 0;
                }
                else {
                    printf("You over-eat and lose 20 health as a result.");
                    player->health -= 20;
                }

                //TODO die here
                break;
            case '2' :
                printf("You fall to your death into a makeshift latrine as the rotten wooden facets break.");
                player->health = 0;

                //TODO die here
                break;
            case 'J' :
                return 9;
            case 'E' :
                return 4;
        }
    }
}

int G(Player *player){
    Action actions[3];
    char result;

    // pick up black key option
    strcpy(actions[0].description, "Pick up the key.");
    actions[0].availablereq = 4;
    actions[0].inventoryreq = -1;
    actions[0].result = '1';

    // Open blue door option
    strcpy(actions[0].description, "Open the blue door");
    actions[0].availablereq = -1;
    actions[0].inventoryreq = -1;
    actions[0].result = 'E';

    // Open mauve door option
    strcpy(actions[0].description, "Open the mauve door");
    actions[0].availablereq = -1;
    actions[0].inventoryreq = -1;
    actions[0].result = 'I';

    printf("You enter a large atrium, it like many of the other rooms smells very bad. There are only two doors, one blue and one mauve.");

    if (player->visitedrooms[6] == 'V'){
        printf("You remember being in this very atrium before");
    }
    else {
        printf("You notice that there is a faint ray of light coming from the ceiling.");
    }
    if (player->attrs[4] == 'A'){
        printf("There is a large black key on the floor.");
    }

    for(;;){
        result = actionSelection(actions, 3, player);
        switch(result){
            case '1' :
                player->attrs[4] = 'I';
                break;
            case 'E' :
                return 4;
            case 'I' :
                return 8;
        }
    }
}

int H(Player *player){
    //TODO Wizard battle here also oh fuck we at 1000
}