#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.c"
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex_end_condition = PTHREAD_MUTEX_INITIALIZER;

//map dimensions
#ifndef n
#define n 25
#endif

#ifndef m
#define m 25
#endif

//level number
#ifndef l
#define l 0
#endif

//snake number
#ifndef s
#define s 2
#endif

//Initialisation of the map
char **map = NULL;
//Initialisation of the score needed to win
int score_to_win = 0;
//Initilize variable to check the victory 
int win = 0;
//Initialisation of the winner id
int number_of_snake = s;
int id_winner = -1;
//Initilisation of the struct of current fruit on the map
struct fruit *current_fruit = NULL;

//Thread function which generate a new fruit each time the old one has been eaten
void *plateau(void *p){
    
    while(1){
        //Generate fruit
        generate_fruit(map,n,m,current_fruit);
        //Print the map
        print_grid(map,n,m);
        printf("\n\n\n");
        //You can sleep(1) to have a better visualisation( if you do this
        //then also do this at the end of player function)
        //sleep(1);
    }
}
//Thread funtion that initialze snake snake move and check their status
void *player(void *p){
    //Allocate memory to the snake
    struct snake *s1 = (snake *)malloc(sizeof(struct snake));
    //Initialize the snake
    snake_init(s1,5,4,map,n,m,rand() % 9 + 0);
    while(!s1->dead){
        //Move the the snake
        snake_move(s1,map,n,m,current_fruit);
        //Lock the mutex to manipulate the map (if dead snake->remove his body)
        pthread_mutex_lock(& mutex_end_condition);
        //If the snake has no more hp remaining his thread is canceled
        if(s1->life_point ==0){
            printf("\nLe snake %d a touché trois fois un obstable\n",s1->id);
            remove_snake(s1,map);
            number_of_snake--;
            s1->dead = 1;
            
        }
        //If the score if too hight we kill the snake
        if(s1->score >= (score_to_win+45)){
            printf("\nLe snake a dépassé de %d points le score a atteindre il est donc mort ",(s1->score-score_to_win));
            remove_snake(s1,map);
            s1->dead = 1;
        }
        //If the snake has win we update his status
        if(s1->score>=score_to_win && !s1->dead){
            win = 1;
            id_winner = s1->id;
        }
        //Free the muted
        pthread_mutex_unlock(& mutex_end_condition);
        //This sleep represent the speed of the snake(0.1 sleep basis 
        //and the sleeping time is increased each time the snake eat
        //a fruit*/
        sleep(s1->speed);

    }
}

//Thread function to check if a snake has win the game or if there is no more snake alive
void *score(void *p){
    while(1){
        //Check if a snake has win the game
        if(win){
            printf("Le snake %d gagne !",id_winner);
            exit(0);
        }
        //Check if all the snake are dead
        if(number_of_snake == 0){
            printf("\n Tous les snakes sont morts ! Fin du programme");
            exit(0);
        }
    }
    
}
int main (int argc, char *argv[], char *env[]){
    
    score_to_win = rand() % 99 + 50;
    pthread_t plateau_thread; 
    pthread_t player_thread; 
    pthread_t arbitre_thread;

    current_fruit = (fruit *)malloc(sizeof(struct fruit));
    //Initialisation of the map
    map = grid_init(n,m,l);
    //Fill the map
    grid_fill(map,n,m,l);

    //Create the board thread
    pthread_create(&plateau_thread, NULL, plateau,NULL);

    //Create the arbiter thread to check the wininig condition for the snakes
    pthread_create(&arbitre_thread, NULL, score,NULL);

    //Create the snake thread
    for (int i=0; i<s ; i++){
        pthread_create(&player_thread, NULL, player, (void*)i);
    }
    //Join all the threads together
    pthread_join(plateau_thread,NULL);
    pthread_join(arbitre_thread,NULL);

    for (int i=0; i<s ; i++){
        pthread_join(player_thread,NULL);
    }
    
    return 0;
}
