#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/shm.h>
int main() {
    int temp = fork();

    if(temp == 0) {
    //child
    
    key_t key = ftok("OS", 90);
    int shmid = shmget(key, 4096, 0666|IPC_CREAT);
    int n, p;
    int *s = (int *)shmat(shmid, (void *)0, 0);
    
    printf("Enter no upto which u wane get prime no from shared Memory : ");
    scanf("%d", &n);
    
    //finding prime numbers
    int prime[n + 1];
    memset(prime, -1, sizeof(prime));
    int notp = 0;
    for(p = 2; p*p< n;p++) {
        int i; 
        if(prime[p] == -1) {
            for(i = p * 2;i <= n;i+= p){
                if(prime[i] == -1){
                prime[i] = -2;
                notp++;}
                }
        }    
    }

    //printf("notp = %d\n", notp);
    int nt = n - notp + 1;
    printf("nt = %d\n", nt);
    int count = 0;
    for(p = 2;p <= nt;p++) {
        if(prime[p] == -1) {
            s[count] = p;count++;
        }
    }
    shmdt(s);

    }else{
    //parent
        wait();
        key_t key = ftok("OS", 90);
        int shmid = shmget(key, 4096, 0666|IPC_CREAT);
        int *s = (int *)shmat(shmid, (void*)0, 0); 
        printf("Data read from sm : \n");
        int i;
        for(i = 0;i < 5;i++)
            printf("%d ", s[i]);
        printf("\n");
        shmdt(s);
        shmctl(shmid, IPC_RMID, NULL);
    }
}
