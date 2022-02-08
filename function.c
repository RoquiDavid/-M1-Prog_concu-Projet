#include "function.h"

//Function that initialize the map
char **grid_init(int L, int C, int lvl){
    //Allocate the memory
    char** map = (char **) malloc(sizeof(char*)*L);
    for(int i = 0; i < C; i ++){
        map[i] = (char *) malloc(sizeof(char)*C);
    }
    return map;

}

//Function that fill the map
void grid_fill(char **map, int L, int C){
    //Fill the map with 0
    for(int i = 0; i < L; i ++){
        for(int j = 0; j < C; j++){
            map[i][j] = '0';
        }
    }

}

//Function that print the map
void print_grid(char** map, int L, int C){
    for(int i = 0; i < L; i ++){
        for(int j = 0; j < C; j++){
            printf("|%c|",map[i][j]);
        }
        printf("\n");
    }
}