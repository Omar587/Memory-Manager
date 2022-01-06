

#ifndef MALLOCHELPER_H
#define MALLOCHELPER_H


/*GIVES LOCATION TO FREE CHUNK  
returns: RELP pointer location for the free chunk */
RELP *find_free_chunk();



/*Helper function for myMalloc
 goes through the list loooking for an exact size 
if there is an exact size that is free
turn the chunk into a used chunk 

Paramater:  size of desired allocation 
Returns relp pointer 
*/

RELP exactChunk(size_t size);






/*This function is responsible for 
splitting the free chunk.   
Paramater: size of desired allocation
Returns: RELP pointer location to memory*/ 
RELP allocate_chunk(size_t size);



/*Initilizes memory for the user must be used before malloc calls are made*/
void initializeMemory();


#endif
