#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Struct that allow to definie coordonate of the case from
//which we will create and obstacle
typedef struct snake{
    int id; //Id of the snake
    int length; //The length of the snake
    int score; //The score of the snake
    int life_point; //The remaning life points of the snake
    int speed; //The speed of the snake (basic speed = 0.1 sleep)
    int last_move;// Record the last direction taken by the snake
    int C_last; // Last Col played
    int L_last; // Last line played
    int no_move; //Check if snake position has change between his last round played
    int last_move_status; // Variable to check if the snae has been hited in his last move
    struct part_of_snake  *corpse;
}snake;

typedef struct part_of_snake{
    int L; //Ligne pos of the part
    int C; //Col pos of the part
    struct part_of_snake *next; //Link to the next part of the snake
}part_of_snake;