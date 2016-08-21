#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
 
#include <stdbool.h> 
 
/* Opaque buffer element type.  This would be defined by the application. */
typedef char ElemType;
 
/* Circular buffer object */
struct CircularBuffer {
    int         size;   /* maximum number of elements           */
    int         start;  /* index of oldest element              */
    int         end;    /* index at which to write new element  */
    ElemType   *elems;  /* vector of elements                   */
};
 
void cbInit(struct CircularBuffer *cb, int size);
 
void cbFree(struct CircularBuffer *cb);
 
bool cbIsFull(struct CircularBuffer *cb);
 
bool cbIsEmpty(struct CircularBuffer *cb);
 //////////////////////////////////////////////////////////////////////////
/* Write an element, overwriting oldest element if buffer is full. App can
   choose to avoid the overwrite by checking cbIsFull(). */
void cbWrite(struct CircularBuffer *cb, ElemType elem);
 
/* Read oldest element. App must ensure !cbIsEmpty() first. */
ElemType cbRead(struct CircularBuffer *cb);
 
#endif

