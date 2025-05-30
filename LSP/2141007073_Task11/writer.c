#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);  // unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // shared memory

    char *str = (char *) shmat(shmid, (void*)0, 0); 

    strcpy(str, "Hello from shared memory....!");
    printf("Data written to shared memory Successfully : %s\n", str);

    shmdt(str); 
    return 0;
}

