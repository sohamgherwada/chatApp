#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(){
    int *ip = "127.0.0.1";
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
    printf("Connected");
    return 0;
}