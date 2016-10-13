#ifndef _mymalloc_h
#define _mymalloc_h

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

/*
void * malloc(size_t size);
void free();
*/

#endif
