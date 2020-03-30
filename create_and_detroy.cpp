#include <pthread.h>
#include <iostream>
#include <unistd.h> // for sleep

using namespace std;


void* do_loop(void *data)
{
    int i;
    int *me = (int *)data;

    for(int i = 0; i < 5; i++)
    {
        sleep(1);
        cout << *me << "\tGot\t " << i << endl;
    }

    pthread_exit(NULL);
}

int main()
{
    int thr_id;
    pthread_t p_thread;
    int a =1;
    int b = 2;
    
    thr_id = pthread_create(&p_thread,NULL,&do_loop,&a);
    // CHay thread 1
    // Thread main()
    do_loop(&b);
    sleep(0.5);
    return 0;
}
