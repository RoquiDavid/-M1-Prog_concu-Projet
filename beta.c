#include <stdio.h>
#include <stdlib.h>
#include "function.c"
#include "snake.h"
#include <time.h>
#include <unistd.h>

void snake_init(snake *player, int size, int hp,char **map,int taille, int nb_ligne, int nb_col, int id){
    player->id = id;
    player->length = size;
    player->life_point = hp;
    player->score = 0;
    int head_placed = 0;

    srand(time(NULL));
    while(!head_placed){
        printf("ok");
        int rand_L = rand() % nb_ligne + 0;
        int rand_C = rand() % nb_col + 0;
        if(map[rand_L][rand_C]=='0'){
            map[rand_L][rand_C] = player->id+'0';
            player->corpse = (part_of_snake*)malloc(sizeof(struct part_of_snake));
            player->corpse->L = rand_L;
            player->corpse->C = rand_C;
            head_placed = 1;
        }
    }
    
    int part_placed = 1;
    
    srand(time(NULL));

    struct part_of_snake *current_part = NULL;
    
    while(part_placed < player->length){
        
        current_part = player->corpse;
        struct part_of_snake *new_node = (part_of_snake *)malloc(sizeof(struct part_of_snake));

        while (current_part->next != NULL){
            current_part = current_part->next;
        }
        
        int direction = rand() % 4 + 0;

        printf("placed : %d length: %d dir: %d L: %d C: %d\n", part_placed,player->length, direction,current_part->L,current_part->C);
        sleep(1);
        //printf("%d",direction);
        if((direction == 0) & (current_part->L+1 < nb_ligne)){
            
            if(map[current_part->L+1][current_part->C]=='0'){

                printf("ok1");
                map[current_part->L+1][current_part->C] = player->id+'0';
                new_node->L = current_part->L+1;
                new_node->C = current_part->C;
                part_placed++;
            }
        }

        if((direction == 1) & (current_part->L-1 >= 0)){
            if(map[current_part->L-1][current_part->C]=='0'){

                printf("ok2");
                map[current_part->L-1][current_part->C]= player->id+'0';
                new_node->L = current_part->L-1;
                new_node->C = current_part->C;
                part_placed++;
            }
        }

        if((direction == 2) & (current_part->C+1 < nb_col)){
            if(map[current_part->L][current_part->C+1]=='0'){

                printf("ok3");
                map[current_part->L][current_part->C+1] = player->id+'0';
                new_node->L = current_part->L;
                new_node->C = current_part->C+1;
                part_placed++;
            }
        }

        if((direction == 3) & (current_part->C-1 >=0)){
            if(map[current_part->L][current_part->C-1]=='0'){

                printf("ok4");
                map[current_part->L][current_part->C-1] = player->id +'0';
                new_node->L = current_part->L;
                new_node->C = current_part->C-1;
                part_placed++;
            }
        }
        current_part->next = new_node;
    }
    

}

void snake_move(snake *player,char **map){

    int move_done = 0;
    srand(time(NULL));
    int old_L = 0;
    int old_C = 0;

    int old_L_next = 0;
    int old_C_next = 0;
    struct part_of_snake *head = player->corpse;
    while(!move_done){
        int direction = rand() % 4 + 0;

        if(direction == 0){
            
            if(map[player->corpse->L+1][player->corpse->C]=='X'){
                player->life_point--;
            }
            map[player->corpse->L+1][player->corpse->C]= player->id;
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            }
        
        if(direction == 1){
            
            if(map[player->corpse->L-1][player->corpse->C]=='X'){
                player->life_point--;
            }
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L-1][player->corpse->C]= player->id;
            head->L = head->L-1;
        }
        

        if(direction == 2){
            
            if(map[player->corpse->L][player->corpse->C+1]=='X'){
                player->life_point--;
            }
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C+1]= player->id;
            head->L = head->C+1;
            
        }

        if(direction == 3){
            
            if(map[player->corpse->L][player->corpse->C-1]=='X'){
                player->life_point--;
            }
                
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id;
            head->L = head->C-1;
            
        }
        move_done =1;
    }

    if(move_done){
        
        
        struct part_of_snake *current_part = player->corpse;
        while (current_part->next != NULL){
            current_part = current_part->next;
            
            old_L_next = current_part->L;
            old_C_next = current_part->C;

            current_part->L = old_L;
            current_part->C = old_C;

            old_L = old_L_next;
            old_C = old_C_next;
            map[current_part->L][current_part->C] = player->id+'0';

        }
            

    }
}
int main(int argc, char* argv[], char* env[]){

    int size_grid = 20;    
    //Initialisation of the map
    char **map = grid_init(size_grid,size_grid,1);
    //Fill the map
    grid_fill(map,size_grid,size_grid,3);
    //Print the map
    print_grid(map,size_grid,size_grid);

    struct snake *s1 = (snake *)malloc(sizeof(struct snake));


    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    snake_init(s1,5,4,map,5 ,size_grid,size_grid,9);

    print_grid(map,size_grid,size_grid);
    /*
    snake_move(s1,map);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    print_grid(map,size_grid,size_grid);

    
    struct part_of_snake *head_ref = s1->corpse;
    while (head_ref->next != NULL){
        head_ref = head_ref->next;
        printf("%d %d \n",head_ref->C, head_ref->L);
    }


    for(int i = 0; i < 10; i++){
        
        struct part_of_snake* new_node = (struct part_of_snake*) malloc(sizeof(struct part_of_snake));
        struct part_of_snake *last = head;  

        new_node->C  = i;
        new_node->L  = i;

        new_node->next = NULL;

        if (head == NULL)
        {
            head = new_node;
            return;
        } 
        while (last->next != NULL)
            last = last->next;
        
        last->next = new_node;
    }
    player->corpse = head;


    head
    */
    return 0;

}