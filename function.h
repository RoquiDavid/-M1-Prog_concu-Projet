#include "snake.h"
#include "fruit.h"
//Function that initialize the map
char **grid_init(int L, int C, int lvl);

//Function that fill the map
void grid_fill(char **map, int L, int C, int lvl);

//Function that print the map
void print_grid(char** map, int L, int C);

//function to initialise snake
void snake_init(snake *player, int size, int hp,char **map,int taille, int nb_ligne, int nb_col, int id);

//Function that allow to move the snake
void snake_move(snake *player,char **map,fruit *current_fruit);

