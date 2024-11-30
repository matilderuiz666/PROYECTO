#ifndef MEDICAMENTOS_H
#define MEDICAMENTOS_H

#include <iostream>
#include <string>
#include "sqlite3.h"
#include "DatabaseMedicamentos.h" // Archivo que contiene las funciones de base de datos

using namespace std;

// Función para agregar un medicamento
void agregarMedicamento(sqlite3* db, const string& codigoPaciente);

// Función para mostrar los medicamentos de un paciente
void mostrarMedicamentos(sqlite3* db, const string& codigoPaciente);

// Función para monitorear el cumplimiento del tratamiento
void monitoreoMedicamentos(sqlite3* db, const string& codigoPaciente);

namespace base_datos {
    void Medicamentos(sqlite3* db, const string& codigoPaciente) {
        // Crear la tabla de medicamentos si no existe
        crearTablaMedicamentos(db);

        int opcion;
        do {
            cout << "\n\t--- Menu de Medicamentos ---\n\n";
            cout << "\t1. Lista de medicamentos\n";
            cout << "\t2. Monitorear cumplimiento de tratamiento\n";
            cout << "\t3. Agregar medicamento\n";
            cout << "\t0. Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore(); // Limpiar buffer
            system("cls");

            switch (opcion) {
            case 1:
                mostrarMedicamentos(db, codigoPaciente);
                break;
            case 2:
                monitoreoMedicamentos(db, codigoPaciente);
                break;
            case 3:
                agregarMedicamento(db, codigoPaciente);
                break;
            case 0:
                cout << "Saliendo del menu de medicamentos...\n";
                break;
            default:
                cout << "Opción no valida. Por favor, intente nuevamente.\n";
                break;
            }
        } while (opcion != 0);
    }
}

void agregarMedicamento(sqlite3* db, const string& codigoPaciente) {
    string nombre, horario;
    int dosis;

    cout << "\nIngrese el nombre del medicamento: ";
    getline(cin, nombre);
    cout << "Ingrese la dosis: ";
    cin >> dosis;
    cin.ignore();
    cout << "Ingrese el horario (ejemplo: 08:00, 14:00): ";
    getline(cin, horario);
    // Pausa antes de limpiar la pantalla
    cout << "\nPresione Enter para continuar...";
    cin.ignore(); // Espera a que el usuario presione Enter

    system("cls");

    bdAgregarMedicamento(db, codigoPaciente, nombre, dosis, horario);
}

void mostrarMedicamentos(sqlite3* db, const string& codigoPaciente) {
    cout << "\n--- Lista de Medicamentos ---\n\n";
    bdMostrarMedicamentos(db, codigoPaciente);
    // Pausa antes de limpiar la pantalla
    cout << "\nPresione Enter para continuar...";
    cin.ignore(); // Espera a que el usuario presione Enter

    system("cls");
}

void monitoreoMedicamentos(sqlite3* db, const string& codigoPaciente) {
    cout << "\n--- Monitoreo de Medicamentos ---\n\n";
    bdMonitoreoMedicamentos(db, codigoPaciente);
    // Pausa antes de limpiar la pantalla
    cout << "\nPresione Enter para continuar...";
    cin.ignore(); // Espera a que el usuario presione Enter

    system("cls");
}

#endif
