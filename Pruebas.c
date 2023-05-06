#include <ncurses.h>

void mostrar_opciones(WINDOW* ventana, const char* opciones[], int filas, int columnas, int fila, int columna) {
    // Borrar la ventana y mostrar las opciones
    wclear(ventana);
    // Imprimir el título
    mvwprintw(ventana, 1, (getmaxx(ventana) - 6) / 2, "Horario");

    // Imprimir las opciones
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            mvwprintw(ventana, i + 2, j * 15 + 2, opciones[i * columnas + j]);
        }
    }

    // Resaltar la opción seleccionada
    wattron(ventana, A_REVERSE);
    mvwprintw(ventana, fila + 2, columna * 15 + 2, opciones[fila * columnas + columna]);
    wattroff(ventana, A_REVERSE);

    // Actualizar la ventana
    wrefresh(ventana);
}

void ejecutar_menu(WINDOW* ventana_opciones, const char* opciones[], int filas, int columnas) {
    // Definir variables para la posición del cursor
    int fila = 0;
    int columna = 0;

    // Mostrar las opciones por primera vez
    mostrar_opciones(ventana_opciones, opciones, filas, columnas, fila, columna);

    // Bucle principal
    while (true) {
        // Esperar a que el usuario presione una tecla
        int tecla = getch();

        // Actualizar la posición del cursor según la tecla presionada
        switch (tecla) {
            case KEY_UP:
                fila = (fila - 1 + filas) % filas;
                break;
            case KEY_DOWN:
                fila = (fila + 1) % filas;
                break;
            case KEY_LEFT:
                columna = (columna - 1 + columnas) % columnas;
                break;
            case KEY_RIGHT:
                columna = (columna + 1) % columnas;
                break;
            case 10:
                // Verificar si la opción seleccionada es válida
                if (fila * columnas + columna < filas * columnas - 2) {
                    // Mostrar mensaje de selección
                    clear();
                    mvprintw(0, 0, "Seleccionaste la opción: %s", opciones[fila * columnas + columna]);
                    getch(); // Esperar a que el usuario presione cualquier tecla para continuar
                    return; // Salir de la función
                }
                break;
            default:
                break;
        }

        // Mostrar las opciones actualizadas
        mostrar_opciones(ventana_opciones, opciones, filas, columnas, fila, columna);
    }
}


int main() {
    // Definir las opciones como un arreglo
    const char* opciones[] = {
        "Opción 1", "Opción 2", "Opción 3",
        "Opción 4", "Opción 5", "Opción 6",
        "Opción 7", "Opción 8", "Opción 9",
        "Opción 10","        ", "        "

    };

    // Inicializar ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Crear la ventana para mostrar las opciones
    WINDOW* ventana_opciones = newwin(7, 45, (LINES - 7) / 2, (COLS - 45) / 2);
    
    refresh(); // Actualizar la pantalla

    // Ejecutar el menú
    ejecutar_menu(ventana_opciones, opciones, 4, 3);

    // Finalizar ncurses
    endwin();

    return 0;
}

