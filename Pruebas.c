#include <ncurses.h>

void mostrar_opciones(WINDOW* ventana, const char* opciones[], int filas, int columnas, int fila, int columna) {
    // Borrar la ventana y mostrar las opciones
    wclear(ventana);
    // Imprimir el título
    mvwprintw(ventana, 1, (getmaxx(ventana) - 7) / 2, "Horario");

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

int ejecutar_menu(WINDOW* ventana_opciones, const char* opciones[], int filas, int columnas) {
    int fila = 0;
    int columna = 0;

    mostrar_opciones(ventana_opciones, opciones, filas, columnas, fila, columna);

    while (true) {
        int tecla = getch();

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
                if (fila * columnas + columna < filas * columnas - 2 && strlen(opciones[fila * columnas + columna]) > 0) {
                    return fila * columnas + columna;
                }
                break;
            default:
                break;
        }

        mostrar_opciones(ventana_opciones, opciones, filas, columnas, fila, columna);
    }
}


int main() {
    // LAS OPCIONES QUE ESTEN VACIAS NO SE PODRAN SELECCIONAR
    const char* opciones[] = {
        "Opción 1", "Opción 2", "Opción 3",
        "Opción 4", "Opción 5", "Opción 6",
        "Opción 7", "Opción 8", "Opción 9",
        "Opción 10","", ""

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
 int opcionSeleccionada=  ejecutar_menu(ventana_opciones, opciones, 4, 3);
    printw("La opcion seleccionada es: %d y la opcion %s", opcionSeleccionada, opciones[opcionSeleccionada]);
    refresh();
    getch();
    // Finalizar ncurses
    endwin();

    return 0;
}

