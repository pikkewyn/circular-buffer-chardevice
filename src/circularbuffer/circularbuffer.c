/* Circular buffer example, keeps one slot open */

#include <stdlib.h> 
#include "circularbuffer.h"
 
void cbInit( struct CircularBuffer *cb, int size) {
    cb->size  = size + 1; /* include empty elem */
    cb->start = 0;
    cb->end   = 0;
    cb->elems = calloc(cb->size, sizeof(ElemType));
}
 
void cbFree( struct CircularBuffer *cb) {
    free(cb->elems); /* OK if null */
}
 
bool cbIsFull( struct CircularBuffer *cb) {
    return (cb->end + 1) % cb->size == cb->start;//najpierw reszta z dzielenia pozniej porownanie wynik 1 lub 0
}
 
bool cbIsEmpty( struct CircularBuffer *cb) {
    return cb->end == cb->start;
}
 //////////////////////////////////////////////////////////////////////////
/* Write an element, overwriting oldest element if buffer is full. App can
   choose to avoid the overwrite by checking cbIsFull(). */
void cbWrite( struct CircularBuffer *cb, ElemType elem) {
    cb->elems[cb->end] = elem;
    cb->end = (cb->end + 1) % cb->size;
    if (cb->end == cb->start)
        cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
}
 
/* Read oldest element. App must ensure !cbIsEmpty() first. */
ElemType cbRead( struct CircularBuffer *cb) {
	ElemType elem = cb->elems[cb->start];
    cb->start = (cb->start + 1) % cb->size;
    return elem;
}
 
