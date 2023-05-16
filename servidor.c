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
#define FILENAME "info.bin"

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Crear socket del servidor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error en la creación del socket");
        exit(EXIT_FAILURE);
    }

    // Asignar opciones al socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Error en la asignación de opciones del socket");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Asignar dirección al socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("Error en la asignación de dirección del socket");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        perror("Error al intentar escuchar conexiones entrantes");
        exit(EXIT_FAILURE);
    }

    printf("Servidor iniciado. Esperando conexiones entrantes...\n");

    while (1) {
        // Aceptar nueva conexión
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("Error al aceptar conexión entrante");
            exit(EXIT_FAILURE);
        }

        printf("Cliente conectado. Enviando archivo...\n");

        // Abrir archivo y enviarlo al cliente
        int fd = open(FILENAME, O_RDONLY);
        char buffer[4096] = {0};
        int bytes_read;
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            write(new_socket, buffer, bytes_read);
        }

        close(fd);
        close(new_socket);

        printf("Archivo enviado. Esperando nuevas conexiones...\n");
    }

    return 0;
}
