#ifndef HABITOS_H
#define HABITOS_H

#include <iostream>
#include <string>
#include "DatabaseHabitos.h" // Archivo que contiene la lógica de base de datos de hábitos

using namespace std;

void Menu();
void registrarHabito(sqlite3* db, const string& contrasenha);
void mostrarProgreso(sqlite3* db, const string& contrasenha);

namespace base_datos {  //organiza el codigo sin duplicar el main
    void Habitos(sqlite3* db, const string& contrasenha) {
        // Crear la tabla de hábitos si no existe
        crearTablaHabitos(db);

        int opc;
        do {
            Menu();
            cin >> opc;
            system("cls");
            cin.ignore(); // Limpiar el buffer de entrada

            switch (opc) {
            case 1:
                registrarHabito(db, contrasenha);
                break;
            case 2:
                mostrarProgreso(db, contrasenha);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no valida. Por favor, intente nuevamente.\n";
                break;
            }
        } while (opc != 0);

        // Cerrar la base de datos
        sqlite3_close(db);
    }
}

void Menu() {
    cout << "\t-----------------------------------\n";
    cout << "\tElija la opcion de su preferencia:\n";
    cout << "\t-----------------------------------\n";
    cout << "\t0. Salir\n";
    cout << "\t1. Registrar actividad diaria\n";
    cout << "\t2. Consultar progreso semanal\n";
    cout << "\nIngrese su opcion: ";
}

void registrarHabito(sqlite3* db, const string& contrasenha) {
    string pasos, agua, sueño, fecha;

    // Solicitar los datos de hábitos al usuario
    cout << "\nIngrese el numero de pasos caminados hoy: ";
    getline(cin, pasos);

    cout << "Ingrese cuantos litros de agua bebio hoy: ";
    getline(cin, agua);

    cout << "Ingrese cuantas horas durmio anoche: ";
    getline(cin, sueño);

    // Pedir la fecha al usuario en formato YYYY-MM-DD
    cout << "Ingrese la fecha (formato YYYY-MM-DD): ";
    getline(cin, fecha);

    // Pasar los datos a la función de la base de datos
    bdRegistrarHabito(db, contrasenha, pasos, agua, sueño, fecha);
}

void mostrarProgreso(sqlite3* db, const string& contrasenha) {
    cout << "\nProgreso semanal: \n";
    bdMostrarProgreso(db, contrasenha); // Llama a la función de la base de datos
}

#endif
