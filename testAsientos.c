#include <ncurses.h>
#include <string.h>
void mostrar_opciones(WINDOW* ventana, const char* opciones[4][3], int fila, int columna) {
    // Borrar la ventana y mostrar las tres columnas de opciones
    wclear(ventana);
        // Imprimir el título
    mvwprintw(ventana, 1, (getmaxx(ventana) - 6) / 2, "Horario");
    wborder(ventana,'|','|','-','-','+','+','+','+');
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            mvwprintw(ventana, i + 2, j * 15 + 2, opciones[i][j]);
        }
    }

    // Resaltar la opción seleccionada
    wattron(ventana, A_REVERSE);
    mvwprintw(ventana, fila + 2, columna * 15 + 2, opciones[fila][columna]);
    wattroff(ventana, A_REVERSE);
    // Actualizar la ventana
    wrefresh(ventana);
}


void ejecutar_menu(WINDOW* ventana_opciones, const char* opciones[4][3]) {
    // Definir variables para la posición del cursor
    int fila = 0;
    int columna = 0;

    // Mostrar las opciones por primera vez
    mostrar_opciones(ventana_opciones, opciones, fila, columna);

    // Bucle principal
    while (true) {
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
                // Mostrar mensaje de selección
                clear();
                mvprintw(0, 0, "Seleccionaste la opción: %s", opciones[fila][columna]);
                getch(); // Esperar a que el usuario presione cualquier tecla para continuar
                return; // Salir de la función
            default:
                break;
        }

        // Mostrar las opciones actualizadas
        mostrar_opciones(ventana_opciones, opciones, fila, columna);
    }
}

int main() {
    // Definir las opciones como una matriz
    const char* opciones[4][3] = {
        {"Opción 1", "Opción 2", "Opción 3"},
        {"Opción 4", "Opción 5", "Opción 6"},
        {"Opción 7", "Opción 8", "Opción 9"},
        {"Opción 10", "", ""}
    };

    // Inicializar ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    WINDOW* ventana_opciones = newwin(7, 45,  (LINES - 7) / 2,  (COLS - 45) / 2);
    wrefresh(ventana_opciones); // Actualizar la ventana
    refresh(); // Actualizar la pantalla

    // Ejecutar el menú
    ejecutar_menu(ventana_opciones, opciones);

    // Finalizar ncurses
    endwin();

    return 0;
}
