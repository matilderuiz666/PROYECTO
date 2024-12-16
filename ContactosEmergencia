#ifndef CONTACTOSEMERGENCIA_H
#define CONTACTOSEMERGENCIA_H

#include <iostream>
#include <string>
#include "DatabaseContactosEmergencia.h" // Archivo que contiene la lógica de base de datos de contactos de emergencia

using namespace std;

void mo_Menu();
void añadirContacto(sqlite3* db, const string& contrasenha);
void consultarContactos(sqlite3* db, const string& contrasenha);
void eliminarContacto(sqlite3* db, const string& contrasenha);

namespace base_datos {  //organiza el código sin duplicar el main
    void ContactosEmergencia(sqlite3* db, const string& contrasenha) {
        // Crear la tabla de contactos si no existe
        crearTablaContactos(db);

        int opc;
        do {
            mo_Menu();
            cin >> opc;
            system("cls");
            cin.ignore(); // Limpiar el buffer de entrada

            switch (opc) {
            case 1:
                añadirContacto(db, contrasenha);
                break;
            case 2:
                consultarContactos(db, contrasenha);
                break;
            case 3:
                eliminarContacto(db, contrasenha);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida. Por favor, intente nuevamente.\n";
                break;
            }
        } while (opc != 0);

        // Cerrar la base de datos
        sqlite3_close(db);
    }
}

void mo_Menu() {
    cout << "\t-----------------------------------\n";
    cout << "\tElija la opcion de su preferencia:\n";
    cout << "\t-----------------------------------\n";
    cout << "\t0. Salir\n";
    cout << "\t1. Anhadir contacto\n";
    cout << "\t2. Consultar contactos\n";
    cout << "\t3. Eliminar contacto\n";
    cout << "\nIngrese su opcion: ";
}

void añadirContacto(sqlite3* db, const string& contrasenha) {
    string nombre, relacion, telefono;

    // Solicitar los datos del contacto al usuario
    cout << "\nIngrese el nombre del contacto: ";
    getline(cin, nombre);

    cout << "Ingrese la relacion del contacto (ej. Hija, Vecino, etc.): ";
    getline(cin, relacion);

    cout << "Ingrese el telefono del contacto: ";
    getline(cin, telefono);

    // Pasar los datos a la función de la base de datos
    bdAñadirContacto(db, contrasenha, nombre, relacion, telefono);
}

void consultarContactos(sqlite3* db, const string& contrasenha) {
    cout << "\nContactos de emergencia: \n";
    bdConsultarContactos(db, contrasenha); // Llama a la función de la base de datos
}

void eliminarContacto(sqlite3* db, const string& contrasenha) {
    string nombre;

    cout << "\nIngrese el nombre del contacto a eliminar: ";
    getline(cin, nombre);

    bdEliminarContacto(db, contrasenha, nombre);
}

#endif

