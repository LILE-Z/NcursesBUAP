#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 8080
#define FILENAME_TRANSFER "info_recibido.bin"

int recibir_info() {
    int sockfd, valread;
    struct sockaddr_in serv_addr;

    // Crear socket del cliente
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error en la creación del socket");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección del servidor
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Error en la asignación de dirección del servidor");
        exit(EXIT_FAILURE);
    }

    // Conectar al servidor
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error al conectar al servidor");
        exit(EXIT_FAILURE);
    }

    printf("Conexión establecida con el servidor. Recibiendo archivo...\n");

    // Abrir archivo para escritura
    int fd = open(FILENAME_TRANSFER, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    char buffer[4096] = {0};
    int bytes_received;
    while ((bytes_received = read(sockfd, buffer, sizeof(buffer))) > 0) {
        write(fd, buffer, bytes_received);
    }

    close(fd);
    close(sockfd);

    printf("Archivo recibido correctamente.\n");

    //return 0;
}
