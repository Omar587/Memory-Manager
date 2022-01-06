


#ifndef FREEHELPER_H
#define FREEHELPER_H 


/*Combines the forward chunk with the current chunk
only if the forward chunk is free

the paramater will be provided from the myFree function
the pointer points to the ara of memory that will freed. 
Will combine chunk if the right neighbour is free.

*/

void combineRightNeighbour(RELP *p);



/*The purpose of this function is to take a chunk that 
is going to be freed. Then the backward chunk of the array
is checked if it is free. If the chunk is free the
current and the backward chunk is combined   

paramater: RELP pointer

returns nothing

*/
void checkLeftNeighbour(RELP *p);

#endif
