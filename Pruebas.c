#include <ncurses.h>
#include <string.h>

int main() {
    char* title = "Título centrado";
    char* asciiArt[] = {
        "   /\\_/\\",
        "  ( o.o )",
        "   > ^ <"
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);

    // Inicializar ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Obtener tamaño de la ventana
    int windowHeight, windowWidth;
    getmaxyx(stdscr, windowHeight, windowWidth);

    // Calcular posiciones
    int titleLength = strlen(title);
    int titleX = (windowWidth - titleLength) / 2;
    int titleY = windowHeight / 2 - numLines / 2;

    int artX = (windowWidth - strlen(asciiArt[0])) / 2;

    // Crear ventana
    WINDOW* win = newwin(windowHeight, windowWidth, 0, 0);
    box(win, 0, 0);
    refresh();
    // Imprimir título
    mvwprintw(win, titleY, titleX, "%s", title);

    // Imprimir ASCII art
    for (int i = 0; i < numLines; i++) {
        mvwprintw(win, titleY + i + 2, artX, "%s", asciiArt[i]);
    }

    // Refrescar la ventana
    wrefresh(win);

    // Esperar la entrada del usuario
    getch();

    // Finalizar ncurses
    endwin();

    return 0;
}
