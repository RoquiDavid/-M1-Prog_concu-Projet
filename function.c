#include "function.h"
#include <math.h>
#include <getopt.h>
#include <time.h>
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
            map[i][j] = ' ';
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
            for(int j = C-3-perim; j < C-2; j++){
                map[i][j] = 'X';
            }
        }
        //Right top obstacle
        for(int i = 2; i < 2+perim ; i++){
            for(int j = C-3-perim; j < C-2; j++){
                map[i][j] = 'X';
            }
        }

    }
    
    
}


//function to initialise snake
void snake_init(snake *player, int size, int hp,char **map,int taille, int nb_ligne, int nb_col, int id){
    player->id = id;
    player->length = size;
    player->life_point = hp;
    player->score = 0;
    int head_placed = 0;

    srand(time(NULL));
    //We randomly place the head of the snake
    while(!head_placed){
        int rand_L = rand() % nb_ligne + 0;
        int rand_C = rand() % nb_col + 0;
        if(map[rand_L][rand_C]==' '){
            map[rand_L][rand_C] = player->id+' ';
            player->corpse = (part_of_snake*)malloc(sizeof(struct part_of_snake));
            player->corpse->L = rand_L;
            player->corpse->C = rand_C;
            head_placed = 1;
        }
    }
    
    int part_placed = 1;
    srand(time(NULL));

    struct part_of_snake *current_part = NULL;
    
    //Loop until all parts of the snake are placed
    while(part_placed < player->length){
        
        current_part = player->corpse;
        struct part_of_snake *new_node = (part_of_snake *)malloc(sizeof(struct part_of_snake));

        while (current_part->next != NULL){
            current_part = current_part->next;
        }
        
        //Chose a random direction
        int direction = rand() % 4 + 0;

        //printf("placed : %d length: %d dir: %d L: %d C: %d\n", part_placed,player->length, direction,current_part->L,current_part->C);
        
        //printf("%d",direction);
        //Bot direction
        if((direction == 0) & (current_part->L+1 < nb_ligne)){
            
            if(map[current_part->L+1][current_part->C]==' '){

                //Change map value by the id of the snake
                map[current_part->L+1][current_part->C] = player->id+'0';
                //Initialise the next part ligne and col
                new_node->L = current_part->L+1;
                new_node->C = current_part->C;
                part_placed++;

        current_part->next = new_node;
            }
        }
        //Top direction
        if((direction == 1) & (current_part->L-1 >= 0)){
            if(map[current_part->L-1][current_part->C]==' '){


                map[current_part->L-1][current_part->C]= player->id+'0';
                new_node->L = current_part->L-1;
                new_node->C = current_part->C;
                part_placed++;

        current_part->next = new_node;
            }
        }

        //Right direction
        if((direction == 2) & (current_part->C+1 < nb_col)){
            if(map[current_part->L][current_part->C+1]==' '){

                map[current_part->L][current_part->C+1] = player->id+'0';
                new_node->L = current_part->L;
                new_node->C = current_part->C+1;
                part_placed++;

        current_part->next = new_node;
            }
        }
        //Left direction
        if((direction == 3) & (current_part->C-1 >=0)){
            if(map[current_part->L][current_part->C-1]==' '){

                map[current_part->L][current_part->C-1] = player->id +'0';
                new_node->L = current_part->L;
                new_node->C = current_part->C-1;
                part_placed++;

        current_part->next = new_node;
            }
        }

        
    }
}

