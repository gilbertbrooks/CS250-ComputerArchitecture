#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265358979323846
//Pizza Linked List
struct pizza{

    char name[256] ;
    float diameter;
    float cost;
    float ppd;
    struct pizza* next;

};

void printList(struct pizza *printme)
{
    struct pizza *temp; //to free memory later
    //struct pizza *temp = printme;
    while(printme != NULL)
    {
        printf("%s %f\n",printme->name, printme->ppd);
        temp = printme;
        printme = printme->next;
        free(temp);
    }
}


void createListWithMalloc(struct pizza** head, char someName [256],float a,float b){

  struct pizza* new_node = (struct pizza*) malloc(sizeof(pizza));

  char buffer[256];
  strcpy(buffer,someName);
  buffer[strcspn(someName, "\n")] = 0;

  strcpy(new_node->name,buffer);

  // - Computing Pizza Per Dollar

  new_node->diameter  = a;
  new_node->cost  = b;

  a = (a*a)*(PI/4);
  new_node->ppd  = a/b;
  new_node->next = (*head);
  (*head) = new_node;

  //free(new_node);
}

void sortNodes(struct pizza**, struct pizza*);

void sort(struct pizza **head)
{
    struct pizza *sorted = NULL;
    struct pizza *current = *head;
    while (current != NULL)
    {
        struct pizza *next = current->next;
        sortNodes(&sorted, current);
        current = next;
    }
    *head = sorted;
}

void sortNodes(struct pizza** head, struct pizza* new_node)
{
    struct pizza* current;

    //sort descending based on ppd (highest to lowest)
    if (*head == NULL || (*head)->ppd < new_node->ppd)
    {
        new_node->next = *head;
        *head = new_node;
    }
    if ((*head)->ppd == new_node->ppd){
      //if head comes b4 new_node alphabetically
      if (strcmp((*head)->name,new_node->name) < 0){

        printf("%s\n", "hello from other side");

        new_node->next = *head;
        *head = new_node;
      }
    }

    else
    {
        current = *head;
        while (current->next!=NULL &&
               current->next->ppd > new_node->ppd)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}


int main (int argc,char* argv[]){

    struct pizza *starter = NULL;
    char my_str[256];
    FILE *fp = fopen(argv[1], "r");
    char* str;
    int c;

    if (fp!=NULL) {

        if (fp) {

            // read file and pass results to push function
            while(fgets(my_str,256,fp)!=0){

                char end [256];
                strncpy(end,my_str,256);
                int ret = strcmp(end,"DONE\n");
                if (ret == 0) {
                    break;
                }

                else{

                    char nameOfPizza [256];
                    float diameter;
                    float cost;

                    //set values

                    sscanf("%s",my_str,nameOfPizza);
                    strcpy(nameOfPizza,my_str);

                    sscanf("%f",fgets(my_str,256,fp),diameter);
                    diameter = atof(my_str);

                    sscanf("%f",fgets(my_str,256,fp), cost);
                    cost = atof(my_str);

                    //hack city for when evil input is passed in

                    if (cost == 0.00 || diameter == 0.00){
                        cost = 1;
                        diameter =0;
                    }

                    // createLL(&starter,nameOfPizza,diameter,cost);
                    createListWithMalloc(&starter,nameOfPizza,diameter,cost);
                }
            }
        }

        fclose(fp);
    }
    else{
        int size = ftell(fp);

        if (0 == size) {
            printf("PIZZA FILE IS EMPTY\n");
        }
    }
    sort(&starter);
    printList(starter);
    return 0;
}
