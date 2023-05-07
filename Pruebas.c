#include <ncurses.h>
#include <string.h>

void printPelicula(WINDOW* win, const char* title, const char* asciiArt[]) {
    int titleLength = strlen(title);
    int titleX = (COLS - titleLength) / 2;

    box(win, 0, 0);

    mvwprintw(win,2 , titleX, "%s", title); //parametros window, y, x, string

    for (int i = 0; asciiArt[i] != NULL; i++) {
        int artX = (COLS - strlen(asciiArt[i])) / 2;
        mvwprintw(win, 2 + i + 2, artX, "%s", asciiArt[i]);
    }

    wrefresh(win);
    getch();
}

int main() {
    // Inicializar ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Crear ventana
    WINDOW* win = newwin(0, 0, 0, 0);
    refresh();
    // Definir contenido de la ventana
    char* title = "Título centrado";
    char* asciiArt[] = {
        "   /\\_/\\",
        "  ( o.o )",
        "   > ^ <",
        NULL
    };

    // Mostrar ventana
    printPelicula(win, title, asciiArt);

    // Finalizar ncurses
    endwin();

    return 0;
}
