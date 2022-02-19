#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snake.h"
#include "function.c"


int main(int argc, char* argv[], char* env[]){

    int size_grid = 20;    
    //Initialisation of the map
    char **map = grid_init(size_grid,size_grid,1);
    //Fill the map
    grid_fill(map,size_grid,size_grid,3);
    //Print the map
    print_grid(map,size_grid,size_grid);

    struct snake *s1 = (snake *)malloc(sizeof(struct snake));
    struct snake *s2 = (snake *)malloc(sizeof(struct snake));
    struct snake *s3 = (snake *)malloc(sizeof(struct snake));
    struct snake *s4 = (snake *)malloc(sizeof(struct snake));


    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    snake_init(s1,5,4,map,5 ,size_grid,size_grid,1);
    snake_init(s2,5,4,map,5 ,size_grid,size_grid,2);
    snake_init(s3,5,4,map,5 ,size_grid,size_grid,3);
    snake_init(s4,5,4,map,5 ,size_grid,size_grid,4);

    print_grid(map,size_grid,size_grid);
    
    srand(time(NULL));
    snake_move(s1,map);
    snake_move(s1,map);
    snake_move(s1,map);
    snake_move(s1,map);

    snake_move(s2,map);
    snake_move(s2,map);
    snake_move(s2,map);
    snake_move(s2,map);

    snake_move(s3,map);
    snake_move(s3,map);
    snake_move(s3,map);
    snake_move(s3,map);

    snake_move(s4,map);
    snake_move(s4,map);
    snake_move(s4,map);
    snake_move(s4,map);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    print_grid(map,size_grid,size_grid);
    return 0;
}