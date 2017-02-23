#include <stdlib.h>
#include <string.h> // memset
#include <stdio.h>
#include <math.h>
#include "CCRing.h"

#define PI 3.14159265

CCRing* createRing(unsigned long length) {

  CCRing* ring = (CCRing*) malloc(sizeof(CCRing));
  if (ring == NULL) {
    return NULL;
  }

  // size of the data in bytes
  size_t dataSize = length * sizeof(ccAudioDataType);

  // allocate data storage
  ring->data = (ccAudioDataType*) malloc(dataSize);
  if (ring->data == NULL) {
    free(ring);
    return NULL;
  }

  // initialize length
  ring->length = length;

  // initialize index to last spot in data array
  ring->index = length - 1;

  // initialize all data to zero
  memset(ring->data, 0, dataSize);

  return ring;
}

CCError freeRing(CCRing* pRing) {
  free(pRing->data);
  free(pRing);
  return ccNoError;
}

CCError ccAppend(CCRing* pRing, ccAudioDataType arr[], unsigned long length) {
  for (unsigned long i = 0; i < length; i++) {
    (pRing->index)++;
    if ((pRing->index) >= (pRing->length)){
      pRing->index = 0;
    }
    *(pRing->data + pRing->index) = *(arr + i);
  }
  return ccNoError;
}


CCError ccGenerateSin(CCRing* sinusoid, double cycles) {
  double distBetweenPoints = (2*PI)/sinusoid->length;
  for (unsigned long i = 0; i < sinusoid->length; ++i) {
    double n = i * distBetweenPoints;
    *(sinusoid->data + i) = sin(cycles * n);
  }
  return ccNoError;
}
