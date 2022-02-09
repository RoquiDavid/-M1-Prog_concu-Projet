#include <stdio.h>
#include <stdlib.h>
#include "function.c"


int main(int argc, char* argv[], char* env[]){

    int size_grid = 40;
    
    //Initialisation of the map
    char **map = grid_init(size_grid,size_grid,1);
    //Fill the map
    grid_fill(map,size_grid,size_grid,3);
    //Print the map
    print_grid(map,size_grid,size_grid);
    return 0;
}