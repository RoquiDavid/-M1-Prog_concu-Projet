#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.c"
#include <pthread.h>
#include <unistd.h>
#include <time.h>
pthread_mutex_t mutex_plateau = PTHREAD_MUTEX_INITIALIZER;
int size_grid = 20;    
//Initialisation of the map
char **map = NULL;
int score_to_win = 0;
//Initilize variable to check the victory 
int win = 0;
int id_winner = -1;
int number of snake = -1;
struct fruit *current_fruit = NULL;

void *plateau(void *p){
    
    while(1){
        generate_fruit(map,size_grid,size_grid,current_fruit);
        print_grid(map,size_grid,size_grid);
        printf("\n\n\n");
        sleep(1);
    }
}
void *player(void *p){

    struct snake *s1 = (snake *)malloc(sizeof(struct snake));
    snake_init(s1,5,4,map,5 ,size_grid,size_grid,rand() % 11 + 0);
    while(1){
        snake_move(s1,map,current_fruit);

        //If the snake has no more hp remaining his thread is canceled
        if(snake_dead(s1)){
            printf("Le snake a touché trois fois un obstable");
            part_of_snake* head = s1->corpse;
            part_of_snake *current_node = head;
            while ( current_node != NULL && current_node->next != NULL) {
                map[current_node->C][current_node->L] = ' ';
                current_node = current_node->next;
            }
            
            int pthread_cancel(pthread_t s1);
        }
        if(s1->score==score_to_win){
            win = 1;
            id_winner = s1->id;
        }
        if(s1->score >= (score_to_win+45)){
            printf("Le snake a dépassé de %d points le score a atteindre il est donc mort",(s1->score-score_to_win));
            int pthread_cancel(pthread_t s1);
        }
        //This sleep represent the speed of the snake(0.1 sleep basis 
        //and the sleeping time is increased each time the snake eat
        //a fruit*/
        sleep(1);
    }
}

void *score(void *p){
    if(win){
        printf("The snake %d gagne !",id_winner);
        exit(0);
    }
    if(number_of_snake == 0){
        printf("Tous les snakes sont morts ! Fin du programme",id_winner);
        exit(0);
    }
    
}
int main (int argc, char *argv[], char *env[]){
    number_of_snake = 4;
    score_to_win = rand() % 99 + 50;
    pthread_t plateau_thread; 
    pthread_t player_thread; 
    number_of_snake = 4;
    current_fruit = (fruit *)malloc(sizeof(struct fruit));
    //Initialisation of the map
    map = grid_init(size_grid,size_grid,1);
    //Fill the map
    grid_fill(map,size_grid,size_grid,4);

    pthread_create(&plateau_thread, NULL, plateau,NULL);

    for (int i=0; i<4 ; i++){
        pthread_create(&player_thread, NULL, player, (void*)i);
    }
    pthread_join(plateau_thread,NULL);

    for (int i=0; i<4 ; i++){
        pthread_join(player_thread,NULL);
    }
    
    return 0;
}
