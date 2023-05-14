#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "recibir_archivo.h"
#include "esc_lec_salas.h"
int centerx, centery;
int height, width;
char **choices=NULL;
char* asciiArt[] = {
        "   /\\_/\\",
        "  ( o.o )",
        "   > ^ <",
        NULL
};
  int estados[10] ;// 1: Disponible, 0: No disponible
  char *reciboM[] = {
    "Recibo de pago",
    "",
    "",
    "",
    "",
    "",
    "Total a pagar: $ 100.00"
  };
//menu
//int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
int MenuG(WINDOW *menu_win,WINDOW *frame_win);
void printPelicula(WINDOW* win,  char* title,  char* asciiArt[]);

//Barra
void draw_progress_bar(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y);
void Barra(WINDOW* win,char* msg);
void update_progress(WINDOW* win, int progress, int max_progress, int bar_width, int bar_x, int bar_y);

//Horarios
void mostrar_opciones(WINDOW* ventana, int estados[], int filas, int columnas, int fila, int columna);
int menuAsientos(WINDOW* ventana_opciones, int estados[], int filas, int columnas);
void HorasC();
//Confirmacion
int confirmation_box(WINDOW* win,char* msg);
//recibo
void printRecibo(WINDOW *window);
int main()

{ 
  int confirmacionA=0,confirmacionP=0,contadorG=0,contadorL=0,contadorRecibo=0,asientoC=0,horario=0,sala=0;
  int opcionSeleccionada=0;
  char pelicula[50]="";
  WINDOW *menu_win,*frame_win;
  initializeChoices();
  recibir_info();
  lectura();
  //initiate ncurses
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);
  start_color();
  keypad(stdscr, TRUE);
  // Colores
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_YELLOW, COLOR_GREEN);
    //Dibuja barra de carga
  bkgd(COLOR_PAIR(1));  
  WINDOW* wBarra = newwin(7, COLS-4, (LINES-7), 2);
  Barra(wBarra,"BIENVENIDO");
  WINDOW* wAsientos = newwin(7, 45, (LINES - 7) / 2, (COLS - 45) / 2);
  wbkgd(wAsientos, COLOR_PAIR(2));
  WINDOW* confirmationW = newwin(10, 30, (LINES-10)/2, (COLS-30)/2); //parameters: height, width, y, x
  wbkgd(confirmationW,COLOR_PAIR(3));
  box(confirmationW, 0, 0);
  keypad(confirmationW, TRUE);
  WINDOW* recibow = newwin(LINES - 4, COLS - 4, 2, 2);
  box(recibow, 0, 0);

  
  //keypad(confirmationW, TRUE);
//             MENU
  menu_win = newwin(14,19,4,0); //parametros: alto, ancho, y, x
  wbkgd(menu_win, COLOR_PAIR(2));
  keypad(menu_win, TRUE);
  refresh();
  //Frame 
  frame_win = newwin(LINES-4,COLS-19,4,18); //parametros: alto, ancho, y, x
  wbkgd(frame_win, COLOR_PAIR(2));
  //wborder(frame_win, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(frame_win);
  refresh();
  

 //Gestiona menu de peliculas
  while (1)
  { 
    clear();
    wclear(menu_win);
  printw( "Utilice las flechas para ir arriba y abajo, Presione enter para elegir"); //paraetros y,x, texto
    refresh();
  //MENU Peliculas
  //Cargar choices con las peliclas de la base de datos
  peliculasC();
  contadorRecibo++;
  pelicula[0]=0;
  sala=MenuG(menu_win,frame_win);
  strcpy( pelicula,choices[sala]);
  printw("La opcion seleccionada es: %s", pelicula);
  werase(menu_win);
   //cambiar choices por los horarios
  HorasC();
  //MENU Horarios 
  horario=MenuG(menu_win,frame_win);
// second loop  
 contadorL=0; //selecciono un asiento en un misma pelicula
 while (1)
  { wclear(confirmationW);
    wclear(wAsientos);
  asientosC(sala,horario);
  //Asientos
  contadorL++;
  wmove(wAsientos, 0, 0);
   opcionSeleccionada=  menuAsientos(wAsientos, estados, 4, 3);
   if (opcionSeleccionada == -1) {
      contadorL--;
      break;
    }
 // Registra el asiento seleccionado
   rSalas[sala].asientos[horario][opcionSeleccionada]=0;
   printw("La opcion seleccionada es: %d y la opcion %d", opcionSeleccionada, estados[opcionSeleccionada]);
   escritura();
  //Confirmacion de si desea agregar mas asientos
  confirmacionA = confirmation_box(confirmationW,"Desea agregar mas asientos?");  
    if(confirmacionA==0) {
      break;
    }
 
  }
  // Aqui se pasan a recibo los datos de la pelicula y los asientos
  reciboM[contadorRecibo] = malloc(strlen(pelicula) + 41);
  sprintf(reciboM[contadorRecibo], "%s ------ boletos :%d", pelicula, contadorL);
  //reciboM[contadorRecibo] = malloc(strlen(pelicula) + 1); // Asignar memoria para la cadena
  //strcpy(reciboM[contadorRecibo], pelicula);
  contadorG+=contadorL;
 wclear(confirmationW);
 // printw("La opcion seleccionada es: %d y la opcion %s", opcionSeleccionada, Asientos[opcionSeleccionada]);
  //Confirmacion de si desea agregar mas asientos
  //Confirmacion de si desea otra pelicula
  confirmacionP = confirmation_box(confirmationW,"Desea regresar al menu?");  
    if(confirmacionP==0) {
      break;
    }
  }
  clear();
  refresh();
 //  printw("%d",contadorG);
  //printw("PELICULA: %s",pelicula);
  reciboM[6] = malloc(strlen(pelicula) + 41);
  sprintf(reciboM[6], "Total a pagar por %d boletos:%d$", contadorG,contadorG*50);
  printRecibo(recibow);
  wrefresh(recibow);
  clrtoeol();
  refresh();
  getch();
  endwin();
  return 0;
}

