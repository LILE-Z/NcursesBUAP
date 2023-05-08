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
char* asciiArt[] = {
        "   /\\_/\\",
        "  ( o.o )",
        "   > ^ <",
        NULL
};
//menu
//int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight, int n_choices);
int MenuG(WINDOW *menu_win,WINDOW *frame_win);
void printPelicula(WINDOW* win, const char* title, const char* asciiArt[]);

//Barra
void draw_progress_bar(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y);
void Barra(WINDOW* win,char* msg);
void update_progress(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y);

//Horarios
void mostrar_opciones(WINDOW* ventana, const char* opciones[], int filas, int columnas, int fila, int columna);
int ejecutar_menu(WINDOW* ventana_opciones, const char* opciones[], int filas, int columnas);

//Confirmacion



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
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_YELLOW, COLOR_GREEN);
    //Dibuja barra de carga
  bkgd(COLOR_PAIR(1));  
  WINDOW* wBarra = newwin(7, COLS-4, (LINES-7), 2);
  Barra(wBarra,"BIENVENIDO");

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
  MenuG(menu_win,frame_win);
  clrtoeol();
  refresh();
  getch();
  endwin();
  return 0;
}

///FUNCIONES
//**********************************************************************************************************************
void print_menu(WINDOW *menu_win, int highlight, int n_choices)
{ int x, y, i;
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
int MenuG( WINDOW *menu_win,WINDOW *frame_win){
    int n_choices = sizeof(choices) / sizeof(char *);
   int highlight = 1; /* Resalta la primera opcion por defecto */
  int choice = 0;
  int c;
     print_menu(menu_win, highlight,n_choices);
  while(1)
    { c = wgetch(menu_win);
      switch(c) {
        case KEY_UP:
          if(highlight == 1)
            highlight = n_choices;
          else
            --highlight;
          break;
        case KEY_DOWN:
          if(highlight == n_choices)
            highlight = 1;
          else
            ++highlight;
          break;
        case 10:
          choice = highlight;
          break;
        default:
          mvprintw((LINES/2)+2, 0, "Caracter presionado = %3d Ojala se imprima como '%c'", c, c);
          refresh();
          break;
        }
          // Incertar info en el frame
        wclear(frame_win);
        //mvwprintw(frame_win, 1, 1, "Opcion %d pelicula %s\n", highlight, choices[highlight - 1]);
        printPelicula(frame_win, choices[highlight - 1], asciiArt);

        if(choice != 0) /* El usuario eligio salir del bucle infinito */
            break;

        // Refresca el menu
        print_menu(menu_win, highlight,n_choices);
    }
  attron(A_BOLD|A_REVERSE);
  mvprintw(2, 10, "Elegiste la opcion %d con la cadena %s\n", choice, choices[choice - 1]);
  attroff(A_BOLD|A_REVERSE);
  return choice;
}

void printPelicula(WINDOW* win, const char* title, const char* asciiArt[]) {
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    int titleLength = strlen(title);
    int titleX = (COLS - titleLength) / 2;

    box(win, 0, 0);

    mvwprintw(win, 1, titleX, "%s", title); // Mostrar título en la línea 1

    int artStartY = 3; // Inicio de las líneas de arte ASCII

    for (int i = 0; asciiArt[i] != NULL; i++) {
        int artX = (COLS - strlen(asciiArt[i])) / 2;
        mvwprintw(win, artStartY + i, artX, "%s", asciiArt[i]);
    }

    wrefresh(win);
}

//Barra
//**********************************************************************************************************************
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
//Horario
//**********************************************************************************************************************



//Asientos
//**********************************************************************************************************************