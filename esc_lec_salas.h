#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_ESC_LEC "info.bin"

struct Pelicula{
	char titulo[30];
	char director[30]; //20
	char horario[10];
	float precio;
};

struct Sala {
	struct Pelicula pelicula;
	int asientos[4][10]; //[horarios][asientos]
};

struct Sala rSalas[5];

void escritura();
void lectura();

int ejecutable(){
	lectura();
}

void escritura(){
	FILE *f;
	char filename[20] = "info.bin";

	// Escritura
	f = fopen(FILENAME_ESC_LEC, "wb");
	if(f != NULL){
		int result = fwrite(
			rSalas,
			sizeof(struct Sala),
			5,
			f
		);

		fclose(f);
		printf("Escritura de archivo info.bin\n");
	}
}

void lectura(){
	// lectura
	FILE *f;
	//struct Sala rSalas[10];

	f = fopen(FILENAME_ESC_LEC, "rb");
	if(f != NULL){
		int result = fread(
			rSalas,
			sizeof(struct Sala),
			5,
			f
		);
		fclose(f);
		printf("\nArchivo leido\n");
	}

	// resultados
	for(int i = 0; i<5; i++){
		printf("Sala %d\n", i+1);
		printf("Titulo: %s \n", rSalas[i].pelicula.titulo);
		printf("Director: %s \n", rSalas[i].pelicula.director);
		printf("Horario: %s hrs \n", rSalas[i].pelicula.horario);
		printf("Precio: %.2f$ \n", rSalas[i].pelicula.precio);
		printf("\n");
	}
}

void nueva_info(){

	struct Sala salas[5] = {
		{
			.pelicula = {
					.titulo = "Chunking Express",
					.director = "Wong Kar Wai",
					.horario = "10:00",
					.precio = 90.0f
			},
			.asientos = {
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
			}
		},
		{
			.pelicula = {
					.titulo = "The Lighthouse",
					.director = "Robert Eggers",
					.horario = "10:00",
					.precio = 90.0f
			},
			.asientos = {
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
			}
		},
		{
			.pelicula = {
					.titulo = "Lady Vengeance",
					.director = "Park Chan-wook",
					.horario = "10:00",
					.precio = 90.0f
			},
			.asientos = {
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
			}
		},
		{
			.pelicula = {
					.titulo = "Fallen Angels",
					.director = "Wong Kar Wai",
					.horario = "10:00",
					.precio = 90.0f
			},
			.asientos = {
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
			}
		},
		{
			.pelicula = {
					.titulo = "The Wind Rises",
					.director = "Hayau Miyazaki",
					.horario = "10:00",
					.precio = 90.0f
			},
			.asientos = {
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
				{
					1,1,1,1,1,
					1,1,1,1,1,
				},
			}
		},
	};

	FILE *f;
	char filename[20] = "info.bin";

	// Escritura
	f = fopen(FILENAME_ESC_LEC, "wb");
	if(f != NULL){
		int result = fwrite(
			salas,
			sizeof(struct Sala),
			5, // n elementos
			f
		);

		fclose(f);
		printf("Escritura de archivo info.bin\n");
	}

	//for(int i = 0; i<1; i++){
	//	printf("Sala %d\n", i+1);
	//	printf("Peliculas disponibles: \n\n");
	//	for(int j = 0; j<4; j++){
	//		printf("Titulo: %s \n", salas[i].peliculas[j].titulo);
	//		printf("Director: %s \n", salas[i].peliculas[j].director);
	//		printf("Horario: %s hrs \n", salas[i].peliculas[j].horario);
	//		printf("Precio: %.2f$ \n", salas[i].peliculas[j].precio);
	//		printf("\n");
	//	}
	//}
}
