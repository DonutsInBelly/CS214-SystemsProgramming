#include <stdio.h>
#include <stdlib.h>
#include "lols.h"

void worker(FileData* data) {
  compress((void *) data);
}
