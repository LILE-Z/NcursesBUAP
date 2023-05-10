#include <ncurses.h>

void print_array(WINDOW *window, char *array[], int size) {
  int i;
  int sectionHeight = (getmaxy(window) - 2) / size;
  
  for (i = 0; i < size; i++) {
    // Imprimir línea horizontal
    if (i != 0) {
      mvwhline(window, i * sectionHeight, 1, ACS_HLINE, getmaxx(window) - 2);
    }
    
    // Imprimir elemento del arreglo
    mvwprintw(window, i * sectionHeight + 1, 2, "Elemento %d: %s", i + 1, array[i]);
  }
}

int main() {
  WINDOW *window;
  char *reciboM[] = {
    "Texto 1",
    "Texto 2",
    "Texto 3",
    "Texto 4",
    "Texto 5"
  };
  
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  
  // Crear ventana
  window = newwin(LINES - 4, COLS - 4, 2, 2);
  box(window, 0, 0);
  refresh(); 
  // Imprimir el arreglo y las líneas horizontales en la ventana
  print_array(window, reciboM, sizeof(reciboM) / sizeof(char *));
  
  wrefresh(window);
  
  getch();
  
  endwin();
  return 0;
}

