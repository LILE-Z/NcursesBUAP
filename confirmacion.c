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
    WINDOW* confirmacionW = newwin(10, 30, 4, 2); //parameters: height, width, y, x
    wbkgd(confirmacionW,COLOR_PAIR(1));
    box(confirmacionW, 0, 0);
    keypad(confirmacionW, TRUE);
    refresh();
    wrefresh(confirmacionW);

    mvwprintw(confirmacionW, 1, 2, "¿Desea continuar?");
    mvwprintw(confirmacionW, 3, 2, "Sí");
    mvwprintw(confirmacionW, 3, 6, "No");

    while (1) {
        if (highlight == 1) {
            wattron(confirmacionW, A_REVERSE);
            mvwprintw(confirmacionW, 3, 2, "Sí");
            wattroff(confirmacionW, A_REVERSE);
        } else {
            mvwprintw(confirmacionW, 3, 2, "Sí");
        }

        if (highlight == 2) {
            wattron(confirmacionW, A_REVERSE);
            mvwprintw(confirmacionW, 3, 6, "No");
            wattroff(confirmacionW, A_REVERSE);
        } else {
            mvwprintw(confirmacionW, 3, 6, "No");
        }

        choice = wgetch(confirmacionW);

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
    wattron(confirmacionW, A_REVERSE);
    if (highlight == 1) {
        mvwprintw(confirmacionW,4, 1, " Seleccionaste: Sí");// parameters: window, y, x, string
    } else {
        mvwprintw(confirmacionW,4, 1, "Seleccionaste :No");
    }
    wattroff(confirmacionW, A_REVERSE);
    wrefresh(confirmacionW);
    refresh();
    getch();
    endwin();

    return 0;
}
