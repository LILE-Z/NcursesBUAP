#include <ncurses.h>

int main() {
    // Inicializar ncurses
    initscr();

    // Desactivar eco del teclado y activar la captura de teclas especiales
    noecho();
    keypad(stdscr, TRUE);

    // Definir tres columnas de opciones
    const char* column1[] = {"Opción 1", "Opción 2", "Opción 3", "Opción 10"};
    const char* column2[] = {"Opción 4", "Opción 5", "Opción 6", ""};
    const char* column3[] = {"Opción 7", "Opción 8", "Opción 9", ""};

    // Definir variables para la posición del cursor
    int fila = 0;
    int columna = 0;
    int opcion = 0;
    // Bucle principal
    while (true) {
        // Borrar la pantalla y mostrar las tres columnas de opciones
        clear();

        for (int i = 0; i < 4; i++) {
            mvprintw(i, 0, column1[i]);
            mvprintw(i, 15, column2[i]);
            mvprintw(i, 30, column3[i]);
        }

        // Resaltar la opción seleccionada
        attron(A_REVERSE);
        mvprintw(fila, columna * 15, columna == 0 ? column1[fila] : columna == 1 ? column2[fila] : column3[fila]);
        attroff(A_REVERSE);

        // Esperar a que el usuario presione una tecla
        int tecla = getch();

        // Actualizar la posición del cursor según la tecla presionada
        switch (tecla) {
            case KEY_UP:
                fila = (fila - 1 + 4) % 4;
                break;
            case KEY_DOWN:
                fila = (fila + 1) % 4;
                break;
            case KEY_LEFT:
                columna = (columna - 1 + 3) % 3;
                break;
            case KEY_RIGHT:
                columna = (columna + 1) % 3;
                break;
            case 10:
                 opcion = fila;

                // Mostrar mensaje de selección
                clear();
                mvprintw(0, 0, "Seleccionaste la opción: %s", columna == 0 ? column1[opcion] : columna == 1 ? column2[opcion] : column3[opcion]);
                getch(); // Esperar a que el usuario presione cualquier tecla para continuar
                break;
          break;
            default:
                break;
        }
    }
   getch();
    // Finalizar ncurses
    endwin();

    return 0;
}

