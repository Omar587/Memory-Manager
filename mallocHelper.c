#include <stdio.h>
#include <stdlib.h>
#include "memManager.h"
#include "mallocHelper.h"
#include "freeHelper.h"

#define lastByte (196606/2)




/*GIVES LOCATION TO FREE CHUNK

Returns: RELP pointer location to free chunk */
RELP *find_free_chunk(){

RELP *p= (RELP*)myMemory;
RELP start= *p; //Start from the header points to next freeChunk


while ( *(p + start/2 +1) != 0){  

p = p + *p;
}

p= p+ *p/2;


return p;
}






/*Helper function for myMalloc 
goes through the list loooking for an exact size
if there is an exact size that is free
turn the chunk into a used chunk

Paramater:  size of desired allocation
Returns relp pointer

 */

RELP exactChunk(size_t size){

RELP *p= (RELP*)myMemory; //starts from header
int count=0;

int max=196606/2; 

while ( count !=max ){ //while not up to the end of the list

count++;

if ( *(p+count)==size) {  //if *p is the exact size


if ( ( *(p+count)  % 4 == 0)    &&  ( *(p+count +size/2 -1 ) %4==0 ) ){  //check if fsize and esize are free

*(p+count)=size+1; //MARK FSIZED AS USED
RELP relpLocation =(char*)p-myMemory +2;
*(p+count +size/2 -1 )=size+1; //MARK ESIZE AS USED

return relpLocation; //return the relp location

}
}
}

return 0; //If 0 is returned then there is no exact fit
}




/*This function is responsible for 
splitting the free chunk.

Paramater: size of desired allocation

Returns: RELP pointer location to memory
*/


RELP allocate_chunk(size_t size){

RELP *header= (RELP*)myMemory;
RELP *end= (RELP*)myMemory; 


RELP *freeChunk= (RELP*)myMemory;
freeChunk= find_free_chunk();

 
RELP leftOverChunk=  *freeChunk - size; //leftover chunk

freeChunk= find_free_chunk(); //pointer to freeChunk

*(freeChunk)= size+ 1; //Mark used Fsize of newly allocated chunk
*(freeChunk + size/2 -1) = size +1; //Marked as used Esize of newly allocated chunk


*(freeChunk + size/2 ) = leftOverChunk; //Fsize for leftover
*(end + lastByte )=leftOverChunk;//Esize for leftover end of the array


*header= *header +size; //FW header
*(header +1)= *(header+1 )+size; //BW header

RELP relpRetVal= *freeChunk;  //Location of used chunk


relpRetVal=(char*)freeChunk-myMemory +2;

return  relpRetVal;
}








/*Initilizes memory for the user must be used before malloc calls are made*/
void initializeMemory(){

myMemory = malloc(MAX_TOTAL_MEMORY);


if (myMemory==NULL){
    return;
}

RELP *p= (RELP*)myMemory;

//sets up the header
*(p)=4;
*(p+1)=4;

//Make the freechunk
unsigned int freeSize= (MAX_TOTAL_MEMORY -4);
*(p +  2)= freeSize; //Fsize

*(p+ lastByte)=freeSize; //Places the size at the very last byte



 return;   
}



