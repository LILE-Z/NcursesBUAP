#include <ncurses.h>

int main() {
    int highlight = 1;
    int choice;

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    WINDOW* menu_win = newwin(10, 30, 4, 2); //parameters: height, width, y, x
    wbkgd(menu_win,COLOR_PAIR(1));
    box(menu_win, 0, 0);
    keypad(menu_win, TRUE);
    refresh();
    wrefresh(menu_win);

    mvwprintw(menu_win, 1, 2, "¿Desea continuar?");
    mvwprintw(menu_win, 3, 2, "Sí");
    mvwprintw(menu_win, 3, 6, "No");

    while (1) {
        if (highlight == 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 3, 2, "Sí");
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, 3, 2, "Sí");
        }

        if (highlight == 2) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 3, 6, "No");
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, 3, 6, "No");
        }

        choice = wgetch(menu_win);

        switch (choice) {
            case KEY_LEFT:
                highlight--;
                if (highlight == 0) {
                    highlight = 1;
                }
                break;
            case KEY_RIGHT:
                highlight++;
                if (highlight == 3) {
                    highlight = 2;
                }
                break;
            default:
                break;
        }

        if (choice == 10) {
            break;
        }
    }
    wattron(menu_win, A_REVERSE);
    if (highlight == 1) {
        mvwprintw(menu_win,4, 1, " Seleccionaste: Sí");// parameters: window, y, x, string
    } else {
        mvwprintw(menu_win,4, 1, "Seleccionaste :No");
    }
    wattroff(menu_win, A_REVERSE);
    wrefresh(menu_win);
    refresh();
    getch();
    endwin();

    return 0;
}
