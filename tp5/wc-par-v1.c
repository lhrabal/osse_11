#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Count the number of newline in the specified file interval.
*/
void countNewline(char* f, int from, int to, int n_fork)
{
        int fd = open(f, O_RDONLY);
        int size = to - from;
        char buff[size];
        int counter = 0;
        lseek(fd, from, SEEK_SET);
        read(fd, buff, size);

        for (int i = 0; i < size; i++)
        {
            if (buff[i] == '\n')
                counter++;
        }
        printf("Fork %d : il y a %d '\\n'\n", n_fork, counter);
        close(fd);
}

int main(int argc, char const *argv[])
{
    char* f = argv[1];

    // get the size of the file
    struct stat st;
    stat(f,&st);
    long size = st.st_size;

    __pid_t pid[4];
    for (int i = 0; i < 4; i++)    
    {
        __pid_t* tmp = &pid[i];
        if (fork() == 0)
        {
            *tmp = getpid();
            break;
        }
    }

    __pid_t current_pid = getpid();

    if (current_pid == pid[0])
        countNewline(f, 0, size/4, 1);
    else if (current_pid == pid[1])
        countNewline(f, size/4, size/2, 2);
    else if (current_pid == pid[2])
        countNewline(f, size/2, (3*size)/4, 3);
    else if (current_pid == pid[3])
        countNewline(f, (3*size)/4, size, 4);

    for (int i = 0; i < 4; i++)    
    {
        wait(NULL);
    }

    return 0;
}
