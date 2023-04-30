#include <ncurses.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // Inicializar ncurses
    initscr();
    noecho();
    curs_set(FALSE);

    // Configurar la barra de carga
    int progress = 0;
    int max_progress = 100;
    int bar_width = COLS - 10;
    int bar_x = (COLS - bar_width) / 2;
    int bar_y = LINES / 2;

    // Dibujar la barra de carga vacía
    mvprintw(bar_y, bar_x, "[");
    for (int i = 1; i < bar_width - 1; ++i) {
        mvprintw(bar_y, bar_x + i, " ");
    }
    mvprintw(bar_y, bar_x + bar_width - 1, "]");

    // Actualizar la barra de carga
    while (progress < max_progress) {
        // Calcular el progreso actual
        progress = (progress + 1) % (max_progress + 1);

        // Actualizar la barra de carga
        int bar_filled_width = (bar_width - 2) * progress / max_progress;
        mvprintw(bar_y, bar_x + 1, "|");
        for (int i = 1; i < bar_filled_width + 1; ++i) {
            mvprintw(bar_y, bar_x + i, "#");
        }
        for (int i = bar_filled_width + 1; i < bar_width - 1; ++i) {
            mvprintw(bar_y, bar_x + i, " ");
        }
        mvprintw(bar_y, bar_x + bar_width - 1, "|");

        // Refrescar la pantalla
        refresh();

        // Esperar un poco
        usleep(10000); // 10 ms
    }

    // Esperar a que el usuario presione cualquier tecla para salir
    mvprintw(LINES - 1, 0, "Presiona cualquier tecla para salir...");
    getch();

    // Finalizar ncurses
    endwin();
    return 0;
}
