#include <ncurses.h>
int confirmation_box(WINDOW* win) {
    int highlight = 1;
    int choice;

    mvwprintw(win, 1, 2, "¿Desea continuar?");
    mvwprintw(win, 3, 2, "Sí");
    mvwprintw(win, 3, 6, "No");

    while (1) {
        if (highlight == 1) {
            wattron(win, A_REVERSE);
            mvwprintw(win, 3, 2, "Sí");
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, 3, 2, "Sí");
        }

        if (highlight == 2) {
            wattron(win, A_REVERSE);
            mvwprintw(win, 3, 6, "No");
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, 3, 6, "No");
        }

        choice = wgetch(win);

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

    if (highlight == 1) {
        return 1;
    } else {
        return 0;
    }
}
int main() {
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    WINDOW* confirmationW = newwin(10, 30, 4, 2); //parameters: height, width, y, x
    wbkgd(confirmationW,COLOR_PAIR(1));
    box(confirmationW, 0, 0);
    keypad(confirmationW, TRUE);
    refresh();
    wrefresh(confirmationW);

    int choice = confirmation_box(confirmationW);

    if (choice == 1) {
        mvwprintw(confirmationW, 2, 1, "Sí");
    } else {
        mvwprintw(confirmationW, 2, 1, "No");
    }
    wrefresh(confirmationW);
    refresh();
    getch();
    endwin();

    return 0;
}
