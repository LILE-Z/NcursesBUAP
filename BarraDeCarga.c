#include <ncurses.h>
#include <unistd.h>

void draw_progress_bar(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y);
void Barra(WINDOW* win,char* msg);
void progress_bar(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y);
int main()
{
    // Inicializar ncurses
    initscr();
    start_color();
    noecho();
    curs_set(FALSE);
    
 
    refresh();
    // Definir pares de colores
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_GREEN);
    WINDOW* wBarra = newwin(7, COLS-4, (LINES-7), 2);
    //Dibuja barra de carga
    Barra(wBarra,"BIENVENIDO");

    // Esperar la tecla "Enter" para salir
    mvprintw(LINES - 1, 0, "Presiona Enter para salir...");
    refresh();
    getch();

    // Limpiar y salir
    endwin();
    return 0;
}
void draw_progress_bar(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y)
{
    // Dibujar la barra de carga vacía
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, bar_y, bar_x, "[");
    for (int i = 1; i < bar_width - 1; ++i) {
        mvwprintw(win, bar_y, bar_x + i, " ");
    }
    mvwprintw(win, bar_y, bar_x + bar_width - 1, "]");
    wattroff(win, COLOR_PAIR(3));

    // Actualizar la barra de carga
    int bar_filled_width = (bar_width - 2) * progress / max_progress;
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, bar_y, bar_x + 1, "[");
    for (int i = 1; i < bar_filled_width + 1; ++i) {
        mvwprintw(win, bar_y, bar_x + i, "=");
    }
    for (int i = bar_filled_width + 1; i < bar_width - 1; ++i) {
        mvwprintw(win, bar_y, bar_x + i, " ");
    }
    wattroff(win, COLOR_PAIR(4));
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
        wclear(win);
        wrefresh(win);
    }
}
void Barra(WINDOW* win,char *msg){ 
// Actualizar el progreso de la barra
    mvwprintw(win,1,(COLS-strlen(msg))/2,msg);
    for (int i = 0; i <= 100; ++i) {
        update_progress(win, i, 100, (COLS-4)-15, 5, 2);
        usleep(100000);
    }

}