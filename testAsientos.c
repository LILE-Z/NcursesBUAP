#include <ncurses.h>
#include <string.h>

void mostrar_opciones(WINDOW* ventana, int estados[], int filas, int columnas, int fila, int columna);
int menuAsientos(WINDOW* ventana_opciones, int estados[], int filas, int columnas);

int main() {
    int estados[10] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 0}; // 1: Disponible, 0: No disponible

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    WINDOW* wAsientos = newwin(7, 45, (LINES - 7) / 2, (COLS - 45) / 2);

    refresh();

    int opcionSeleccionada = menuAsientos(wAsientos, estados, 4, 3);

    if (opcionSeleccionada != -1) {
        printw("La opción seleccionada es: %d", opcionSeleccionada + 1);
    } else {
        printw("No se seleccionó ninguna opción disponible.");
    }

    refresh();
    getch();
    endwin();

    return 0;
}

void mostrar_opciones(WINDOW* ventana, int estados[], int filas, int columnas, int fila, int columna) {
    wclear(ventana);
    mvwprintw(ventana, 1, (getmaxx(ventana) - 7) / 2, "Horario");

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int index = i * columnas + j;
            if (estados[index] == 1) {
                mvwprintw(ventana, i + 2, j * 15 + 2, "Disponible");
            } else {
                mvwprintw(ventana, i + 2, j * 15 + 2, "No disponible");
            }
        }
    }

    int index = fila * columnas + columna;
    if (estados[index] == 1) {
        wattron(ventana, A_REVERSE);
        mvwprintw(ventana, fila + 2, columna * 15 + 2, "Disponible");
        wattroff(ventana, A_REVERSE);
    }

    wrefresh(ventana);
}
int menuAsientos(WINDOW* ventana_opciones, int estados[], int filas, int columnas) {
    bool menu_vacio = true;
    for (int i = 0; i < filas * columnas; i++) {
        if (estados[i] == 1) {
            menu_vacio = false;
            break;
        }
    }

    if (menu_vacio) {
        return -1;
    }

    int fila = 0;
    int columna = 0;

    // Buscar la primera opción disponible
    for (int i = 0; i < filas * columnas; i++) {
        if (estados[i] == 1) {
            fila = i / columnas;
            columna = i % columnas;
            break;
        }
    }

    mostrar_opciones(ventana_opciones, estados, filas, columnas, fila, columna);

    while (true) {
        int tecla = getch();

        switch (tecla) {
            case KEY_UP:
                do {
                    fila = (fila - 1 + filas) % filas;
                    columna = (columna + columnas) % columnas;
                } while (estados[fila * columnas + columna] != 1);
                break;
            case KEY_DOWN:
                do {
                    fila = (fila + 1) % filas;
                    columna = (columna + columnas) % columnas;
                } while (estados[fila * columnas + columna] != 1);
                break;
            case KEY_LEFT:
                do {
                    columna = (columna - 1 + columnas) % columnas;
                } while (estados[fila * columnas + columna] != 1);
                break;
            case KEY_RIGHT:
                do {
                    columna = (columna + 1) % columnas;
                } while (estados[fila * columnas + columna] != 1);
                break;
            case 10:
                if (fila * columnas + columna < filas * columnas && estados[fila * columnas + columna] == 1) {
                    return fila * columnas + columna;
                }
                break;
            default:
                break;
        }

        mostrar_opciones(ventana_opciones, estados, filas, columnas, fila, columna);
    }
}

