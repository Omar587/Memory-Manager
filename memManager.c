#include <stdio.h>
#include <stdlib.h>
#include "memManager.h"
#define lastByte 196606/2;
#include "mallocHelper.h"
#include "freeHelper.h"




RELP myMalloc(size_t size){


 if (size % 4 != 0)  {       //make sure that multiples of 4's are only taken
  size += (4- size % 4); 

}
size=size+4;


 if (size > MAX_TOTAL_MEMORY){
 printf("%zu is too big value will not be allocated\n", size);  //check if size is more than whats availiable 
 return 0;
}


RELP exactLocation = exactChunk(size);

if (exactLocation == 0){  //if there is no exact chunk then split a chunk for memory
return allocate_chunk(size); //return the the chunk to the user

}else{
return exactLocation;  //return the allocation where the exact chunk was set to used

}

}




void myFree(RELP region){

RELP *p= (RELP*)myMemory;

p= p+ region/2 -1; //Points to the area of memory that will be freed



if ( *p % 4==0){
printf("Chunk is already free! ");  //Makes sure user can not free a chunkt that is already free
return;
}



*p= *p-1;  //make the flag equal to 0 marked as a free for Fsize

RELP getUserSpace= *p -2;  //how many bytes needed to reach the Esize

*(p + getUserSpace/2 )= *p; //make the flag equal to 0 marked as a free for Esize

checkLeftNeighbour(p); //will coalesnce chunks on the left side if a free chunk is availiable

combineRightNeighbour(p); //will coalesnce chunks on the right side if a free chunk is availiable 


}



/*Test function, place your mymalloc and myfree tests here
in order to test out the program.
*/


int test(){

//Mememory is too big nothing will be allocated
myMalloc(70000);

//17 is not a multiple of four will round up to 20
RELP p1=myMalloc(17);

//Making multiple myMalloc calls, will split the freechunk
//successfully marks chunk as used. +1 
RELP p2=myMalloc(16);
myMalloc(3); //round to 4 
myMalloc(8);
RELP p5=myMalloc(12);
myMalloc(30); //round to 36
myMalloc(30);
myMalloc(30);
myMalloc(77); //rounds up to 80
RELP p10=myMalloc(24);

//start testing bigger values
myMalloc(1200);
myMalloc(8000);
myMalloc(4000);
myMalloc(20000); 
myMalloc(1000);
myMalloc(1400);
myMalloc(980);
myMalloc(400);
myMalloc(200);
/*Start to free mmemory, chunk will be marked as free
the last two bits are 0 now. If there is a neighbour 
free chunk them the chunk will be combined  */ 

myFree(p1); //first memory block is freed
myFree(p2); //second memory block is freed. Since p1 is free the chunk will be coalesced 

myFree(p5); //The 5th memory block is freed
myMalloc(16); //The 5th memory block value is 16 and its free thus, there is an exact fit. Allocate the chunk and make it show as used.


myMalloc(40); // Since myFree(p1) and myFree(p2) resulted in a coalesced chunk of size 44 at the start of the list. 
             // myMalloc(40) will fit exactly in the coalesced free chunk. The chunk will be marked as used now.

myFree(p10); //frees the 10th block of memory[2;2R

return 0;
}


/*Writes a binary map*/
void memWrite(char* filename){

//write to memory
FILE *fout=fopen(filename, "wb");
fwrite(myMemory, sizeof(myMemory), MAX_TOTAL_MEMORY, fout);
fclose(fout);

//read to memory
fout=fopen(filename, "rb");
fread(myMemory,sizeof(myMemory), MAX_TOTAL_MEMORY, fout);
fclose(fout);

}



int main(){


initializeMemory();
test();
memWrite("memMap");

return 0;
}
