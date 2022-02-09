#include <stdio.h>
#include <stdlib.h>
#include "function.c"
#include <math.h>
#include <getopt.h>
//Function that fill the map
void grid_fill2(char **map, int L, int C, int lvl){
    //Fill the map with 0
    for(int i =0 ; i < L; i ++){
        for(int j = 0; j < C; j++){
            map[i][j] = '0';
        }
    }
    if(lvl == 1){

        //Left
        for(int i = 0; i < L; i ++){
            map[i][0] = 'X';
        }
        //Right
        for(int i = 0; i < L; i ++){
            map[i][C-1] = 'X';
        }
        //Top
        for(int j = 0; j < C; j ++){
            map[0][j] = 'X';
        }
        //Bot
        for(int j = 0; j < L; j ++){
            map[L-1][j] = 'X';
        }


    }
    if(lvl == 2){
        //We determine the range of the obstable by the /10 division of 
        //the numer of line
        int perim = round(L/10);
            //Left bot obstacle
        for(int i = L-3; i > L-3-perim ; i--){
            for(int j = 2; j <= 2+perim; j++){
                map[i][j] = 'X';
            }
        }
        //Left top obstacle
        for(int i = 2; i < 2+perim ; i++){
            for(int j = 2; j <= 2+perim; j++){
                map[i][j] = 'X';
            }
        }
        //Right bot obstacle
        for(int i = L-3; i > L-3-perim ; i--){
            for(int j = C-2-perim; j <= C-2; j++){
                map[i][j] = 'X';
            }
        }
        //Right top obstacle
        for(int i = 2; i < 2+perim ; i++){
            for(int j = C-2-perim; j <= C-2; j++){
                map[i][j] = 'X';
            }
        }
    }

    if(lvl == 3){

          //Left
        for(int i = 0; i < L; i ++){
            map[i][0] = 'X';
        }
        //Right
        for(int i = 0; i < L; i ++){
            map[i][C-1] = 'X';
        }
        //Top
        for(int j = 0; j < C; j ++){
            map[0][j] = 'X';
        }
        //Bot
        for(int j = 0; j < L; j ++){
            map[L-1][j] = 'X';
        }


        //We determine the range of the obstable by the /10 division of 
        //the numer of line
        int perim = round(L/10);
            //Left bot obstacle
        for(int i = L-3; i > L-3-perim ; i--){
            for(int j = 2; j <= 2+perim; j++){
                map[i][j] = 'X';
            }
        }
        //Left top obstacle
        for(int i = 2; i < 2+perim ; i++){
            for(int j = 2; j <= 2+perim; j++){
                map[i][j] = 'X';
            }
        }
        //Right bot obstacle
        for(int i = L-3; i > L-3-perim ; i--){
            for(int j = C-2-perim; j <= C-2; j++){
                map[i][j] = 'X';
            }
        }
        //Right top obstacle
        for(int i = 2; i < 2+perim ; i++){
            for(int j = C-2-perim; j <= C-2; j++){
                map[i][j] = 'X';
            }
        }

    }
    
    
}
int main(int argc, char* argv[], char* env[]){
    int size_grid = 40;
 int flags, opt;
    int nsecs, tfnd;

    nsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "l:")) != -1) {
        switch (opt) {
        case 'l':
            flags = 1;
            printf("ok");
            break;
        case aqtaq:
            nsecs = atoi(optarg);
            tfnd = 1;
            break;
        default: /* aq?aq */
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    /*
    //Initialisation of the map
    char **map = grid_init(size_grid,size_grid,1);
    //Fill the map
    grid_fill2(map,size_grid,size_grid,3);
    //Print the map
    print_grid(map,size_grid,size_grid);*/
    return 0;
}