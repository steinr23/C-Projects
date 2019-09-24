//Robert Stein
//Assignment 2 - parasols.c

#include <stdio.h>
#include <stdlib.h>

typedef enum Bool {False, True} Bool;

int howMany(int n, const int* positions, int width){
  /**
    Returns the number of parasols required of a certain width.
   **/
    int starting = 0;
    int index = 0;
    int accountedFor = 0;
    int parasols = 0;

  while ( accountedFor != n ){
    parasols++;
    while ( index < n && positions[index] < positions[starting] + width){
      index++;
      accountedFor++;
    }
    starting = index;
  }
  return parasols;
}

int calcMinWidth(int n, int* positions, int k){
  /**
    Binary search to find the minimum width of the parasols.
   **/
 int lowBound = 1;
 int highBound = positions[n-1] - positions[0] + 1;

 while (True) {

    int midPt = (lowBound + highBound) / 2;
    int count = howMany(n,positions,midPt);
    int temp = howMany(n,positions,midPt);


   if (highBound == lowBound){
     return highBound;
   }

   else if ( highBound - lowBound == 1){
     int upper = howMany(n,positions,highBound),
         lower = howMany(n,positions,lowBound);
     if ( upper <= k && lower > upper){
       return highBound;
     }
     return lowBound;
   }


   if (count == k && temp != count){
     return midPt;
   }
   else if (count == k && temp == count){
     highBound = midPt;
   }
   else if ( count > k){
     lowBound = midPt;
   }
   else if (count < k){
     highBound = midPt;
   }
 }

 return 1;
}

int main(){
  int n, k;
  int *stools;
  scanf("%d %d",&n,&k);
  stools = malloc( sizeof(int) * n );
    if (stools == NULL){
        exit(1);
    }
  for (int i=0; i<n; i++){
    scanf("%d",&stools[i]);
  }

  printf("%d\n",calcMinWidth(n,stools,k));

}
