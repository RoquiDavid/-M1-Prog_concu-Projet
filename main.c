#include <stdio.h>
#include <stdlib.h>
#include "function.h"


int main(int argc, char* argv[], char* env[]){

    //Initialisation of the map
    char **map = grid_init(20,20,1);

    //Fill the map
    grid_fill(map,20,20);
    
    //Print the map
    print_grid(map,20,20);

    return 0;
}