#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Juego.h"

using namespace std;

int main()
{
    int dados[5];
    int numeros[6];
    int alternativas[10];
    int opcion,controndas=0,i;
    char nombre[30];
    int tiro;
    int corte;
    int totalpuntos;
    ///2judores

    char nombre1[30];
    char nombre2[30];
    char nombremayor[30];
    int jugador1[10], jugador2[10];

    srand(time(NULL));

    for(int i = 0; i < 10; i++) {
        alternativas[i] = -1;
    }

    while (true){
    system("cls");
    cout<< "----------------------------------------"<<endl;
    cout<< "|     BIENVENIDO A LA GENERALA          |"<<endl;
    cout<< "----------------------------------------"<<endl;
    cout<<endl;
    cout<< "1- NUEVO JUEGO PARA UN JUGADOR. "<<endl;
    cout<< "2- NUEVO JUEGO PARA DOS JUGADORES. "<<endl;
    cout<< "3- MOSTRAR PUNTAJE MAS ALTO. "<<endl;
    cout<< "0- SALIR DEL JUEGO. "<<endl<<endl;

        cout <<"ELIGA UNA OPCION: " << endl;
        cin >> opcion;
        switch(opcion){
            case 0:
                system("cls");
                char salir;
                cout << "CONFIRMAR (S/N)"<<endl;
                cin >>salir;
                if(salir=='S' || salir=='s' ){
                    return 0;
                }

                break;
            case 1:
            totalpuntos = 0;
            system("cls");
            cout<< "INGRES NOMBRE DEL JUGADOR: ";
            cin>>nombre;


     controndas=0;
    for (i=1; i<= 3; i++){
    tiro = 0;
    controndas++;

    corte=1;

    cout<<"RONDA: "<<controndas<<"NOMBRE : "<<nombre<<endl;
    while(!(corte == 0 || tiro == 2 )){
        tiro++;
        if(tiro==1){
        tirarTodos(dados);
        contar(dados, numeros);
        system("cls");

        ordenarDados(dados);
        }

        corte = dibujarTodos(dados, 5, 2, tiro);

    }

        system("cls");
        cout<<"RONDA: "<<controndas<<"    NOMBRE : "<<nombre<<endl;
        dibujarTodoslosdados(dados,5,2);
        contar(dados, numeros);
        ordenarDados(dados);
        cout << endl << endl;
        cout << endl << endl;


        mostrarAlternativas(numeros, alternativas, tiro);

        cout << endl << endl;

    }

        totalpuntos = mostrarpuntos(nombre, alternativas, nombremayor);




        break;

            case 2:

        totalpuntos = 0;
       for(int i = 0; i < 10; i++) {
        jugador1[i] = -1;
    }

                system("cls");
                cout<< "INGRESE NOMBRE DEL JUGADOR 1: ";
                cin>>nombre1;
                cout<< "INGRESE NOMBRE DEL JUGADOR 2: ";
                cin>>nombre2;

        system("cls");
        cout<< "INICIA JUEGO PARA JUGADOR 1."<<endl;
        system("pause>null");
    controndas=0;
    for (i=1; i<= 10; i++){
    tiro = 0;
    controndas++;
    corte=1;
    while(!(corte == 0 || tiro == 2 )){
        tiro++;
        if(tiro==1){
        tirarTodos(dados);
        contar(dados, numeros);
        system("cls");
        ordenarDados(dados);
        }

        corte = dibujarTodos(dados, 5, 2, tiro);
    }
        system("cls");
        cout<<"RONDA: "<<controndas<<"    NOMBRE : "<<nombre1<<endl;
        dibujarTodoslosdados(dados,5,2);
        contar(dados, numeros);
        ordenarDados(dados);
        cout << endl << endl;
        cout << endl << endl;
        mostrarAlternativas(numeros, jugador1, tiro);

        cout << endl << endl;

    }




       for(int i = 0; i < 10; i++) {
        jugador2[i] = -1;
    }
        system("cls");
        cout<< "INICIA JUEGO PARA JUGADOR 2."<<endl;
        system("pause>null");

    controndas=0;
    for (i=1; i<= 10; i++){
    tiro = 0;
    controndas++;
    corte=1;
    while(!(corte == 0 || tiro == 2 )){
        tiro++;
        if(tiro==1){
        tirarTodos(dados);
        contar(dados, numeros);
        system("cls");
        ordenarDados(dados);
        }

        corte = dibujarTodos(dados, 5, 2, tiro);
    }
        system("cls");
        cout<<"RONDA: "<<controndas<<"    NOMBRE : "<<nombre2<<endl;
        dibujarTodoslosdados(dados,5,2);
        contar(dados, numeros);
        ordenarDados(dados);
        cout << endl << endl;
        cout << endl << endl;
        mostrarAlternativas(numeros, jugador2, tiro);

        cout << endl << endl;

    }


        totalpuntos = totalpuntos2jugadores(nombre1, nombre2, jugador2, jugador1, nombremayor);




                break;

            case 3:
                system("cls");
                puntajemasalto(nombremayor,totalpuntos);
                system("pause>null");
                break;

        }
}

}
