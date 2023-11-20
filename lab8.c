#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <time.h>

void print_permissions(mode_t mode)
{
    printf("drepturi de acces user: %c%c%c\n", (mode & S_IRUSR) ? 'R' : '-', (mode & S_IWUSR) ? 'W' : '-', (mode & S_IXUSR) ? 'X' : '-');
    printf("drepturi de acces grup: %c%c%c\n", (mode & S_IRGRP) ? 'R' : '-', (mode & S_IWGRP) ? 'W' : '-', (mode & S_IXGRP) ? 'X' : '-');
    printf("drepturi de acces altii: %c%c%c\n", (mode & S_IROTH) ? 'R' : '-', (mode & S_IWOTH) ? 'W' : '-', (mode & S_IXOTH) ? 'X' : '-');
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <fisier_intrare>\n", argv[0]);
        exit(-1);
    }

    int fd_input = open(argv[1], O_RDONLY);
    if (fd_input == -1)
    {
        perror("Eroare la deschiderea fisierului de intrare");
        exit(-1);
    }

    struct stat file_stat;
    if (fstat(fd_input, &file_stat) == -1)
    {
        perror("Eroare la obtinerea informatiilor despre fisier");
        close(fd_input);
        exit(-1);
    }

    char output_filename[] = "statistica.txt";
    int fd_statistica = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd_statistica == -1)
    {
        perror("Eroare la deschiderea fisierului de statistica");
        close(fd_input);
        exit(-1);
    }

    char buffer[256];
    int n = snprintf(buffer, sizeof(buffer), "nume fisier: %s\n", argv[1]);
    if (write(fd_statistica, buffer, n) == -1)
    {
        perror("Eroare la scriere in fisierul de statistica");
        close(fd_statistica);
        close(fd_input);
        exit(-1);
    }

    n = snprintf(buffer, sizeof(buffer), "inaltime: %ld\nlungime: %ld\ndimensiune: %ld\n", file_stat.st_size, file_stat.st_size, file_stat.st_size);
    if (write(fd_statistica, buffer, n) == -1)
    {
        perror("Eroare la scriere in fisierul de statistica");
        close(fd_statistica);
        close(fd_input);
        exit(-1);
    }

    struct passwd *pwd = getpwuid(file_stat.st_uid);
    if (pwd != NULL)
    {
        n = snprintf(buffer, sizeof(buffer), "identificatorul utilizatorului: %d\n", pwd->pw_uid);
        if (write(fd_statistica, buffer, n) == -1)
        {
            perror("Eroare la scriere in fisierul de statistica");
            close(fd_statistica);
            close(fd_input);
            exit(-1);
        }
    }

    char date_modified[20];
    strftime(date_modified, sizeof(date_modified), "%d.%m.%Y", localtime(&(file_stat.st_mtime)));
    n = snprintf(buffer, sizeof(buffer), "timpul ultimei modificari: %s\n", date_modified);
    if (write(fd_statistica, buffer, n) == -1)
    {
        perror("Eroare la scriere in fisierul de statistica");
        close(fd_statistica);
        close(fd_input);
        exit(-1);
    }

    n = snprintf(buffer, sizeof(buffer), "contorul de legaturi: %ld\n", file_stat.st_nlink);
    if (write(fd_statistica, buffer, n) == -1)
    {
        perror("Eroare la scriere in fisierul de statistica");
        close(fd_statistica);
        close(fd_input);
        exit(-1);
    }

    print_permissions(file_stat.st_mode);

    close(fd_statistica);
    close(fd_input);

    return 0;