#include <stdio.h>
#include <ncurses.h>
#include <string.h>

int centerx, centery;
int height, width;
char *choices[] = {
  "Eleccion 1",
  "Eleccion 2",
  "Eleccion 3",
  "Eleccion 4",
  "Salir",
};
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
int MenuG(WINDOW *menu_win,WINDOW *frame_win);
int main()

{ 
  
  WINDOW *menu_win,*frame_win;
  //initiate ncurses
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);
  start_color();
  // Colores
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  bkgd(COLOR_PAIR(1));  
  //Centers the window
  centerx = COLS/2;
  centery= LINES/2;
  //window dimensions
  height = LINES/2;
  width = COLS/2;
  //creating windows

//             MENU
  menu_win = newwin(14,15,4,0); //parametros: alto, ancho, y, x
  wbkgd(menu_win, COLOR_PAIR(2));
  keypad(menu_win, TRUE);
  mvprintw(0, 0, "Utilice las flechas para ir arriba y abajo, Presione enter para elegir");
  refresh();
  //Frame 
  frame_win = newwin(LINES-4,COLS-16,4,16); //parametros: alto, ancho, y, x
  wbkgd(frame_win, COLOR_PAIR(2));
  wborder(frame_win, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(frame_win);
  refresh();
  //MENU
 int opcion= MenuG(menu_win,frame_win);
  clrtoeol();
  refresh();
  getch();
  endwin();
  return 0;
}
void print_menu(WINDOW *menu_win, int highlight)
{
  int x, y, i;
  x = 2;
  y = 3;
  wborder(menu_win, '|', '|', '-', '-', '+', '+', '+', '+');
  mvwprintw(menu_win, 1, 5, "MENU");
  mvwchgat(menu_win, 1, 5, 5, A_BOLD, 1, NULL);  //parametros: ventana, y, x, largo, atributos, color, NULL

  for(i = 0; i < n_choices; ++i)
    {   if(highlight == i + 1) /* Resalta lo opcion actual */
        { wattron(menu_win, A_REVERSE | A_BOLD );
          mvwprintw(menu_win, y, x, "%s", choices[i]);
          wattroff(menu_win, A_REVERSE | A_BOLD);
        }
      else
        mvwprintw(menu_win, y, x, "%s", choices[i]);
      y=y+2;
    }
  wrefresh(menu_win);
}
int MenuG(WINDOW *menu_win, WINDOW *frame_win) {
  int highlight = 1; /* Resalta la primera opcion por defecto */
  int choice = 0;
  int c;
  
  print_menu(menu_win, highlight);
  
  while (1) {
    c = wgetch(menu_win);
    
    switch (c) {
      case KEY_UP:
        if (highlight == 1)
          highlight = n_choices;
        else
          --highlight;
        break;
        
      case KEY_DOWN:
        if (highlight == n_choices)
          highlight = 1;
        else
          ++highlight;
        break;
        
      case 10:
        choice = highlight;
        break;
        
      default:
        mvprintw((LINES / 2) + 2, 0, "Caracter presionado = %3d Ojala se imprima como '%c'", c, c);
        refresh();
        break;
    }
    
    // Insertar info en el frame
    wclear(frame_win);
    mvwprintw(frame_win, 1, 1, "Opcion %d pelicula %s\n", highlight, choices[highlight - 1]);
    wborder(frame_win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(frame_win);
    
    if (choice != 0) /* El usuario eligio salir del bucle infinito */
      break;
    
    // Refresca el menu
    print_menu(menu_win, highlight);
  }
  
  attron(A_BOLD | A_REVERSE);
  mvprintw(2, 10, "Elegiste la opcion %d con la cadena %s\n", choice, choices[choice - 1]);
  attroff(A_BOLD | A_REVERSE);
  
  return choice;
}
