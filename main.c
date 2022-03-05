#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.c"
#include <pthread.h>
#include <unistd.h>
#include <time.h>
pthread_mutex_t mutex_end_condition = PTHREAD_MUTEX_INITIALIZER;
int size_grid = 20;    
//Initialisation of the map
char **map = NULL;
int score_to_win = 0;
//Initilize variable to check the victory 
int win = 0;
int id_winner = -1;
int number_of_snake = -1;
struct fruit *current_fruit = NULL;

void *plateau(void *p){
    
    while(1){
        generate_fruit(map,size_grid,size_grid,current_fruit);
        print_grid(map,size_grid,size_grid);
        printf("\n\n\n");
    }
}
void *player(void *p){

    struct snake *s1 = (snake *)malloc(sizeof(struct snake));
    snake_init(s1,5,4,map,5 ,size_grid,size_grid,rand() % 11 + 0);
    int dead = 0;
    while(!dead){
        snake_move(s1,map,current_fruit);
        pthread_mutex_lock(& mutex_end_condition);
        //If the snake has no more hp remaining his thread is canceled
        if(s1->life_point ==0){
            printf("\nLe snake %d a touché trois fois un obstable\n",s1->id);
            remove_snake(s1,map);
            number_of_snake--;
            dead = 1;
            
        }
        if(s1->score>=score_to_win){
            win = 1;
            id_winner = s1->id;
        }
        if(s1->score >= (score_to_win+45)){
            printf("\nLe snake a dépassé de %d points le score a atteindre il est donc mort ",(s1->score-score_to_win));
            remove_snake(s1,map);
        }
        pthread_mutex_unlock(& mutex_end_condition);
        //This sleep represent the speed of the snake(0.1 sleep basis 
        //and the sleeping time is increased each time the snake eat
        //a fruit*/
        sleep(s1->speed);

    }
}

void *score(void *p){
    while(1){
        if(win){
            printf("Le snake %d gagne !",id_winner);
            exit(0);
        }
        if(number_of_snake == 0){
            printf("\n Tous les snakes sont morts ! Fin du programme");
            exit(0);
        }
    }
    
}
int main (int argc, char *argv[], char *env[]){
    number_of_snake = 4;
    score_to_win = rand() % 99 + 50;
    pthread_t plateau_thread; 
    pthread_t player_thread; 
    pthread_t arbitre_thread;

    current_fruit = (fruit *)malloc(sizeof(struct fruit));
    //Initialisation of the map
    map = grid_init(size_grid,size_grid,1);
    //Fill the map
    grid_fill(map,size_grid,size_grid,4);

    //Create the board thread
    pthread_create(&plateau_thread, NULL, plateau,NULL);

    //Create the arbiter thread to check the wininig condition for the snakes
    pthread_create(&arbitre_thread, NULL, score,NULL);

    for (int i=0; i<4 ; i++){
        pthread_create(&player_thread, NULL, player, (void*)i);
    }
    pthread_join(plateau_thread,NULL);
    pthread_join(arbitre_thread,NULL);

    for (int i=0; i<4 ; i++){
        pthread_join(player_thread,NULL);
    }
    
    return 0;
}
