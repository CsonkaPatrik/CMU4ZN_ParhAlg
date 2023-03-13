#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int main(){
int array[10];
FILE *fptr;

fptr=fopen("randomNum.txt","w+");

if(fptr == NULL){
      printf("Error! Exiting...");
      exit(1);
}
for(int i=0;i<10;i++){
array[i] = (rand() %(1000 - 500 + 1)) + 500;
fprintf(fptr, "%d: %d\n", i+1, array[i]);
}

fclose(fptr);
}