//Function that allow to move the snake
void snake_move(snake *player,char **map){
    int old_L = 0;
    int old_C = 0;

    int old_L_next = 0;
    int old_C_next = 0;
    struct part_of_snake *head = player->corpse;
    int move_done = 0;

    //we chose a random direction
    int direction = rand() % 4 + 0;
    //Bot direction
    if(direction == 0){
        
        //If the snake reach an obstacle he lose 1 hp
        if(map[player->corpse->L+1][player->corpse->C]=='X'){
            player->life_point--;
        }
        if(map[player->corpse->L+1][player->corpse->C]==' '){
            
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
        }

        if(map[player->corpse->L+1][player->corpse->C]=='F'){
            
            player->score+=5;
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
        }

        if(map[player->corpse->L+1][player->corpse->C]=='C'){
            
            player->score+=3;
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
        }

        if(map[player->corpse->L+1][player->corpse->C]=='B'){
            
            player->score+=2;
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
        }

        if(map[player->corpse->L+1][player->corpse->C]=='P'){
            
            player->score+=1;
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
        }
    }
    
    //Top direction
    if(direction == 1){
        
        if(map[player->corpse->L-1][player->corpse->C]=='X'){
            player->life_point--;
        }
        if(map[player->corpse->L-1][player->corpse->C]==' '){
            
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
        }

        if(map[player->corpse->L-1][player->corpse->C]=='F'){
            
            player->score+=5;
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
        }

        if(map[player->corpse->L-1][player->corpse->C]=='C'){
            
            player->score+=3;
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
        }

        if(map[player->corpse->L-1][player->corpse->C]=='B'){
            
            player->score+=2;
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
        }

        if(map[player->corpse->L-1][player->corpse->C]=='P'){
            
            player->score+=1;
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
        }
    }
    
    //Right direction
    if(direction == 2){
        
        if(map[player->corpse->L][player->corpse->C+1]=='X'){
            player->life_point--;
        }
        if(map[player->corpse->L][player->corpse->C+1]==' '){

            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
        }
        
        if(map[player->corpse->L][player->corpse->C+1]=='F'){
            
            player->score+=5;
            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
        }

        if(map[player->corpse->L][player->corpse->C+1]=='C'){
            
            player->score+=3;
            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
        }

        if(map[player->corpse->L][player->corpse->C+1]=='B'){
            
            player->score+=2;
            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
        }

        if(map[player->corpse->L][player->corpse->C+1]=='P'){
            
            player->score+=1;
            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
        }
    }

    //Left direction
    if(direction == 3){
        
        if(map[player->corpse->L][player->corpse->C-1]=='X'){
            player->life_point--;
        }
        if(map[player->corpse->L][player->corpse->C-1]==' '){
            
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
        }  

        if(map[player->corpse->L][player->corpse->C-1]=='F'){
            
            player->score+=5;
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
        }

        if(map[player->corpse->L][player->corpse->C-1]=='C'){
            
            player->score+=3;
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
        }

        if(map[player->corpse->L][player->corpse->C-1]=='B'){
            
            player->score+=2;
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
        }

        if(map[player->corpse->L][player->corpse->C-1]=='P'){
            
            player->score+=1;
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
        }          
    }

    if(move_done){

        //Once the move done we update value of all the parts of the snake
        struct part_of_snake *current_part = player->corpse;
        while (current_part->next != NULL){
            map[current_part->L][current_part->C] = player->id+'0';
            current_part = current_part->next;

            if(current_part->next == NULL){
                map[current_part->L][current_part->C]=' ';
            }
            //Store the old value of the part
            old_L_next = current_part->L;
            old_C_next = current_part->C;
            //Update the value of the part
            current_part->L = old_L;
            current_part->C = old_C;
            //Update the old value of the part
            old_L = old_L_next;
            old_C = old_C_next;
            //Replace the map value 
            map[current_part->L][current_part->C] = player->id+'0';
        }

    
    }
    printf("\n");
    
}
//Function that check if a fruit is already placed in the grid
int there_is_fruit(char **map,int nb_ligne, int nb_col){
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
//Function that allow us to generate a fruit
void generate_fruit(char **map,int nb_ligne, int nb_col){
    if(!there_is_fruit(map,nb_ligne, nb_col)){
        srand(time(NULL));
        int fruit_placed = 0;
        //Select a random fruit
        int num_fruit = rand() % 4 + 0;
        
        //While fruit is not places we select another random cell
        while(!fruit_placed){
            int rand_L = rand() % nb_ligne + 0;
            int rand_C = rand() % nb_col + 0;
            //If cell empty we place the fruit
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
//Function that print the map
void print_grid(char** map, int L, int C){
    for(int i = 0; i < L; i ++){
        for(int j = 0; j < C; j++){
            printf("|%c|",map[i][j]);
        }
        printf("\n");
    }
}