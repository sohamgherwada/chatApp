#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(){
    char *ip = "127.0.0.1";
    int port = 3000;
    int socke;

    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;


    socke = socket(AF_INET, SOCK_STREAM, 0);
    if(socke < 0){
        perror("[-]Socket Error");
        exit(1);
    }
    printf("[+]Socket Created\n");
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);
    connect(socke, (struct sockaddr*)&addr, sizeof(addr));
    printf("Connected\n");
    char message[1024];
    while(1) {
        printf("Enter your message: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove trailing newline character
        
        // Send message to server
        send(socke, message, strlen(message), 0);
        
        // Receive response from server
        bzero(buffer, 1024);
        recv(socke, buffer, sizeof(buffer), 0);
        printf("Server: %s\n", buffer);
        
        // Check if conversation should end
        if (strcmp(message, "exit") == 0) {
            break;
        }
    }
    printf("[+]Disconnected from the server\n\n");
    return 0;
}