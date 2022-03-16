/*
 * File:   Game.c
 * Author: rhuang43
 *
 * Created on February 27, 2022, 10:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
// helper function to get current room to the room being passed in
static int CurrentRoom = 0;
static int TitleLength;
static int ItemsContainedLength;
static int ItemReqLength;
static int DescripLength; // length of an something
static uint8_t ItemRequired;
static uint8_t ItemsContained;
struct Versions
{
    char *Title;
    char *ItemReq;
    char *Description;
};
typedef struct
{
    char Title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char Descrip[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t north;
    uint8_t south;
    uint8_t east;
    uint8_t west;
} TheRooms;
static TheRooms Current_Room;
struct Versions V2; // Declares V2 of type Version
struct Versions V1; // Declares V1 of type Version
// helper function to get the appropriate amount of versions
int LoadRoom(uint16_t RoomNumber)
{

    char FileName[100];
    sprintf(FileName, "RoomFiles/room%d.txt", RoomNumber);
    FILE *fp = fopen(FileName, "rb");
    if (fp == NULL)
    {
        fclose(fp);
        return STANDARD_ERROR;
    }
    fseek(fp, 3, SEEK_SET);
    TitleLength = fgetc(fp);
    fgets(Current_Room.Title, TitleLength + 1, fp);
    Current_Room.Title[TitleLength] = '\0';
    int flag = TRUE;
    while (flag == TRUE)
    {
        ItemReqLength = fgetc(fp);
        for (int i = 0; i < ItemReqLength; i++)
        {
            ItemRequired = fgetc(fp);
            if (FindInInventory(ItemRequired) == SUCCESS)
            {
                flag = FALSE;
            }
            else
            {
                flag = TRUE;
            }
        }
        DescripLength = fgetc(fp);
        fgets(Current_Room.Descrip, DescripLength + 1, fp);
        Current_Room.Descrip[DescripLength] = '\0';
        ItemsContainedLength = fgetc(fp);
        for (int i = 0; i < ItemsContainedLength; i++)
        {
            ItemsContained = fgetc(fp);
            AddToInventory(ItemsContained);
        }
        Current_Room.north = fgetc(fp);
        Current_Room.east = fgetc(fp);
        Current_Room.south = fgetc(fp);
        Current_Room.west = fgetc(fp);
        flag = FALSE;
    }
    fclose(fp);
    return SUCCESS;
}
    // if (Position == 0)
    // {
    //     printf("position, %d", Position); // getting version 1
    //     fseek(fp, 3, SEEK_SET);
    //     TitleLength = fgetc(fp);
    //     printf("title Length %d", TitleLength);
    //     for (int i = 0; i < TitleLength; i++)
    //     { // loop through the file title
    //         TitleHolder[i] = fgetc(fp);
    //     }
    //     TitleHolder[TitleLength + 1] = '\0';
    // }
    // else
    // {
    //     fseek(fp, Position, SEEK_SET);
    // }
//     ItemReqLength = fgetc(fp); // item req counter
//     for (int i = 0; i < CounterLength; i++)
//     {
//         ItemReqHolder[i] = fgetc(fp);
//     }
//     CounterLength = fgetc(fp); // description length counter
//     for (int i = 0; i < CounterLength; i++)
//     {
//         DescHolder[i] = fgetc(fp);
//         Items = i;
//     }
//     DescHolder[CounterLength] = '\0';
//     CounterLength = fgetc(fp); // item contained counter
//     for (int i = 0; i < CounterLength; i++)
//     {
//         AddToInventory(fgetc(fp));
//     }
//     north = fgetc(fp);
//     east = fgetc(fp);
//     south = fgetc(fp);
//     west = fgetc(fp);
//     if (Position == 0)
//     {
//         printf("TitleHolder1, %s", TitleHolder);
//         V1.Title = TitleHolder;
//         V1.Description = DescHolder;
//         V1.ItemReq = ItemReqHolder;
//         Position = ftell(fp);
//         fclose(fp);
//     }
//     else
//     {
//         printf("TitleHolder2, %s", TitleHolder);
//         V2.Title = TitleHolder;
//         V2.Description = DescHolder;
//         V2.ItemReq = ItemReqHolder;
//         Position = 0;
//         fclose(fp);
//     }
// }
// char *GetTitleHolder(void)
// {
//     if (Position == 0)
//     {
//         return V1.Title;
//     }
//     else
//     {
//         return V2.Title;
//     }
// }
int GameGoNorth(void)
{
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS)
    { // The current room has a  north exit
        return LoadRoom(Current_Room.north);
    }
    else
    {
        return STANDARD_ERROR;
    }
}

/**
 * @see GameGoNorth
 */
int GameGoEast(void)
{
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS)
    {
        // The current room has an east exit

        return LoadRoom(Current_Room.east);
    }
    else
    {
        return STANDARD_ERROR;
    }
}

/**
 * @see GameGoNorth
 */
int GameGoSouth(void)
{
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS)
    {
        // The current room has an south exit
        return LoadRoom(Current_Room.south);
    }
    else
    {
        return STANDARD_ERROR;
    }
}

/**
 * @see GameGoNorth
 */

int GameGoWest(void)
{
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS)
    {
        return LoadRoom(Current_Room.west);;
    }
    else
    {
        return STANDARD_ERROR;
    }
}

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void)
{
    CurrentRoom = 32;
    if (CurrentRoom == STARTING_ROOM)
    {
        return LoadRoom(CurrentRoom);
    }
    else
    {
        return STANDARD_ERROR;
    }
}

/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title)
{
    strncpy(title, Current_Room.Title , GAME_MAX_ROOM_TITLE_LENGTH + 1);
    return strlen(title);
}

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc)
{
    strncpy(desc, Current_Room.Descrip , GAME_MAX_ROOM_DESC_LENGTH + 1);
    return strlen(desc);
}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
uint8_t GameGetCurrentRoomExits(void)
{
    uint8_t Results = 0B0000;
    if (Current_Room.north != 0)
    {
        Results += GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (Current_Room.east != 0x00)
    {
        Results += GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (Current_Room.south != 0x00)
    {
        Results += GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (Current_Room.west != 0x00)
    {
        Results += GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return Results;
}
