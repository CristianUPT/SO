#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>                                                             
#include <fcntl.h>                                                              
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
/*
void citire_director(char *director){

  DIR *dir;
  dir = opendir(director);
  struct dirent *entry;
  struct stat st_file;
  char str[500];
  while((entry = readdir(dir)) != NULL){
    printf("%s", entry->d_name);
    sprintf(str, "%s/%s", director, entry->d_name);
    stat(str, &st_file);
  }
}
*/
int main(int argc, char *argv[]){

  if(argc != 2){
    printf("Usage %s <fisier_intrare>" , argv[0]);
    exit(-1);
  }

  int input_file = open(argv[1], O_RDONLY);

  if(input_file == -1){
    printf("CAN'T OPEN FILE \n");
    exit(-1);
  }

  int output_file = open("statistica.txt" , O_WRONLY | O_CREAT | O_TRUNC | S_IRUSR | S_IWUSR);
  if(output_file == -1){
    printf("CAN'T OPEN OUTPUT FILE \n");
    exit(-1);
  }

  char buffer[256];
  int dim = printf(buffer, "Nume fisier: %s \n" , argv[1]);
  if(write(output_file, buffer, dim) == -1){
  printf("CANT WRITE IN OUTPUT FILE \n");
  close(output_file);
  exit(-1);
  }

  /*
  lseek(file_descriptor, 18, SEEK_SET);
    int latime;
    read(file_d, &latime, sizeof(int));

    citire_director(argv[i]);
  */
    close(input_file);
    close(output_file);

    return 0;
}
