    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<math.h>

    struct node{
            int X, Y;
            int cur_PP, max_PP;
            char *name;

            struct node *next;
            int visited;

            int adj_size;
            struct node **adj_list;

            int healing;
        };

    int initial_range, jump_range, num_jumps, initial_power = 0;
    double power_reduction;

    struct node *first;
    struct node *current;
    struct node *temp;

    int best_healing;
    struct node **best_path;
    int **healing;

    struct node **temp_path;
    int **current_healing;

    struct node *check1;
    struct node *check2;




    void dfs(struct node* node, int hop, int num_jumpsL, int total_healing, struct node* from,int counter_array){

        int needed_healing;
        int reset_init_power = initial_power;

        if(node->visited == 1 || hop>num_jumpsL){
            node->visited = 0;
            return;
        }
        int count;

        //recording the path
        temp_path[counter_array] = node;


        /*printf("Printing from Node: From->%s",from->name);*/
        /*printf("Name: %s Hop: %d\n", node->name, hop);*/
        //healing calculation for each node

       /*printf("temp_path[%d]: %s  \n\n", counter_array, temp_path[counter_array]->name);*/



        if(counter_array == num_jumpsL-1){
                     int loop_C;
                     for(loop_C = 0; loop_C<num_jumpsL;loop_C++){


                        printf("Name: %s--->", temp_path[loop_C]->name); //??????????????????????????????????????????
                        needed_healing = temp_path[loop_C]->max_PP - temp_path[loop_C]->cur_PP;
                        if(needed_healing<initial_power)
                            temp_path[loop_C]->healing = needed_healing;
                        else
                            temp_path[loop_C]->healing = rint(initial_power);

                        initial_power = initial_power * (1-power_reduction);

                        //total healing
                        total_healing = total_healing + temp_path[loop_C]->healing;

                        //recording the healing
                        current_healing[loop_C] = temp_path[loop_C]->healing;

                        printf("\nCurrent healing[%d]: %d ", loop_C, current_healing[loop_C]);
                        printf("\nTotal Healing: %d\n\n ", total_healing);



                        }
                        //checking duplicate and rejecting the path
                        int dupC;
                        int dupC2;
                        for(dupC=0; dupC<num_jumpsL-1;dupC++){
                                for(dupC2=dupC+1;dupC2<num_jumpsL;dupC2++){
                                    check1 = temp_path[dupC];
                                    check2 = temp_path[dupC2];
                                    //printf("\n\nTemp Path: %s\n",temp_path[dupC]->name);
                                    if(check1 == check2)
                                        total_healing = 0;
                                        }

                     }



                     initial_power = reset_init_power;

                    int x;
                    if(total_healing>best_healing){

                    best_healing = total_healing;
                    for(x=0;x<num_jumpsL;x++){
                        best_path[x]=temp_path[x];
                        //printf("\n\nTemp Path: %s\n",temp_path[x]->name);
                        healing[x]=current_healing[x];
                    }
                }
        }


        for(count = 0; count<node->adj_size; count++){
            node->visited = 1;

            dfs(node->adj_list[count], hop+1, num_jumpsL,total_healing,node->next,counter_array+1);
        }


    }




    int main(){

        first = (struct node*) malloc(sizeof(struct node));
        current = (struct node*) malloc(sizeof(struct node));
        first = NULL;

        int x, y, cur_PP, max_PP;
        char *name = malloc(sizeof(char) * 100);



        printf("Please Enter your arguments in the following order:\n");
        printf("initial_range jump_range num_jumps intial_power power_reduction\n");

        scanf("%d %d %d %d %lf", &initial_range, &jump_range, &num_jumps, &initial_power, &power_reduction);
        printf("You entered: \n%d %d %d %d %lf \n", initial_range, jump_range, num_jumps, initial_power, power_reduction);

        FILE *f = fopen("input.txt","r");
        int node_counter = 0;


            while (fscanf(f, "%d %d %d %d %s", &x, &y, &cur_PP, &max_PP, name) != EOF){
            printf("Line %d: ", node_counter);
            printf("%d %d %d %d %s\n", x, y, cur_PP, max_PP, name);

            temp = (struct node*) malloc(sizeof(struct node));
            temp->X = x;
            temp->Y = y;
            temp->cur_PP = cur_PP;
            temp->max_PP = max_PP;
            temp->name = malloc(sizeof(char) * 100);
            strcpy(temp->name, name);

            if(node_counter <= 0){
                first = temp;
                first->next = NULL;
                current = first;
            }else{
                current->next = temp;
                current = temp;
                current->next = NULL;
            }

            node_counter++;
        }

            fclose(f);


        current = first;
        int looper = 0;
        printf("\n\n ***Printing from LinkedList ***\n");
        while(current){
            printf("Node: %d -> ", looper++);
            printf("%d %d %d %d %s\n", current->X, current->Y, current->cur_PP, current->max_PP, current->name);
            current = current->next;
        }

        struct node *outer_current = (struct node*) malloc(sizeof(struct node));
        struct node *inner_current = (struct node*) malloc(sizeof(struct node));

        outer_current = first;


        while(outer_current){
            int adj_counter = 0;
            inner_current = first;


            while(inner_current ){

    printf(" Diff 1: %d %d %d %d %d\n",outer_current->X, outer_current->Y, inner_current->X,inner_current->Y, (int)sqrt(((outer_current->X - inner_current->X)*(outer_current->X - inner_current->X)) + ((outer_current->Y - inner_current->Y)*(outer_current->Y - inner_current->Y))));


                if( outer_current != inner_current){
                if(sqrt(((outer_current->X - inner_current->X)*(outer_current->X - inner_current->X)) + ((outer_current->Y - inner_current->Y)*(outer_current->Y
                    - inner_current->Y))) <= jump_range){
                    adj_counter++;
                }
            }

                inner_current = inner_current->next;
            }

            outer_current->adj_size = adj_counter;
            outer_current = outer_current->next;
        }

        current = first;
        printf("\n\n ***Printing Adjecency node size ***\n");
        while(current){
            printf("Node: %d -> ", looper++);
            printf("%d %d %d %d %s %d\n", current->X, current->Y, current->cur_PP, current->max_PP, current->name, current->adj_size);
            current = current->next;
        }

        //putting the nodes onto adjacency list
        outer_current = first;

        while(outer_current){
            outer_current->adj_list = (struct node**)malloc(sizeof(struct node*) * outer_current->adj_size);
            int index_counter = 0;
            inner_current = first;


            while(inner_current){

                    if(outer_current == first){

                    }

                if( outer_current != inner_current){
                    if(sqrt(((outer_current->X - inner_current->X)*(outer_current->X - inner_current->X)) + ((outer_current->Y -
                    inner_current->Y)*(outer_current->Y - inner_current->Y))) <= jump_range){
                        outer_current->adj_list[index_counter++]=inner_current;
                    }
                }

                inner_current = inner_current->next;
            }
            outer_current = outer_current->next;
        }


        int listC = 0;
        current = first;
        printf("\n\n ***Printing Adjecency node List ***\n");
        while(current){
            printf("Node: %d -> ", looper++);
            printf("%d %d %d %d %s %d\n", current->X, current->Y, current->cur_PP, current->max_PP, current->name, current->adj_size);

            for(listC = 0; listC < current->adj_size; listC++)
                printf("%s; ", current->adj_list[listC]->name);

            printf("\n");
            current = current->next;
        }


        //callinf dfs
        printf("\n\n\n\nPrinting all paths\n");

        //


        temp_path = (struct node**)malloc(sizeof(struct node*) * num_jumps);
        current_healing =  (int**)malloc(sizeof(int*) * num_jumps);

        best_path = (struct node**)malloc(sizeof(struct node*) * num_jumps);
        healing =   (int**)malloc(sizeof(int*)*num_jumps);

        check1 = (struct node*) malloc(sizeof(struct node));
        check2 = (struct node*) malloc(sizeof(struct node));

        best_healing = 0;

        int counter;
        current = first;

        for(counter = 0; counter<node_counter; counter++){
                if(sqrt(((first->X - current->X)*(first->X - current->X)) +
                        ((first->Y - current->Y)*(first->Y - current->Y))) <= initial_range){
                            printf("First: %s  Next: %s\n\n", first->name, current->name);
                            dfs(current, 1, num_jumps,0, NULL,0);
                            current = current->next;

            }
        }

        int cX=0;
        printf("Best Path:");
        for(cX=0; cX<num_jumps;cX++){
            printf(" %s--->", best_path[cX]->name);
        }
        printf("\nBest Healing: %d", best_healing);


    printf("\nProgram End!\n");
    return 0;
    }
