// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
// CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"

// User libraries

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
static char Title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
static char Descrip[GAME_MAX_ROOM_DESC_LENGTH + 1];
static uint8_t Exits = 0;
static uint8_t UserInput = 0;
// **** Declare any function prototypes here ****

int main()
{
    /******************************** Your custom code goes below here ********************************/
    if (GameInit() == STANDARD_ERROR)
    {
        FATAL_ERROR();
    };
    GameGetCurrentRoomTitle(Title);
    GameGetCurrentRoomDescription(Descrip);
    printf("Title: %s \n", Title);
    printf("Description: %s \n", Descrip);
    Exits = GameGetCurrentRoomExits();
    while (1)
    {
        if(GAME_ROOM_EXIT_NORTH_EXISTS & Exits){
            printf("North Exit Exists!\n");
        }
        if(GAME_ROOM_EXIT_WEST_EXISTS & Exits){
            printf("WEST Exit Exists!\n");
        }
        if(GAME_ROOM_EXIT_SOUTH_EXISTS & Exits){
            printf("SOUTH Exit Exists!\n");
        }
        if(GAME_ROOM_EXIT_EAST_EXISTS & Exits){
            printf("EAST Exit Exists!\n");
        }
        printf("Select a Direction: n/w/s/e to choose your exit or q to exit game ");
        UserInput = getchar();
        Exits = GameGetCurrentRoomExits();
        if (UserInput == 'n')
        {
            GameGoNorth();
        }
        if (UserInput == 'w')
        {
            GameGoWest();
        }
        if (UserInput == 's')
        {
            GameGoSouth();
        }
        if (UserInput == 'e')
        {
            GameGoEast();
        }
        if (UserInput == 'q'){
            FATAL_ERROR();
        }
        GameGetCurrentRoomTitle(Title);
        GameGetCurrentRoomDescription(Descrip);
        printf("Title: %s \n", Title);
        printf("Description: %s \n", Descrip);
        Exits = GameGetCurrentRoomExits();
        while ((getchar()) != '\n');
    }

    /**************************************************************************************************/
}
