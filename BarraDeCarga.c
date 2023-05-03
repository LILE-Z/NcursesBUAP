#include <ncurses.h>
#include <unistd.h>

void draw_progress_bar(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y)
{
    // Dibujar la barra de carga vacía
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, bar_y, bar_x, "[");
    for (int i = 1; i < bar_width - 1; ++i) {
        mvwprintw(win, bar_y, bar_x + i, " ");
    }
    mvwprintw(win, bar_y, bar_x + bar_width - 1, "]");
    wattroff(win, COLOR_PAIR(1));

    // Actualizar la barra de carga
    int bar_filled_width = (bar_width - 2) * progress / max_progress;
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, bar_y, bar_x + 1, "[");
    for (int i = 1; i < bar_filled_width + 1; ++i) {
        mvwprintw(win, bar_y, bar_x + i, "=");
    }
    for (int i = bar_filled_width + 1; i < bar_width - 1; ++i) {
        mvwprintw(win, bar_y, bar_x + i, " ");
    }
    wattroff(win, COLOR_PAIR(2));
    mvwprintw(win, bar_y + 1, bar_x+bar_width/2, " %d%%", progress);
    mvwprintw(win, bar_y + 1, bar_x + bar_width - 5, " ");
    

    // Refrescar la ventana
    wrefresh(win);
}

void update_progress(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y)
{
    // Actualizar el progreso
    if (progress > max_progress) {
        progress = max_progress;
    }

    // Dibujar la barra de carga
    draw_progress_bar(win, progress, max_progress, bar_width, bar_x, bar_y);

    // Si el progreso ha alcanzado el máximo, eliminar la ventana
    if (progress >= max_progress) {
        delwin(win);
    }
}

int main()
{
    // Inicializar ncurses
    initscr();
    start_color();
    noecho();
    curs_set(FALSE);

    // Definir pares de colores
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_YELLOW, COLOR_GREEN);

    // Crear la ventana
    int win_height = 7;
    int win_width = COLS - 4;
    int win_x = 2;
    int win_y = (LINES - win_height) / 2;
    WINDOW* win = newwin(win_height, win_width, win_y, win_x);

    // Configurar la barra de carga
    int progress = 0;
    int max_progress = 100;
    int bar_width = win_width - 15;
    int bar_x = 5;
    int bar_y = 2;

    // Actualizar el progreso de la barra
    for (int i = 0; i <= max_progress; ++i) {
        update_progress(win, i, max_progress, bar_width, bar_x, bar_y);
        usleep(100000);
    }

    // Esperar la tecla "Enter" para salir
    mvprintw(LINES - 1, 0, "Presiona Enter para salir...");
    refresh();
    getch();

    // Limpiar y salir
    endwin();
    return 0;
}
