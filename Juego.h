#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#define CATEGORIAS 10

#define ESCALERA    6
#define FULL        7
#define POKER       8
#define GENERALA    9
#define SIN_JUEGO   -1

/* retorna un número al azar entre 1 y 6 */
int tirarDado();

/* deja en dados 5 números al azar entre 1 y 6 */
void tirarTodos(int dados[]);

/* deja en dados un número al azar entre 1 y 6 en la posición pos */
void cambiarDado(int dados[], int pos);

/* ordena los valores en dados de menor a mayor */
void ordenarDados(int dados[]);

/* cuenta en num la cantidad de veces que aparece cada valor en dados */
void contar(int dados[], int num[]);

/* evalúa la tirada y retorna uno de los valores definidos en las macros */
int evaluar(int num[]);

/*
Muestra y permite seleccionar las alternativas disponibles para asignar puntos al fin de cada jugada.
Retorna el puntaje elegido.
*/
int mostrarAlternativas(int num[], int categoria[], int jugada);

/*
Representa una jugada completa de un jugador, con sus alternativas.
Recibe y actualiza un vector con las categorías jugadas
y retorna el puntaje obtenido en esa tirada.
*/
int jugada(int categoria[]);
/* dibuja la cara de un dado a partir de la posición x,y */
void dibujar(int dado, int x, int y, int cont);

int dibujarTodos(int dados[], int x, int y, int destino);
int tirarDados(int tirar[],  int x, int y, int dados[]);

void dibujarTodoslosdados (int dados[],int x, int y);

int mostrarpuntos (char nombre[], int alternativa[], char nombremayor[]);

int totalpuntos2jugadores(char nombre1[],char nombre2[] ,int jugador2[], int jugador1[], char nombremayor[]);

void puntajemasalto(char nombre[], int totalpuntos);


#endif
