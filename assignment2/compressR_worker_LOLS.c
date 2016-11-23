#include <stdio.h>
#include <stdlib.h>
#include "lols.h"
#include "utils.h"

void worker(FileData* data) {
  compress((void *) data);
}
