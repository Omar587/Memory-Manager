#include <stdio.h>
#include <stdlib.h>
#include "memManager.h"
#include "freeHelper.h"
#include "mallocHelper.h"




#define lastByte 196606/2;




/*Combines the forward chunk with the current chunk
only if the forward chunk is free

the paramater will be provided from the myFree function,
the pointer points to the ara of memory that will freed.
Will combine chunk if the right neighbour is free

*/

void combineRightNeighbour(RELP *p){

RELP ogChunkVal = *p; //original chunk value  
RELP rightChunkVal= *(p+ ogChunkVal/2); //Fsize of the chunk that will be combined

 
if ( *p % 4 ==0 ){   //checks if current chunk is free


if ( *(p+ ogChunkVal/2 ) % 4 == 0){   //makes sure the fsizse of right chunk is free

*p=rightChunkVal+ ogChunkVal; //Fsize of combined chunk
*(p+ ogChunkVal/2  )=0;//make Fsize of right neighbour 0
*(p+ ogChunkVal/2 -1 )=0; //make Esize of current chunk 0;
*(p+ ogChunkVal/2 + rightChunkVal/2 -1)= rightChunkVal+ ogChunkVal; //Esize of the combined chunk

}
}
}






/*The purpose of this function is to take a chunk that 
is going to be freed. Then the backward chunk of the array
is checked if it is free. If the chunk is free the
current and the backward chunk is combined   

paramater: RELP pointer

returns nothing

*/
void checkLeftNeighbour(RELP *p){


RELP *LeftChunk= (RELP*)myMemory; 
RELP *MiddleChunk= (RELP*)myMemory;  

LeftChunk=p;
MiddleChunk=p;

LeftChunk= LeftChunk-1;

RELP Index=(char*)LeftChunk-myMemory +2;

if (Index != 4){  //Does not point to the header


RELP LeftChunkSize=  *LeftChunk;


if  ( *LeftChunk   % 4 == 0 ){

RELP newSizeL=*LeftChunk + *MiddleChunk; //new size of combined chunk

*(LeftChunk -LeftChunkSize/2 +1)=  *LeftChunk + *MiddleChunk; //fsize for new chunk

RELP mcsize= *MiddleChunk; //grabs current chunk value
*MiddleChunk=0;  //clears array part

*(MiddleChunk + mcsize/2 -1  )=newSizeL; //Esize of the freechunk   

*(MiddleChunk-1)=0; //clears array part


}


}


} 




