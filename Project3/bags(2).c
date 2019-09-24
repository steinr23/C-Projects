//Robert Stein
//Assignment 3 - Bags
//COP 3502c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bag {
  /**
    A struct to represent a bag.
   **/
  int cost;
  int weight;
  char name[20];
}Bag;

typedef struct BagList {
  /**
    A linked list of aforementioned bags.
   **/
  Bag bag;
  struct BagList* next;
}BagList;

void printBL(BagList ** bl) {
  /**
    Helper function used for debugging.
   **/
  for(int i=0;i<10;i++) {
    if (bl[i] != NULL) {
      printf( "%d %d %d %s\n" ,i, bl[i]->bag.weight , bl[i]->bag.cost, bl[i]->bag.name);
    }
  }
  printf("\n\n");
}


int main() {
  // An array of linked lists.
  BagList** bl = malloc(sizeof(BagList*) * 1000);

  // Initialize the pointers to null.
  for (int i=0;i<1000;i++) {
    bl[i] = NULL;
  }

  while (1) {

    int type;
    scanf("%d",&type);

    if (type == -1) {
      // Simulate a sale
      int k,m,c;
      scanf("%d %d %d\n",&k,&m,&c);
      int spent = 0;
      BagList *temp = NULL, *base=NULL;
      while (bl[k] != NULL) {
        if ( bl[k]->bag.cost > m || bl[k]->bag.weight > c ) {
          break;
        }
        else {
          m -= bl[k]->bag.cost;
          c -= bl[k]->bag.weight;
          spent += bl[k]->bag.cost;

          if (temp == NULL) {
            temp = malloc(sizeof(BagList));
            base = temp;
            temp->bag = bl[k]->bag;
            temp->next = NULL;
          }
          else {
            temp->next = malloc(sizeof(BagList));
            temp->next->bag = bl[k]->bag;
            temp->next->next = NULL;
            temp = temp->next;
          }

          bl[k] = bl[k]->next;
        }
      }
      printf("%d ",spent);
      while (base != NULL) {
        printf("%s ",base->bag.name);
        base = base->next;
      }
      puts("");
    }
    else if (type == 0) {
      for (int i=0;i<1000;i++) {
        if (bl[i] != NULL) {
          free(bl[i]);
        }
      }
      free(bl);
      return 0;
    }
    else if(type == 1) {
      int k , n;
      scanf("%d %d\n",&k,&n);
      for (int i=0;i<n;i++) {
        int m,w;
        char name[20];
        scanf("%d %d %s",&m,&w,&name);
        Bag bag;
        bag.weight = w;
        bag.cost = m;
        strcpy(bag.name , name);
        BagList* temp = malloc(sizeof(BagList));
        temp->bag = bag;
        temp->next = bl[k];
        bl[k] = temp;
      }
    }
  }


  return 0;
}

