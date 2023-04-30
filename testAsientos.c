#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void imprimir_menu() {
    clear();
    char *opciones[10] = {"Opción 1", "Opción 2", "Opción 3", "Opción 4", "Opción 5",
                          "Opción 6", "Opción 7", "Opción 8", "Opción 9", "Opción 10"};
    int x[10] = {1, 1, 1, 1, 1, 16, 16, 16, 16, 16};
    int y[10] = {1, 4, 7, 10, 13, 1, 4, 7, 10, 13};
    for (int i = 0; i < 10; i++) {
        mvprintw(y[i], x[i], "%d. %s", i+1, opciones[i]);
    }
    refresh();
}

void seleccionar_opcion(int opcion) {
    clear();
    mvprintw(0, 0, "Seleccionaste la opción %d. Presiona cualquier tecla para continuar.", opcion);
    refresh();
    getch();
}

int main() {
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    int opcion = 1;
    imprimir_menu();
    while (1) {
        int tecla = getch();
		clear();
        switch (tecla) {
            case KEY_UP:
                opcion--;
                if (opcion < 1) opcion = 10;
                break;
            case KEY_DOWN:
                opcion++;
                if (opcion > 10) opcion = 1;
                break;
            case KEY_LEFT:
                opcion -= 5;
                if (opcion < 1) opcion += 10;
                break;
            case KEY_RIGHT:
                opcion += 5;
                if (opcion > 10) opcion -= 10;
                break;
            case 10:
                seleccionar_opcion(opcion);
                imprimir_menu();
                break;
        }
        char *opciones[10] = {"Opción 1", "Opción 2", "Opción 3", "Opción 4", "Opción 5",
                              "Opción 6", "Opción 7", "Opción 8", "Opción 9", "Opción 10"};
        int x[10] = {1, 1, 1, 1, 1, 16, 16, 16, 16, 16};
        int y[10] = {1, 4, 7, 10, 13, 1, 4, 7, 10, 13};
        for (int i = 0; i < 10; i++) {
            if (opcion == i+1) {
                attron(A_REVERSE);
                mvprintw(y[i], x[i], "%d. %s", i+1, opciones[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(y[i], x[i], "%d. %s", i+1, opciones[i]);
            }
        }
        refresh();
    }
    endwin();
    return 0;
}
