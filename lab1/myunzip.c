#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *file;
  if (argc < 2) {
    printf("Usage: %s FILENAME\n", argv[0]);
    exit(1);
  }
  file = fopen(argv[1], "r");
  if(file == NULL) {exit(1);}
  char a;
  int j;
  while(1){
    fread(&j, sizeof(int), 1, file);
    if(feof(file)){break;}
    fread(&a, sizeof(char), 1, file);
    if(feof(file)){break;}

    for(int i=0; i<j; i++){
      printf("%c", a);
    }
  }
  fclose(file);
  return 0;
}
