#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    int sockfd, n, len;
    char recvline[1024];
    struct sockaddr_in servaddr;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(atoi(argv[1]));
    len = sizeof(servaddr);

    printf("Give a number for server: ");
    scanf("%d", &n);
    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&servaddr, len);

    int bytes = recvfrom(sockfd, recvline, sizeof(recvline) - 1, 0, (struct sockaddr *)&servaddr, &len);
    if (bytes < 0) {
        perror("recvfrom failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    recvline[bytes] = '\0';
    printf("\nServer sent: %s\n", recvline);

    close(sockfd);
    return 0;
}
