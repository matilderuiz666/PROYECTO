#ifndef MEDICIONES_H
#define MEDICIONES_H

#include <iostream>
#include <string>
#include "DatabaseMediciones.h" // Archivo que contiene la lógica de base de datos de mediciones

using namespace std;

void m_Menu();
void registrarMedicion(sqlite3* db, const string& contrasenha);
void mostrarMediciones(sqlite3* db, const string& contrasenha);

namespace base_datos {  //organiza el código sin duplicar el main
    void Mediciones(sqlite3* db, const string& contrasenha) {
        // Crear la tabla de mediciones si no existe
        crearTablaMediciones(db);

        int opc;
        do {
            m_Menu();
            cin >> opc;
            system("cls");
            cin.ignore(); // Limpiar el buffer de entrada

            switch (opc) {
            case 1:
                registrarMedicion(db, contrasenha);
                break;
            case 2:
                mostrarMediciones(db, contrasenha);
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

void m_Menu() {
    cout << "\t-----------------------------------\n";
    cout << "\tElija la opcion de su preferencia:\n";
    cout << "\t-----------------------------------\n";
    cout << "\t0. Salir\n";
    cout << "\t1. Registrar medicion\n";
    cout << "\t2. Consultar mediciones recientes\n";
    cout << "\nIngrese su opcion: ";
}

void registrarMedicion(sqlite3* db, const string& contrasenha) {
    string tipo, valor, fecha, hora;

    // Solicitar los datos de la medición al usuario
    cout << "\nIngrese el tipo de medicion (presion arterial, glucosa, temperatura): ";
    getline(cin, tipo);

    cout << "Ingrese el valor de la medicion: ";
    getline(cin, valor);

    cout << "Ingrese la fecha (formato YYYY-MM-DD): ";
    getline(cin, fecha);

    cout << "Ingrese la hora (formato HH:MM): ";
    getline(cin, hora);

    // Pasar los datos a la función de la base de datos
    bdRegistrarMedicion(db, contrasenha, tipo, valor, fecha, hora);
}

void mostrarMediciones(sqlite3* db, const string& contrasenha) {
    cout << "\nMediciones recientes: \n";
    bdMostrarMediciones(db, contrasenha); // Llama a la función de la base de datos
}

#endif

