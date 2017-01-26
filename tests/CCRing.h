#ifndef CCRING_H
#define CCRING_H

#include <stdlib.h>

/* I'm making the assumption here that this is the same data
type that will be pased in to our audio processing callback.
at the time of writing, this is paFloat32 as defined by
portaudio */
typedef float ccAudioDataType;


typedef struct CCRing {
  ccAudioDataType* data;
  unsigned long length;
  int index_ring;
} CCRing;


typedef enum CCError {
  ccNoError = 0,
  ccError = -1000
} CCError;

extern int index_ring;

/* Create and initialize a CCRing struct.
On Success, return a CCRing pointer
On Failure, return NULL */
CCRing* createRing(unsigned long length);


/* Free a memory allocated by createRing
On Success, return ccNoError

Note: Calling free on NULL has no effect. The behavior of
calling free on an unfreeable pointer is undefined. I do not
think that this should ever fail - its behavior will either be
undefined, or it will succeed. */
CCError freeRing(CCRing* pRing);

/* Appends an array to the data of a CCRing. This array keeps
the size of the data in CCRing, and appends numbers on top of
where the pointer is located */
int ccAppend(CCRing* appendRing, ccAudioDataType array[], unsigned long length);
#endif