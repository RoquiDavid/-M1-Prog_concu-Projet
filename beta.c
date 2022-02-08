#include <stdio.h>
#include <stdlib.h>
#include "function.c"
#include "net.h"

//Function that fill the map
void grid_fill2(char **map, int L, int C){
    //Fill the map with 0
    /*
    for(int i = L-3; i < ; i ++){
        for(int j = 0; j < C; j++){
            map[i][j] = '0';
        }
    }*/

    for(int i = 0; i < L; i ++){
        for(int j = 0; j < C; j++){
            map[i][j] = '0';
        }
    }
}
int main(int argc, char* argv[], char* env[]){

    //Initialisation of the map
    char **map = grid_init(20,20,1);
    //Fill the map
    grid_fill(map,20,20);
    //Print the map
    print_grid(map,20,20);

    return 0;
}