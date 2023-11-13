#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

typedef struct Header
{
  char name[10];
}Header;

int main(int argc, char *argv[])
{
  if(argc !=2 )
    {
      printf("Usage %s <fisier_intrare>\n", argv[1]);
      exit (-1);
    }

  int fd_input=open(argv[1], O_RDONLY);
  if(fd_input==-1)
    {
      perror("Eroare la deschiderea fisierului de intrare");
      exit (-1);
    }
  close(fd_input);


  int fd_statistica=open("output_file.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if(fd_statistica==-1)
    {
      perror("Eroare la deschiderea fisierului de statistica");
      exit (-1);
    }

  
  char buffer[256];
  int n=sprintf(buffer, "Nume fis: %s\n", argv[1]);
  if(write(fd_statistica, buffer,n)==-1)
    {
      perror("Eroare la scriere in fis");
      close(fd_statistica);
      exit (-1);
    }

  int inaltime, lungime;
  if(read(fd_input, buffer, 18) !=-1)
    {
      read(fd_input, &inaltime, 4);
      read(fd_input, &lungime, 4);
    }

  n=sprintf(buffer, "Inaltime: %d\nLungime: %d\n", inaltime, lungime);
  if(write(fd_statistica, buffer,n)==-1)
    {
      perror("Eroare la scriere in fis");
      close(fd_statistica);
      exit (-1);
    }
  close(fd_statistica);
  return 0;
}
