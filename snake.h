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
    struct part_of_snake  *corpse;
}snake;

typedef struct part_of_snake{
    int L; //Ligne pos of the part
    int C; //Col pos of the part
    struct part_of_snake *next; //Link to the next part of the snake
}part_of_snake;