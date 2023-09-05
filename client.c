#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

bool ack = false;

void acknowledgement(int sig, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;
    if (sig == SIGUSR1)
        ack = true;
}

void    send_char(unsigned char c, int pid)
{
    unsigned char i = 0;

    while (i < c)
    {
        kill(pid, SIGUSR1);
        while (!ack);
        ack = false;
        i++;
    }
    kill(pid, SIGUSR2);
    while (!ack);
    ack = false;
}

int main(int argc, char **argv)
{
    struct sigaction        sa;

    if (argc != 3)
        return EXIT_FAILURE;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = acknowledgement;
    sigaction(SIGUSR1, &sa, NULL);
    int i = 0;

    while (argv[2][i])
    {
        send_char(argv[2][i], atoi(argv[1]));
        i++;
    }
}