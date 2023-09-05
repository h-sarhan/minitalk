#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

char c = 0;

void    sighandler(int sig, siginfo_t *info, void *context)
{
    (void) context;

    if (sig == SIGUSR1)
        c++;
    else if (sig == SIGUSR2)
    {
        write(1, &c, 1);
        c = 0;
    }
    kill(info->si_pid, SIGUSR1);
}

int main()
{
    struct sigaction        sa;

    printf("Server pid: %d\n", getpid());
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sighandler; 
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
}