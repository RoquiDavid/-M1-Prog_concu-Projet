#include "function.h"
#include <math.h>
#include <getopt.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex_snake = PTHREAD_MUTEX_INITIALIZER;

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
            map[i][0] = ' ';
        }
        //Right
        for(int i = 0; i < L; i ++){
            map[i][C-1] = ' ';
        }
        //Top
        for(int j = 0; j < C; j ++){
            map[0][j] = ' ';
        }
        //Bot
        for(int j = 0; j < L; j ++){
            map[L-1][j] = ' ';
        }


    }

    if(lvl == 2){

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
    if(lvl == 3){
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

    if(lvl == 4){

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
        pthread_mutex_lock(& mutex_snake);
        if(map[rand_L][rand_C]==' '){
            map[rand_L][rand_C] = player->id+' ';
            player->corpse = (part_of_snake*)malloc(sizeof(struct part_of_snake));
            player->corpse->L = rand_L;
            player->corpse->C = rand_C;
            head_placed = 1;
        }
        pthread_mutex_unlock(& mutex_snake);
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
            pthread_mutex_lock(& mutex_snake);
            if(map[current_part->L+1][current_part->C]==' '){

                //Change map value by the id of the snake
                map[current_part->L+1][current_part->C] = player->id+'0';
                //Initialise the next part ligne and col
                new_node->L = current_part->L+1;
                new_node->C = current_part->C;
                part_placed++;
                current_part->next = new_node;
            }
            pthread_mutex_unlock(& mutex_snake);
        }
        //Top direction
        if((direction == 1) & (current_part->L-1 >= 0)){
            pthread_mutex_lock(& mutex_snake);    
            if(map[current_part->L-1][current_part->C]==' '){

                map[current_part->L-1][current_part->C]= player->id+'0';
                new_node->L = current_part->L-1;
                new_node->C = current_part->C;
                part_placed++;
                current_part->next = new_node;
            }
            pthread_mutex_unlock(& mutex_snake);
        }

        //Right direction
        if((direction == 2) & (current_part->C+1 < nb_col)){
            pthread_mutex_lock(& mutex_snake);
            if(map[current_part->L][current_part->C+1]==' '){

                map[current_part->L][current_part->C+1] = player->id+'0';
                new_node->L = current_part->L;
                new_node->C = current_part->C+1;
                part_placed++;
                current_part->next = new_node;
            }
            pthread_mutex_unlock(& mutex_snake);
        }
        //Left direction
        if((direction == 3) & (current_part->C-1 >=0)){
            pthread_mutex_lock(& mutex_snake);
            if(map[current_part->L][current_part->C-1]==' '){

                map[current_part->L][current_part->C-1] = player->id +'0';
                new_node->L = current_part->L;
                new_node->C = current_part->C-1;
                part_placed++;
                current_part->next = new_node;
            }
            pthread_mutex_unlock(& mutex_snake);
        }

        
    }
}
int is_fruit(char **map,int col, int ligne){
    pthread_mutex_lock(& mutex_snake);
    if(map[col][ligne] == 'F'||map[col][ligne] == 'C'||map[col][ligne] == 'B'||map[col][ligne] == 'P'){
        return 1;
    }
    pthread_mutex_unlock(& mutex_snake);
    return 0;
}
//Function that allow to move the snake
void snake_move(snake *player,char **map,fruit *current_fruit){
    int old_L = 0;
    int old_C = 0;
    //Variable use to check if the snake has eat a fruit or no
    int fruit_eated = 0;
    int old_L_next = 0;
    int old_C_next = 0;
    struct part_of_snake *head = player->corpse;
    int move_done = 0;

    //we chose a random direction
    int direction = -1;
    int bad_direction = -2;
    //In this section we chose the best direction for the snake to move toward the fruit
    
    pthread_mutex_lock(& mutex_snake);
    //If the player has hited a wall we avoid this direction
    if(player->last_move_status == -1){
        bad_direction = player->last_move;
    }
    //Right
    //printf("R: %d \n L: %d\n ",head->C - current_fruit->C,head->C - current_fruit->C);
    if(head->C - current_fruit->C < 0 && bad_direction!=2){
        //printf("Right");
            direction = 2;
    }
    //LEFT
    if(head->C - current_fruit->C > 0 && bad_direction!=3){
        //printf("Left");
        direction = 3;
        
    }
    
    //TOP
    if(head->L - current_fruit->L < 0 && bad_direction!=0){
        //printf("BOT");
        direction = 0;
        

    }
    //BOT
    if(head->L - current_fruit->L > 0 && bad_direction!=-1){
        //printf("TOP");
        direction = 1;
        

    }
    //If the snake is blocked by the strategy choosen, he just chose a random direction
    if(player->no_move){
        srand(time(NULL));
        direction = rand() % 4 + 0; 
    }
    //printf("[%d][%d]   [%d][%d]\n",head->C, current_fruit->C,head->L, current_fruit->L);
    pthread_mutex_unlock(& mutex_snake);

    //Bot direction
    if(direction == 0){
        //printf("BOT");
        pthread_mutex_lock(& mutex_snake);
        //If the snake reach an obstacle he lose 1 hp and lose 15 score point
        if(map[player->corpse->L+1][player->corpse->C]=='X'){
            player->life_point--;
            player->score-=15;
            player->last_move_status = -1;
        }
        if(map[player->corpse->L+1][player->corpse->C]==' '){
            
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L+1][player->corpse->C]=='F'){
            fruit_eated = 1;
            player->score+=5;
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L+1][player->corpse->C]=='C'){
            fruit_eated = 1;
            player->score+=3;
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L+1][player->corpse->C]=='B'){
            fruit_eated = 1;
            player->score+=2;
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L+1][player->corpse->C]=='P'){
            fruit_eated = 1;
            player->score+=1;
            //We update the map value
            map[player->corpse->L+1][player->corpse->C]= player->id+' ';
            //We stor the old value of the head
            old_L = head->L;
            old_C = head->C;
            head->L = head->L+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        player->last_move = 0;
        if(player->C_last == player->corpse->C && player->L_last == player->corpse->L){
            player->no_move = 1;
        }
        if(player->C_last != player->corpse->C || player->L_last != player->corpse->L){
            player->no_move = 0;
        }
        player->C_last = player->corpse->C;
        player->L_last = player->corpse->L;
        pthread_mutex_unlock(& mutex_snake);
    }
    
    //Top direction
    if(direction == 1){
        //printf("TOP");
        pthread_mutex_lock(& mutex_snake);
        if(map[player->corpse->L-1][player->corpse->C]=='X'){
            player->life_point--;
            player->score-=15;
            player->last_move_status = -1;
        }
        if(map[player->corpse->L-1][player->corpse->C]==' '){
            
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L-1][player->corpse->C]=='F'){
            fruit_eated = 1;
            player->score+=5;
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L-1][player->corpse->C]=='C'){
            fruit_eated = 1;
            player->score+=3;
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L-1][player->corpse->C]=='B'){
            fruit_eated = 1;
            player->score+=2;
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L-1][player->corpse->C]=='P'){
            fruit_eated = 1;
            player->score+=1;
            map[player->corpse->L-1][player->corpse->C]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->L = head->L-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        player->last_move = 1;
        if(player->C_last == player->corpse->C && player->L_last == player->corpse->L){
            player->no_move = 1;
        }
        player->C_last = player->corpse->C;
        player->L_last = player->corpse->L;
        
        pthread_mutex_unlock(& mutex_snake);
    }
    
    //Right direction
    if(direction == 2){
        //printf("RIGHT");
        pthread_mutex_lock(& mutex_snake);
        if(map[player->corpse->L][player->corpse->C+1]=='X'){
            player->life_point--;
            player->score-=15;
            player->last_move_status = -1;
        }
        if(map[player->corpse->L][player->corpse->C+1]==' '){

            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }
        
        if(map[player->corpse->L][player->corpse->C+1]=='F'){
            fruit_eated = 1;
            player->score+=5;
            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L][player->corpse->C+1]=='C'){
            fruit_eated = 1;
            player->score+=3;
            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L][player->corpse->C+1]=='B'){
            fruit_eated = 1;
            player->score+=2;
            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L][player->corpse->C+1]=='P'){
            fruit_eated = 1;
            player->score+=1;
            map[player->corpse->L][player->corpse->C+1]= player->id+'0';
            old_L = head->L;
            old_C = head->C;
            head->C = head->C+1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        player->last_move = 2;
        if(player->C_last == player->corpse->C && player->L_last == player->corpse->L){
            player->no_move = 1;
        }
        player->C_last = player->corpse->C;
        player->L_last = player->corpse->L;
        pthread_mutex_unlock(& mutex_snake);
    }

    //Left direction
    if(direction == 3){
        //printf("LEFT");
        pthread_mutex_lock(& mutex_snake);
        if(map[player->corpse->L][player->corpse->C-1]=='X'){
            player->life_point--;
            player->score-=15;
            player->last_move_status = -1;
        }
        if(map[player->corpse->L][player->corpse->C-1]==' '){
            
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }  

        if(map[player->corpse->L][player->corpse->C-1]=='F'){
            fruit_eated = 1;
            player->score+=5;
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L][player->corpse->C-1]=='C'){
            fruit_eated = 1;
            player->score+=3;
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L][player->corpse->C-1]=='B'){
            fruit_eated = 1;
            player->score+=2;
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }

        if(map[player->corpse->L][player->corpse->C-1]=='P'){
            fruit_eated = 1;
            player->score+=1;
            old_L = head->L;
            old_C = head->C;
            map[player->corpse->L][player->corpse->C-1]= player->id+'0';
            head->C = head->C-1;
            move_done = 1;
            //Decrease the speed of the snake by increasing his sleeping time
            player->speed+=0.1;
        }    
        player->last_move = 3;
        if(player->C_last == player->corpse->C && player->L_last == player->corpse->L){
            player->no_move = 1;
        }
        player->C_last = player->corpse->C;
        player->L_last = player->corpse->L;
        pthread_mutex_unlock(& mutex_snake);      
    }
    if(fruit_eated){
        int part_added = 0;
        struct part_of_snake* head = player->corpse;
        part_of_snake *current_node = head;
        while ( current_node != NULL && current_node->next != NULL) {
            current_node = current_node->next;
        }
        
        //Add the new part of the snake at the end of the linked list
        if(map[current_node->L][current_node->C+1] == ' '& !part_added){
            part_of_snake *new_node = (part_of_snake *) malloc(sizeof(part_of_snake));
            new_node->C = current_node->C+1;
            new_node->L = current_node->L;
            new_node->next= NULL;
            current_node->next = new_node;
            part_added = 1;
        }

        if(map[current_node->L][current_node->C-1] == ' '& !part_added){
            part_of_snake *new_node = (part_of_snake *) malloc(sizeof(part_of_snake));
            new_node->C = current_node->C-1;
            new_node->L = current_node->L;
            new_node->next= NULL;
            current_node->next = new_node;
            part_added = 1;
        }

        if(map[current_node->L+1][current_node->C] == ' '& !part_added){
            part_of_snake *new_node = (part_of_snake *) malloc(sizeof(part_of_snake));
            new_node->C = current_node->C;
            new_node->L = current_node->L+1;
            new_node->next= NULL;
            current_node->next = new_node;
            part_added = 1;
        }

        if(map[current_node->L-1][current_node->C] == ' '& !part_added){
            part_of_snake *new_node = (part_of_snake *) malloc(sizeof(part_of_snake));
            new_node->C = current_node->C;
            new_node->L = current_node->L-1;
            new_node->next= NULL;
            current_node->next = new_node;
            part_added = 1;
        }
        
    }
    if(move_done){

        //Once the move done we update value of all the parts of the snake
        struct part_of_snake *current_part = player->corpse;
        pthread_mutex_lock(& mutex_snake);
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
        pthread_mutex_unlock(& mutex_snake);

    
    }
    
}
//Function that check if a fruit is already placed in the grid
int there_is_fruit(char **map,int nb_ligne, int nb_col){
    //Iterate throught the map and check if a fruit is already present
    for(int col = 0; col < nb_col; col ++){
        
        for(int ligne = 0; ligne < nb_ligne; ligne ++){
            if(map[ligne][col]=='F'){
                return 1;
                }

            if(map[ligne][col]=='C'){
                return 1;
            }

            if(map[ligne][col]=='B'){
                return 1;
            }

            if(map[ligne][col]=='P'){
                return 1;
            }
        }
    }
    return 0;
}
void generate_fruit(char **map,int nb_ligne, int nb_col,fruit *current_fruit){

    if(!there_is_fruit(map,nb_ligne, nb_col)){

        srand(time(NULL));
        int fruit_placed = 0;
        int num_fruit = rand() % 4 + 0;

        pthread_mutex_lock(& mutex_snake);
        while(!fruit_placed){
            int rand_L = rand() % nb_ligne + 0;
            int rand_C = rand() % nb_col + 0;
            if(map[rand_L][rand_C]==' '){

                if(num_fruit == 0){
                    map[rand_L][rand_C]='F';
                    current_fruit->fruit_type = 'F';
                    fruit_placed = 1;
                }

                if(num_fruit == 1){
                    map[rand_L][rand_C]='C';
                    current_fruit->fruit_type = 'C';
                    fruit_placed = 1;
                }

                if(num_fruit == 2){
                    map[rand_L][rand_C]='B';
                    current_fruit->fruit_type = 'B';
                    fruit_placed = 1;
                }

                if(num_fruit == 3){
                    map[rand_L][rand_C]='P';
                    current_fruit->fruit_type = 'P';
                    fruit_placed = 1;
                }
                current_fruit->C = rand_C;
                current_fruit->L = rand_L;
            }
        }
        pthread_mutex_unlock(& mutex_snake);
    }
}
//Function to remove dead snake
void remove_snake(snake *player, char **map){
    struct part_of_snake *current_part = player->corpse;
    pthread_mutex_lock(& mutex_snake);
    while (current_part->next != NULL){
        map[current_part->L][current_part->C] = ' ';
        current_part = current_part->next;
    }
    map[current_part->L][current_part->C] = ' ';
    pthread_mutex_unlock(& mutex_snake);
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