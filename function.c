#include "function.h"
#include <math.h>
#include <getopt.h>
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
void grid_fill(char **map, int L, int C, int lvl){
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

//Function that print the map
void print_grid(char** map, int L, int C){
    for(int i = 0; i < L; i ++){
        for(int j = 0; j < C; j++){
            printf("|%c|",map[i][j]);
        }
        printf("\n");
    }
}