#include "Juego.h"

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>

using namespace std;

const char *CATEGORIA[] = {
    "As",               // 0
    "Dos",              // 1
    "Tres",             // 2
    "Cuatro",           // 3
    "Cinco",            // 4
    "Seis",             // 5
    "Escalera",         // 6
    "Full",             // 7
    "Poker",            // 8
    "Generala"          // 9
};

const int VALOR[] = { 1, 2, 3, 4, 5, 6, 20, 30, 40, 60 };

/* función auxiliar para ubicar el cursor en la pantalla de texto */
void gotoxy(int x, int y){
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int tirarDado() {
    return (rand()%6)+1;
}

void tirarTodos(int dados[]) {
    for(int i = 0; i < 5; i++) {
        dados[i] = tirarDado();
    }
}

void cambiarDado(int dados[], int pos) {
    dados[pos] = tirarDado();
}

void ordenarDados(int dados[]) {
    bool cambio;
    int aux;
    int tam = 5;

    do {
        cambio = false;
        for(int i = 1; i < tam; i++) {
            if(dados[i] < dados[i-1]) {
                aux = dados[i];
                dados[i] = dados[i-1];
                dados[i-1] = aux;
                cambio = true;
            }
        }
        tam--;
    } while(cambio);
}

int evaluar(int num[]) {
    int max = num[0];
    int i;

    for(i = 1; i < 6; i++) {
        if(num[i] > max) {
            max = num[i];
        }
    }

    switch(max) {
    case 5:
        return GENERALA;
    case 4:
        return POKER;
    case 3:
        for(i = 0; i < 6 && num[i] != 2; i++);
        return i < 6? FULL: SIN_JUEGO;
    case 1:
        return num[0] == 0 || num[5] == 0? ESCALERA: SIN_JUEGO;
    }

    return SIN_JUEGO;
}

void contar(int dados[], int num[]) {
    int i;

    for(i = 0; i < 6; i++) {
        num[i] = 0;
    }

    for(i = 0; i < 5; i++) {
        num[dados[i]-1]++;
    }
}

int jugada(int categoria[]) {
    int tirada[5];
    int numeros[6];

    tirarTodos(tirada);

    ordenarDados(tirada);
    contar(tirada, numeros);
//    mostrarDados(tirada);
return 0;
}

int mostrarAlternativas(int num[], int categoria[], int jugada) {
    int i;
    int valor[10];
    int juego;
    int opcion;

    for(i = 0; i < 6; i++) {
        if(categoria[i] < 0) {
            cout << setw(4) << left << i+1 << setw(10) << left << CATEGORIA[i];
            valor[i] = VALOR[i] * num[i];
            cout << valor[i] << endl;
        } else {
            valor[i] = -1;
        }
    }

    juego = evaluar(num);

    for(i = 6; i < 10; i++) {
        if(categoria[i] < 0) {
            cout << setw(4) << left << i+1 << setw(10) << left << CATEGORIA[i];
            if(i == juego) {
                valor[i] = VALOR[i];
                if(jugada == 1) {
                    valor[i] += 5;
                }
            } else {
                valor[i] = 0;
            }
            cout << valor[i] << endl;
        } else {
            valor[i] = -1;
        }
    }

    cout << endl << "Que desea hacer? ";
    cin >> opcion;

    while(opcion < 1 || opcion > 10 || valor[opcion-1] < 0) {
        cout << "Opcion incorrecta" << endl;
        cout << "Que desea hacer? ";
        cin >> opcion;
    }

    categoria[opcion-1] = valor[opcion-1];

    return valor[opcion-1];
}

void dibujar(int dado, int x, int y, int cont) {

    gotoxy(x+1, y);
    cout << "-------";
    gotoxy(x, y+1);
    cout << "|       |";
    gotoxy(x, y+2);
    cout << "|       |";
    gotoxy(x, y+3);
    cout << "|       |";
    gotoxy(x+1, y+4);
    cout << "-------";
    gotoxy(x+1, y+5);
    cout << "DADO: " << cont+1;

    x+=2;
    y++;

    switch(dado) {
    case 1:
        gotoxy(x+2, y+1);
        cout << "*";
        break;
    case 2:
        gotoxy(x+2, y);
        cout << "*";
        gotoxy(x+2, y+2);
        cout << "*";
        break;
    case 3:
        gotoxy(x, y);
        cout << "*";
        gotoxy(x+2, y+1);
        cout << "*";
        gotoxy(x+4, y+2);
        cout << "*";
        break;
    case 4:
        gotoxy(x, y);
        cout << "*   *";
        gotoxy(x, y+2);
        cout << "*   *";
        break;
    case 5:
        gotoxy(x, y);
        cout << "*   *";
        gotoxy(x+2,y+1);
        cout << "*";
        gotoxy(x,y+2);
        cout << "*   *";
        break;
    case 6:
        gotoxy(x, y);
        cout << "*   *";
        gotoxy(x, y+1);
        cout << "*   *";
        gotoxy(x, y+2);
        cout << "*   *";
        break;
    }
}

int dibujarTodos(int dados[],int x, int y, int destino) {
    int i;
    int h = x;
    int tirar[4];
    int corte;


    for(i = 0; i < 5; i++) {
        dibujar(dados[i], h, y, i);
        h += 10;
    }



   corte = tirarDados(tirar, x, y+10, dados);


     return corte;

}

int tirarDados(int tirar[], int x, int y, int dados[]) {
    int cant;
    int pos=0;
    gotoxy(x, y);
    cout << endl << "Cuantos dados quiere volver a tirar? ";
    cin >> cant;

    while(cant < 0 || cant > 5) {
        cout << endl << "Cantidad incorrecta";
        cout << endl << "Cuantos dados quiere volver a tirar? ";
        cin >> cant;
    }

    if(cant > 0 && cant < 5) {
        int i, j;
        int dado;
        for(i = 0; i < cant; i++) {
            do {
                cout << endl << "Que dado quiere volver a tirar? ";
                cin >> dado;
                while(dado < 1 || dado > 5) {
                    cout << endl << "Dado incorrecto";
                    cout << endl << "Que dado quiere volver a tirar? ";
                    cin >> dado;
                }

                for(j = 0; j < i && tirar[j] != dado; j++);

                if(j < i) {
                    cout << endl << "Ese dado ya fue incluido" << endl;
                } else {
                    tirar[i] = dado;
                }
            } while(j < i);

            pos=dado-1;
            cambiarDado(dados,pos);


        }


    }
    system("cls");
     if (cant==5){
        tirarTodos(dados);
     }
    return cant;
}


void dibujarTodoslosdados (int dados[],int x, int y){

    int i;
    int h = x;



    for(i = 0; i < 5; i++) {
        dibujar(dados[i], h, y, i);
        h += 10;
    }



}

int mostrarpuntos (char nombre[] , int alternativa[], char nombremayor[] ){
int i;
int puntos=0;
for(i=0;i<30;i++)
{
nombremayor[i] = nombre[i];
}

//strcpy(nombremayor, nombre);
//strncpy(nombremayor, nombre, 30);
//strcpy(nombremayor[], nombre[]);

  for(i=0; i<10; i++)  {
puntos+=alternativa[i];
system("cls");

cout<<" --------------------------------------------------"<<endl;
cout<<" | JUGADOR:"<<nombre<<"     "  "|"  "  PUNTOS: "<<puntos<<"                |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | COD | PREMIO             | PUNTOS              |"<<endl;
cout<<" | -----------------------------------------------|"<<endl;
cout<<" | 1   | AS                 |  "<<alternativa[0] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 2   | DOS                |  "<<alternativa[1] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 3   | TRES               |  "<<alternativa[2] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 4   | CUATRO             |  "<<alternativa[3] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 5   | CINCO              |  "<<alternativa[4] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 6   | SEIS               |  "<<alternativa[5] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 7   | ESCALERA           |  "<<alternativa[6] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 8   | FULL               |  "<<alternativa[7] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 9   | POKER              |  "<<alternativa[8] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 10  | GENERALA           |  "<<alternativa[9] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" |       TOTAL              | "<<    puntos      <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;


  }


  system("pause>null");

  return puntos;

}


int totalpuntos2jugadores(char nombre1[],char nombre2[], int jugador2[], int jugador1[], char nombremayor[]){

int i,x,j;
int punto1=0;
int punto2=0;
int mayorpunto=0;

  for(i=0; i<10; i++)  {
punto1+=jugador1[i];
punto2+=jugador2[i];

  }

  if(punto1>punto2){
        mayorpunto=punto1;
        for(i=0;i<30;i++)
        {
        nombremayor[i] = nombre1[i];
        }

    for(x=0; x<10; x++){
system("cls");
cout<<" --------------------------------------------------"<<endl;
cout<<" | JUGADOR:"<<nombre1<<"     "  "|"  "  PUNTOS: "<<punto1<<"                |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | COD | PREMIO             | PUNTOS              |"<<endl;
cout<<" | -----------------------------------------------|"<<endl;
cout<<" | 1   | AS                 |  "<<jugador1[0] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 2   | DOS                |  "<<jugador1[1] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 3   | TRES               |  "<<jugador1[2] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 4   | CUATRO             |  "<<jugador1[3] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 5   | CINCO              |  "<<jugador1[4] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 6   | SEIS               |  "<<jugador1[5] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 7   | ESCALERA           |  "<<jugador1[6] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 8   | FULL               |  "<<jugador1[7] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 9   | POKER              |  "<<jugador1[8] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 10  | GENERALA           |  "<<jugador1[9] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" |       TOTAL              | "<<    punto1      <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;

    }
    system("pause>null");

    }


     else{

         mayorpunto=punto2;
        strcpy(nombremayor, nombre2);

      for (j=0; j<10; j++){

system("cls");

cout<<" --------------------------------------------------"<<endl;
cout<<" | JUGADOR:"<<nombre2<<"     "  "|"  "  PUNTOS: "<<punto2<<"                |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | COD | PREMIO             | PUNTOS              |"<<endl;
cout<<" | -----------------------------------------------|"<<endl;
cout<<" | 1   | AS                 |  "<<jugador2[0] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 2   | DOS                |  "<<jugador2[1] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 3   | TRES               |  "<<jugador2[2] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 4   | CUATRO             |  "<<jugador2[3] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 5   | CINCO              |  "<<jugador2[4] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 6   | SEIS               |  "<<jugador2[5] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 7   | ESCALERA           |  "<<jugador2[6] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 8   | FULL               |  "<<jugador2[7] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 9   | POKER              |  "<<jugador2[8] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" | 10  | GENERALA           |  "<<jugador2[9] <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;
cout<<" |       TOTAL              | "<<    punto2      <<"                  |"<<endl;
cout<<" |------------------------------------------------|"<<endl;





      }
       system("pause>null");

     }

    return mayorpunto;


}



void puntajemasalto(char nombre[] , int totalpuntos){

     cout<<"-------------------------------------|"<<endl;
    cout<< "EL JUGADOR CON EL PUNTAJE MAS ALTO   |"<<endl;
    cout<<"-------------------------------------|"<<endl;
    cout<<"|  NOMBRE: "<<nombre<<                "                      |"<<endl;
    cout<<"|------------------------------------|"<<endl;
    cout<<"|  PUNTAJE: "<<totalpuntos<<          "                      |"<<endl;
    cout<<"|------------------------------------|"<<endl;

}
