#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.c"
#include <pthread.h>
#include <unistd.h>

int size_grid = 20;    
    //Initialisation of the map
char **map = NULL;

int there_is_fruit2(char **map,int nb_ligne, int nb_col){
    //Iterate throught the map and check if a fruit is already present
    for(int col = 0; col < nb_col; col ++){
        
        for(int ligne = 0; ligne < nb_ligne; ligne ++){
            if(map[col][ligne]=='F'){
                return 1;
                }

            if(map[col][ligne]=='C'){
                return 1;
            }

            if(map[col][ligne]=='B'){
                return 1;
            }

            if(map[col][ligne]=='P'){
                return 1;
            }
        }
    }
    return 0;
}

void generate_fruit2(char **map,int nb_ligne, int nb_col){
    if(!there_is_fruit2(map,nb_ligne, nb_col)){

    
        srand(time(NULL));
        int fruit_placed = 0;
        int num_fruit = rand() % 4 + 0;
        
        while(!fruit_placed){
            int rand_L = rand() % nb_ligne + 0;
            int rand_C = rand() % nb_col + 0;
            if(map[rand_L][rand_C]==' '){

                if(num_fruit == 0){
                    map[rand_L][rand_C]='F';
                    fruit_placed = 1;
                }

                if(num_fruit == 1){
                    map[rand_L][rand_C]='C';
                    fruit_placed = 1;
                }

                if(num_fruit == 2){
                    map[rand_L][rand_C]='B';
                    fruit_placed = 1;
                }

                if(num_fruit == 3){
                    map[rand_L][rand_C]='P';
                    fruit_placed = 1;
                }

            }
        }
    }
}
void *plateau(void *p){
    while(1){
        generate_fruit2(map,size_grid,size_grid);
        print_grid(map,size_grid,size_grid);
        printf("\n\n\n");
        sleep(1);
    }
}
void *player(void *p){
    struct snake *s1 = (snake *)malloc(sizeof(struct snake));
    snake_init(s1,5,4,map,5 ,size_grid,size_grid,rand() % 9 + 0);
    while(1){
        snake_move(s1,map);
        sleep(1);
    }
}
int main (int argc, char *argv[], char *env[]){

    pthread_t plateau_thread; 
    pthread_t player_thread; 
    //Initialisation of the map
    map = grid_init(size_grid,size_grid,1);
    //Fill the map
    grid_fill(map,size_grid,size_grid,3);

    pthread_create(&plateau_thread, NULL, plateau,NULL);
    for (int i=0; i<4 ; i++){
        pthread_create(&player_thread, NULL, player, (void*)i);
    }
    pthread_join(plateau_thread,NULL);

    for (int i=0; i<4 ; i++){
        pthread_join(player_thread,NULL);
    }
    
    
    //Print the map

   /* 
    node_t * head = (node_t *) malloc(sizeof(node_t));
    head->val = 1;
   
    print_list(head);
    
    struct node_t* tmp;
    struct node_t* curr;
    curr = head;
    while (head != NULL)
    {
       tmp = head;
       head = head->next;
       printf("delete: %d\n", tmp->val);
       free(tmp);
    }  
    head = (node_t *) malloc(sizeof(node_t));
    head->val = 1;
    free(head);
    print_list(head); 
    */
    return 0;
}
