#include <ncurses.h>
  char *reciboM[] = {
    "Recibo de pago",
    "",
    "",
    "",
    "",
    "",
    "Total a pagar: $ 100.00"
  };
void printRecibo(WINDOW *window);
int main() {
  WINDOW *recibow;
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  
  // Crear ventana
  recibow = newwin(LINES - 4, COLS - 4, 2, 2);
  box(recibow, 0, 0);
  refresh(); 
  // Imprimir el arreglo y las líneas horizontales en la ventana
  printRecibo(recibow);
  
  wrefresh(recibow);
  
  getch();
  
  endwin();
  return 0;
}

void printRecibo(WINDOW *window) {
    int i;
    int size = sizeof(reciboM) / sizeof(reciboM[0]);
    int sectionHeight = (getmaxy(window) - 2) / size;

    for (i = 0; i < size; i++) {
        // Imprimir línea horizontal
        if (i != 0) {
            mvwhline(window, i * sectionHeight, 1, ACS_HLINE, getmaxx(window) - 2);
        }

        // Imprimir elemento del arreglo
        if (i == 0 || i == size - 1) {
            wattron(window, A_BOLD| A_REVERSE);
        }

        mvwprintw(window, i * sectionHeight + 1, 2, "%s", reciboM[i]);

        if (i == 0 || i == size - 1) {
            wattroff(window, A_BOLD| A_REVERSE);
        }
    }
}
