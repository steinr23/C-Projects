//Robert Stein
//Assignment 5 - Playlist.c
//COP 3502c

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum Bool {False , True} Bool;
typedef enum ChildType {Root, Left, Right} ChildType;

typedef struct Song {
  Bool accounted;
  int priority;
  int entry;
  int length;
  char name[25];
}Song;


typedef struct Node {
  /**
    A node in the heap.
    The data stored here is the tree pointer,
    and the key is stored in tree->rec.priority.
   **/
  struct Node* parent;
  struct Node* left;
  struct Node* right;
  Song song;
}Node;



typedef struct Heap {
  /**
    Basically a wrapper around heap.
   **/
  struct Node* root;
  struct Node* last;

  //I had used this to revert back
  //to previous last node but it doesn't
  //work with 2 or more deque in succession.
  //I am just scared deleting this will break something.
  struct Node* penUlt;
}Heap;


ChildType childType(Node* node) {
  /**
    Returns if the node is a Root , LeftChild or RightChild.
   **/
  if (node->parent == NULL) {
    return Root;
  }
  return (node->parent->left != NULL &&  node->parent->left->song.priority == node->song.priority) ? Left : Right;
}

Node* findLeftMost(Node* node) {
  /**
    Given a node, it keeps going
    left until a node is found
    whose left child is NULL,
    then it returns that node.
   **/
  if (node == NULL) {
    return NULL;
  }
  if (node->left == NULL) {
    return node;
  }
  return findLeftMost(node->left);
}

Node* findNextParent(Node* node) {
  /**
    Finds the next position to
    insert the new node.
   **/
  while (node != NULL) {
    ChildType ct = childType(node);
    switch(ct){
      case Root:
        return NULL;
        break;
      case Left:
        if (node->parent->right == NULL) {
          return node->parent;
        }
        return findLeftMost(node->parent->right);
        break;
      case Right:
        node = node->parent;
        break;
    }
  }
  return NULL;
}

void balanceHeap(Node* node) {
  /**
    Balances the heap using
    the algorithm described
    by the pdf
   **/
  if (node->parent == NULL) {
    return;
  }
  else if(node->parent->song.priority > node->song.priority) {
    Song song = node->song;
    node->song = node->parent->song;
    node->parent->song = song;
    balanceHeap(node->parent);
  }
}

void enqueue(Heap* heap, Song song) {
  /**
    Adds a tree to a heap using the
    algorithm described by the pdf.
   **/
  heap->penUlt = heap->last;
  if (heap->last == NULL) {
    heap->last = malloc(sizeof(Node));
    heap->root = heap->last;
    heap->last->song = song;
    heap->last->parent = heap->last->left = heap->last->right = NULL;
    return ;
  }


  Node* parent = findNextParent(heap->last);

  if (parent == NULL) {
    parent = findLeftMost(heap->root);
  }

  if (parent->left == NULL) {
    parent->left = malloc(sizeof(Node));
    parent->left->parent = parent;
    parent->left->left = parent->left->right = NULL;
    parent->left->song = song;
    heap->last = parent->left;
  }
  else{
    parent->right = malloc(sizeof(Node));
    parent->right->parent = parent;
    parent->right->left = parent->right->right = NULL;
    parent->right->song = song;
    heap->last = parent->right;
  }
  balanceHeap(heap->last);
}


void balanceDown(Node* root) {
  /**
    Balances the heap after a deque.
    The algorithm was discussed by the pdf.
   **/
  if (root == NULL){
    return;
  }
  if (root->left == NULL && root->right == NULL) {
    return;
  }
  if (root->left == NULL) {
    if (root->right->song.priority < root->song.priority) {
      Song song = root->right->song;
      root->right->song = root->song;
      root->song= song;
    }
  }
  else if (root->right == NULL){
    if (root->left->song.priority < root->song.priority) {
      Song song = root->left->song;
      root->left->song = root->song;
      root->song= song;
    }
  }
  else {
    if (root->left->song.priority < root->song.priority &&
        root->left->song.priority < root->right->song.priority) {
      Song song = root->left->song;
      root->left->song = root->song;
      root->song = song;
      balanceDown(root->left);
    }
    else if (root->right->song.priority < root->song.priority &&
        root->right->song.priority < root->left->song.priority) {
      Song song = root->right->song;
      root->right->song = root->song;
      root->song = song;
      balanceDown(root->right);
    }
  }
}


