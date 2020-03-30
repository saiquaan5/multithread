#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

char messagess[] = "Hello Word";

void *dothread(void *data)
{
    cout << "Thread function is executing ..." << endl;
    cout << " Thread data is " << (char *)messagess << endl;

    sleep (3);
    strcpy(messagess, "Bye !");
    pthread_exit ((void *)" Thank you for using my thread");
}

int main()
{
    int res;
    pthread_t p_thread;
    void *thread_result;
    res = pthread_create(&p_thread,NULL,&dothread,&messagess);
    if (res)
    {
        perror ("Thread created error\n");
        exit (EXIT_FAILURE);
    }
    printf ("Waiting for thread to finish ...\n");
    res = pthread_join(p_thread,&thread_result);

    if (res != 0)
    {
        perror ("Thread wait error\n");
        exit(EXIT_FAILURE);
    }
    printf ("Thread completed, it returned %s \n", (char*) thread_result);
    printf ("Message is now %s \n", messagess);
    return 0;
}