#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *file;
  if (argc < 2) {
    printf("Usage: %s FILENAME\n", argv[0]);
    exit(1);
  }
  file = fopen(argv[1], "r");
  if( file == NULL) { exit(1);}
  int count = 0;
  char a = fgetc(file);
  char last = a;
  while(1){
    if(a == last){count++;}
    else{fwrite(&count, sizeof(int), 1, stdout); printf("%c", last); count=1;}
    last = a;
    if(feof(file)){break;}
    a = fgetc(file);
  }
  fclose(file);
  return 0;
}