Node* findRightMost(Node* node) {
  /**
    Long lost of findLeftMost.
   **/
  if (node == NULL){
    return NULL;
  }
  if (node->right == NULL) {
    return node;
  }
  return findRightMost(node->right);
}

Node* findLeftCousin(Node* node) {
  /**
    Finds the node exactly left to
    the given node. Technically it could
    also return the brother.
   **/
  while(node != NULL){
    ChildType ct= childType(node);
    switch(ct){
      case Root:
        return NULL;
      case Left:
        node = node->parent;
        break;
      case Right:
        return findRightMost(node->parent->left);
    }
  }
  return NULL;
}


/**
   Sorting the data before inserting it into the priority queue is more or less useless because I used a heap
**/
Song deque(Heap* heap) {
  /**
    Returns the top of the queue
    and re-balances the heap.
   **/
  Song toReturn = heap->root->song;
  Song song = heap->root->song;
  heap->root->song = heap->last->song;
  ChildType ct = childType(heap->last);
  switch(ct){
    case Root:
      //freeTree(heap->root->tree);
      free(heap->root);
      heap->root = NULL;
      heap->last = NULL;
      heap->penUlt = NULL;
      return toReturn;
      break;
    case Left:
      heap->last->parent->left = NULL;
      break;
    case Right:
      heap->last->parent->right = NULL;
      break;
  }
  heap->last = heap->penUlt;
  heap->penUlt = findLeftCousin(heap->last);
  if (heap->penUlt == NULL) {
    heap->penUlt = findRightMost(heap->root);
  }
  balanceDown(heap->root);


  return toReturn;
}

Bool isEmpty(Heap heap) {
  /**
    Simple helper function.
   **/
  return (heap.last == NULL);
}

int getNextSong(Song *songs,int n) {
  Song song;
  int c;
  for(int i=0;i<n;i++){
    if (!songs[i].accounted) {
      song = songs[i];
      c = i;
      break;
    }
  }

  for(int i=0;i<n;i++){
    if (songs[i].entry < song.entry && !songs[i].accounted){
      song = songs[i];
      c = i;
    }
  }
  return c;
}

Bool allSongsAccountedFor(Song *songs,int n){
  for(int i=0;i<n;i++){
    if (!songs[i].accounted){
      return False;
    }
  }
  return True;
}

int main() {
  Heap heap;
  heap.last = NULL;
  heap.root = NULL;

  int n;
  scanf("%d", &n);
  Song* songs = malloc(sizeof(Song) * n);
  for(int i=0;i<n;i++){
    scanf("%d %d %s",&songs[i].entry,&songs[i].length,songs[i].name);
    songs[i].priority = i;
    songs[i].accounted = False;
  }

  int c= getNextSong(songs,n);
  songs[c].accounted = True;
  int currentTime = songs[c].entry + songs[c].length;

  while( (!isEmpty(heap)) || (!allSongsAccountedFor(songs,n))) {
    // Play and load new songs.
    puts(songs[c].name);

    //puts("Enqueueing:");
    while(!allSongsAccountedFor(songs,n)){
      int i = getNextSong(songs,n);
      if (songs[i].entry >= currentTime){
        break;
      }
      songs[i].accounted = True;
      //puts(songs[i].name);
      enqueue(&heap,songs[i]);
    }
    //printf("Current Time: %d\n",currentTime);
    //puts("\n\n");

    if (!isEmpty(heap)) {
      Song song = deque(&heap);
      c = song.priority;
      currentTime = currentTime + song.length;
    }
    else{
      c = getNextSong(songs,n);
      currentTime = songs[c].entry + songs[c].length;
      songs[c].accounted = True;
    }
  }
  puts(songs[c].name);

  free(songs);
}
