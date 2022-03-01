#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defining a struct for elements place (x,y) on the board
typedef struct fruit {
    char fruit_type;
    int L;
    int C;
} fruit;

//Define a ctruct for fruits made  of 4 elements array for the places of each fruit and a boolean variable for detecting wether the fruit is captured or not
typedef struct  fruit{
    part place [4];
    bool not_captured[4];
}fruit;

//define fruits of type fruit
struct fruit fraise,cerise, banane, pomme;