#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 65);  // Same key as writer
    int shmid = shmget(key, 1024, 0666);  // Located the shared memory

    char *str = (char *) shmat(shmid, (void*)0, 0);   // Attach

    printf("Data read from shared memory: %s\n", str);

    shmdt(str);  // Detach
    shmctl(shmid, IPC_RMID, NULL); // Destroy shared memory
    return 0;
}

