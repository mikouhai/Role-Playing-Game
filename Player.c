/* 
 * File:   Player.c
 * Author: rhuang43
 *
 * Created on February 27, 2022, 10:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"
#include <stdint.h>
static int Inventory[INVENTORY_SIZE] = {0,0,0,0};

/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item){
    for(int i = 0; i < 4; i++){
        if(Inventory[i] == 0){
            Inventory[i] = item;
            break;
        }
    }
    if(FindInInventory(item) == SUCCESS){
        return SUCCESS;
    } else{
        return STANDARD_ERROR;
    }
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item){
    for(int i = 0; i < sizeof(Inventory); i++){
        if (Inventory[i] == item){
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}