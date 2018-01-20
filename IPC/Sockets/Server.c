#include<stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *message = "Hello I am server sending message\n";
    
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        printf("setsocketopt \n");
        exit(EXIT_FAILURE);
    }
    // attaching port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
   
    // forcefully attaching socket to port 8080 
   if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("binding error\n");
        printf("cause = %s\n", strerror(errno));
        return -1;
    }

    if(listen(server_fd, 3) < 0) {
        perror("not listening");
    }

    if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024);
    printf("%s", buffer);
    send(new_socket, message, strlen(message), 0);
    printf("Message sent from Server\n");
    return 0;
}
