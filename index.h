#ifndef INDEX_H
#define INDEX_H

#include <sys/types.h>
#include <dirent.h>

typedef union ifile_ {
  FILE *f;
  DIR  *d;
} ifile;

void usage();

ifile f;

#endif
