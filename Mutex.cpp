#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*Biến dữ liệu toàn cục có thể truy xuất bởi cả hai tuyến*/
int global_var;
pthread_mutex_t a_mutex; /*Khai báo biến mutex toàn cục*/
/*Khai báo các hàm dùng thực thi tuyến*/
void* do_thread1 (void* data);
void* do_thread2 (void* data);
/*Chương trình chính*/
int main ()
{
    int res;
    int i;
    pthread_t p_thread1;
    pthread_t p_thread2;

    /*Khởi tạo mutex*/
    res = pthread_mutex_init (&a_mutex, NULL);
    /*Bạn cũng có thể khởi tạo mutex như sau
    a_mutex = PTHREAD_MUTEX_INITIALIZER;
    */
    if (res != 0)
    {
        perror ("Mutex create error");
        exit (EXIT_FAILURE);
    }
    /*Tạo tuyến thứ nhất*/
    res = pthread_create (&p_thread1, NULL, do_thread1, NULL);
    if (res != 0)
    {
        perror ("Thread create error");
        exit (EXIT_FAILURE);
    }
    /*Tạo tuyến thứ hai*/
    res = pthread_create (&p_thread2, NULL, do_thread2, NULL);
    if (res != 0)
    {
        perror ("Thread create error");
        exit (EXIT_FAILURE);
    }
    /*Tuyến chính của chương trình*/
    while(1)
    {

        printf ("Main thread waiting %d second ... \n", i);
        // sleep (1);
    }
    
    return 0;
}
/*Cài đặt hàm thực thi tuyến thứ nhất*/
void* do_thread1 (void* data)
{
    int i;
    pthread_mutex_lock (&a_mutex); /*Khóa mutex*/
    for (i=1; i <= 5; i++)
    {
        printf ("Thread 1 count: %d with global value %d \n", i, global_var++);
        // sleep(1);
    }
    pthread_mutex_unlock (&a_mutex); /*Tháo khóa mutex*/
    printf ("Thread 1 completed !");
}
void* do_thread2 (void* data)
{
    int i;
    pthread_mutex_lock (&a_mutex); /*Khóa mutex*/
    for (i=1; i <= 5; i++)
    {
        printf ("Thread 2 count: %d with global value %d \n", i, global_var--);
        // sleep(2);
    }
    pthread_mutex_unlock (&a_mutex); /*Tháo khóa mutex*/
    printf ("Thread 2 completed !");
}