///FUNCIONES
//**********************************************************************************************************************
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
     printPelicula(frame_win, ("Opcion %d pelicula %s\n", highlight, choices[highlight - 1]),asciiArt);
    //  mvwprintw(frame_win, 1, 1, "Opcion %d pelicula %s\n", highlight, choices[highlight - 1]); 
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
  choices[0] = strdup("11:00");
  choices[1] = strdup("13:00");
  choices[2] = strdup("03:00");
  choices[3] = strdup("06:00");
  choices[4] = strdup("");
}
void peliculasC() {
  // Liberar la memoria de las elecciones anteriores
  for (int i = 0; i < 5; i++) {
    free(choices[i]);
  }
for (int i = 0; i < 5; i++) {
    choices[i] =  strdup(rSalas[i].pelicula.titulo);
  }
}
void asientosC(int sala,int horario ){
  //sala pelicual , horario el arreglo de asientos
  for (int i = 0; i < 9; i++) {
    estados[i] = rSalas[sala].asientos[horario][i];
  } 
  estados[9] = 1;
}



//Pelicula 
void printPelicula(WINDOW* win, char* title,  char* asciiArt[]) {
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
        usleep(10000);
    }

}
//Horario
//**********************************************************************************************************************



//Asientos
//**********************************************************************************************************************

void mostrar_opciones(WINDOW* ventana, int estados[], int filas, int columnas, int fila, int columna) {
    wclear(ventana);
    mvwprintw(ventana, 1, (getmaxx(ventana) - 7) / 2, "Asientos");

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int index = i * columnas + j;
            if (estados[index] == 1) {
                mvwprintw(ventana, i + 2, j * 15 + 2, "Disponible");
            } else {
                mvwprintw(ventana, i + 2, j * 15 + 2, "No disponible");
            }
        }
    }

    int index = fila * columnas + columna;
    if (estados[index] == 1) {
        wattron(ventana, A_REVERSE);
        mvwprintw(ventana, fila + 2, columna * 15 + 2, "Disponible");
        wattroff(ventana, A_REVERSE);
    }

    wrefresh(ventana);
}
int menuAsientos(WINDOW* ventana_opciones, int estados[], int filas, int columnas) {
    bool menu_vacio = true;
    for (int i = 0; i < filas * columnas; i++) {
        if (estados[i] == 1) {
            menu_vacio = false;
            break;
        }
    }

    if (menu_vacio) {
        return -1;
    }

    int fila = 0;
    int columna = 0;

    mostrar_opciones(ventana_opciones, estados, filas, columnas, fila, columna);

    while (true) {
        int tecla = getch();

        switch (tecla) {
            case KEY_UP:
                do {
                    fila = (fila - 1 + filas) % filas;
                } while (!filaTieneElementosDisponibles(estados, filas, columnas, fila));
                columna = encontrarPrimerElementoDisponibleEnFila(estados, filas, columnas, fila);
                break;
            case KEY_DOWN:
                do {
                    fila = (fila + 1) % filas;
                } while (!filaTieneElementosDisponibles(estados, filas, columnas, fila));
                columna = encontrarPrimerElementoDisponibleEnFila(estados, filas, columnas, fila);
                break;
            case KEY_LEFT:
                columna = (columna - 1 + columnas) % columnas;
                break;
            case KEY_RIGHT:
                columna = (columna + 1) % columnas;
                break;
            case 10:
                if (fila * columnas + columna < filas * columnas && estados[fila * columnas + columna] == 1) {
                    return fila * columnas + columna;
                }
                break;
            default:
                break;
        }

        mostrar_opciones(ventana_opciones, estados, filas, columnas, fila, columna);
    }
}

int filaTieneElementosDisponibles(int estados[], int filas, int columnas, int fila) {
    for (int i = fila * columnas; i < (fila + 1) * columnas; i++) {
        if (estados[i] == 1) {
            return 1;
        }
    }
    return 0;
}


int encontrarPrimerElementoDisponibleEnFila(int estados[], int filas, int columnas, int fila) {
    for (int i = fila * columnas; i < (fila + 1) * columnas; i++) {
        if (estados[i] == 1) {
            return i % columnas;
        }
    }
    return 0; // En caso de no encontrar elementos disponibles, se devuelve la primera columna
}


// Confiramción
//**********************************************************************************************************************
int confirmation_box(WINDOW* win,char *msg) {
    int highlight = 1;
    int choice;

    mvwprintw(win, 1, 2,msg);
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
//Recibo
//**********************************************************************************************************************
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
