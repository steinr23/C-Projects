//Robert Stein
//Assignment 4 - Doughnuts.c
//COP 3502c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_MAX 100000000

typedef struct NameList{
  //A linked list of names.
  char name[25];
  struct NameList* next;
}NameList;

typedef struct Node{
  //A linked list of nodes that will be a part of a hash table.
  /**
     Here the vertical lines are of the hash table and the horizontal are the linked lists.
    | - - ->
    | - - ->
    | - - ->
    | - - ->
    | - - ->
    | - - ->
  **/
  char name[25];
  NameList *nameList;
  int count;
  struct Node* next;
}Node;

//The following two functions are borowed from https://www.geeksforgeeks.org/c-program-sort-array-names-strings/
static int myCompare (const void * a, const void * b)
{
    return strcmp (*(const char **) a, *(const char **) b);
}
void sort(char *arr[], int n)
{
    qsort (arr, n, sizeof (const char *), myCompare);
}

//Borrowed from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(unsigned char *str){
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash % HASH_TABLE_MAX;
}

bool nameExists(NameList* node, char* name) {
  //Checks if name exists
  if (node == NULL) {
    return false;
  }
  return (strcmp(node->name,name) == 0 ) || nameExists(node->next,name);
}

void printNames(NameList* node) {
  if (node == NULL){
    return;
  }
  puts(node->name);
  printNames(node->next);
}

NameList* addName(NameList* node, char * name) {
  if (nameExists(node,name)) {
    return node;
  }
  NameList* head = malloc(sizeof(NameList));
  strcpy(head->name,name);
  head->next = node;
  return head;
}

int countNames(NameList* node){
  if (node == NULL){
    return 0;
  }
  return 1 + countNames(node->next);
}

Node* addNode(Node* node,Node* toAdd) {
  if (node == NULL) {
    return toAdd;
  }
  toAdd->next = node;
  return toAdd;
}

bool nodeExists(Node* node, Node* elem) {
  if (node == NULL) {
    return false;
  }
  return (strcmp(node->name, elem->name) == 0) || nodeExists(node->next,elem);
}

Node* getNode(Node* node,char* name) {
  if (node == NULL) {
    return NULL;
  }
  if (strcmp(node->name,name) == 0) {
    return node;
  }
  return getNode(node->next,name);
}

Node* doughnutTable[HASH_TABLE_MAX];
Node* shopTable[HASH_TABLE_MAX];

int main() {
  for (int i=0; i<HASH_TABLE_MAX; i++) {
    doughnutTable[i] = NULL;
    shopTable[i] = NULL;
  }
  while (1) {
    int option;
    scanf("%d", &option);
    if (option == 0) {
      return 0;
    }

    else if (option == 1) {
      int n,m;
      scanf("%d %d",&n,&m);
      char ** donuts = malloc(sizeof(char*) * n);
      char ** shops  = malloc(sizeof(char*) * m);

      for (int i=0; i<n; i++){
        donuts[i] = malloc(sizeof(char) * 25);
        scanf("%s",donuts[i]);
        unsigned long h = hash(donuts[i]);
        Node* donut = malloc(sizeof(Node));
        donut->next = NULL;
        strcpy(donut->name,donuts[i]);
        donut->nameList = NULL;
        donut->count = 0;
        if (!nodeExists(doughnutTable[h],donut))
          doughnutTable[h] = addNode(doughnutTable[h],donut);
      }

      for (int i=0; i<m; i++) {
        shops[i] = malloc(sizeof(char) * 25);
        scanf("%s", shops[i]);
        unsigned long h = hash(shops[i]);
        Node* shop = malloc(sizeof(Node));
        shop->next = NULL;
        strcpy(shop->name,shops[i]);
        shop->nameList = NULL;
        shop->count = 0;
        if (!nodeExists(shopTable[h],shop))
          shopTable[h] = addNode(shopTable[h],shop);
      }

      for (int i=0; i<n;  i++) {
        for (int j=0; j<m; j++) {
          unsigned long h = hash(donuts[i]);
          Node* donut = getNode(doughnutTable[h],donuts[i]);
          donut->nameList = addName(donut->nameList,shops[j]);
          donut->count++;
        }
      }

      for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
          unsigned long h = hash(shops[i]);
          Node* shop = getNode(shopTable[h],shops[i]);
          shop->nameList = addName(shop->nameList,donuts[j]);
          shop->count++;
        }
      }

      for (int i=0; i<n; i++) {
        free(donuts[i]);
      }
      for (int i=0; i<m; i++) {
        free(shops[i]);
      }
      free(donuts);
      free(shops);

    }

    else if(option == 2) {
      char name[25];
      scanf("%s",name);
      unsigned long h = hash(name);
      Node* donut = getNode(doughnutTable[h],name);
      if (donut == NULL) {
        puts("0");
        continue;
      }
      int count = countNames(donut->nameList);
      printf("%d\n",count);

      NameList* temp = donut->nameList;

      char ** names = malloc(sizeof(char*) * count);
      for (int i=0; i<count; i++) {
        names[i] = malloc(sizeof(char) * 25);
        strcpy(names[i],temp->name);
        temp = temp->next;
      }
      sort(names,count);
      for (int i=0; i<count; i++) {
        puts(names[i]);
        free(names[i]);
     }
     free(names);
    }

    else if(option == 3) {
      char name[25];
      scanf("%s",name);
      unsigned long h = hash(name);
      Node* shop = getNode(shopTable[h],name);
       if (shop == NULL) {
        puts("0");
        continue;
      }
      int count = countNames(shop->nameList);
      printf("%d\n",count);

      NameList* temp = shop->nameList;

      char ** names = malloc(sizeof(char*) * count);
      for (int i=0; i<count; i++) {
        names[i] = malloc(sizeof(char) * 25);
        strcpy(names[i],temp->name);
        temp = temp->next;
      }
      sort(names,count);
      for (int i=0; i<count; i++) {
        puts(names[i]);
        free(names[i]);
     }
     free(names);
    }
  }
}
