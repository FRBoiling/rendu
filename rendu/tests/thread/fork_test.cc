//
// Created by boil on 18-10-12.
//


#include <unistd.h>
#include <rendu/thread/CurrentThread.h>
#include <cstdio>

namespace
{
    __thread int x = 0;
}

void print()
{
    printf("pid=%d tid=%d x=%d\n", getpid(), rendu::thread::CurrentThread::tid(), x);
}

int main()
{
    printf("parent %d\n", getpid());
    print();
    x = 1;
    print();
    pid_t p = fork();

    if (p == 0)
    {
        printf("chlid %d\n", getpid());
        // child
        print();
        x = 2;
        print();

        if (fork() == 0)
        {
            printf("grandchlid %d\n", getpid());
            print();
            x = 3;
            print();
        }
    }
    else
    {
        // parent
        print();
    }
}