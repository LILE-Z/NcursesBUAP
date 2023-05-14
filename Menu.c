#include <stdio.h>
#include <ncurses.h>
#include <string.h>

int centerx, centery;
int height, width;
char **choices=NULL;

//int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
int MenuG(WINDOW *menu_win,WINDOW *frame_win);
int main()

{ 
  initializeChoices();
  HorasC();
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
 getch();
  //end ncurses
clear();
  refresh();
 HorasC();
 opcion= MenuG(menu_win,frame_win);
  clrtoeol();
  refresh();
  getch();
  endwin();
  return 0;
}
int MenuG(WINDOW *menu_win, WINDOW *frame_win)
{
  int highlight = 1; /* Resalta la primera opcion por defecto */
  int choice = 0;
  int c;

  int n_choices = 0;
  for (int i = 0; i < 5; i++)
  {
    if (choices[i] && strlen(choices[i]) > 0)
      n_choices++;
  }

  print_menu(menu_win, highlight);

  while (1)
  {
    c = wgetch(menu_win);

    switch (c)
    {
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
    if (choices[highlight - 1] && strlen(choices[highlight - 1]) > 0)
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

  return choice-1;
}

void print_menu(WINDOW *menu_win, int highlight) {
  int x, y, i;
  x = 2;
  y = 3;
  int n_choices = 5; // Calcular el número de opciones de manera local

  wborder(menu_win, '|', '|', '-', '-', '+', '+', '+', '+');
  mvwprintw(menu_win, 1, 5, "MENU");
  mvwchgat(menu_win, 1, 5, 5, A_BOLD, 1, NULL);

  for (i = 0; i < n_choices; ++i) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE | A_BOLD);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE | A_BOLD);
    } else {
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    }
    y += 2;
  }
  wrefresh(menu_win);
}
void initializeChoices() {
  choices = (char **)malloc(5 * sizeof(char *));
  for (int i = 0; i < 5; i++) {
    choices[i] = NULL;  // Inicializar cada elemento con un puntero nulo
  }
}

void HorasC() {
  // Liberar la memoria de las elecciones anteriores
  for (int i = 0; i < 5; i++) {
    free(choices[i]);
  }

  // Modificar las elecciones
  choices[0] = strdup("Nueva eleccion 1");
  choices[1] = strdup("Nueva eleccion 2");
  choices[2] = strdup("Nueva eleccion 3");
  choices[3] = strdup("Nueva eleccion 4");
  choices[4] = strdup("hfhfhfk");
}


