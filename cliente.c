#include <ncurses.h>
#include "recibir_archivo.h"
#include "esc_lec_salas.h"
#include <stdio.h>
#include <string.h>
void peliculas();
int main(){
	recibir_info();
	lectura();
	printf("Cliente\n");
	printf("lalalal %s",rSalas[1].pelicula.titulo);
	peliculas();
	sleep(10);
	initscr(); // Inicializar ncurses
    printw("Titulo: %s\n", rSalas[0].pelicula.titulo);
    refresh(); // Actualizar pantalla
    getch(); // Esperar una entrada del usuario
    endwin(); // Finalizar ncurses

	// modificando atributo
	
	//char name[20] = "Wong Kar Wai";
	//strcpy(rSalas[0].pelicula.director, name);

	//printf("%s\n", rSalas[0].pelicula.director);

	

	//escritura();

	//nueva_info();

	return 0;
}
// Pruebas con funciones
void peliculas(){
printf("Peliculas funcion\n");
for(int i = 0; i < 5; i++){
	printf("Pelicula %d\n", i);
	printf("Titulo: %s\n", rSalas[i].pelicula.titulo);
	printf("Director: %s\n", rSalas[i].pelicula.director);
	printf("Horario: %s\n", rSalas[i].pelicula.horario);
	printf("Precio: %f\n", rSalas[i].pelicula.precio);
}
}