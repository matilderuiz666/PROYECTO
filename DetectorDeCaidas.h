#ifndef DETECTORDECAIDAS_H
#define DETECTORDECAIDAS_H

#include <iostream>
#include <string>
#include "sqlite3.h"  // Librería para la base de datos

using namespace std;

void crearTablaSignos(sqlite3* db);
void mostrarSignosVitales(sqlite3* db, const string& LoginPass);
void simularSignos(sqlite3* db, const string& LoginPass);
void simularCaida(sqlite3* db);

namespace base_datos {
    void DetectorCaidas(sqlite3* db, const string& LoginPass) {
        crearTablaSignos(db);

        int option;
        do {
            cout << "\t\t\t\t" << endl;
            cout << "\t*-*-*-*-*-*-*\t" << endl;
            cout << "\tHealth-Grand\t" << endl;
            cout << "\t1. Ver signos vitales\t" << endl;
            cout << "\t2. Simular signos vitales\t" << endl;
            cout << "\t0. Salir\t" << endl;
            cout << "\t*-*-*-*-*-*-*\t" << endl;
            cout << "\t\t\t\t" << endl;
            cin >> option;
            cin.ignore();
            system("cls");

            switch (option) {
            case 1:
                mostrarSignosVitales(db, LoginPass);
                break;
            case 2:
                simularSignos(db, LoginPass);
                break;
            case 0:
                cout << "\tSaliendo..." << endl;
                break;
            default:
                cout << "\tOpción no válida" << endl;
                break;
            }
        } while (option != 0);
    }
}

void crearTablaSignos(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS SignosVitales ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "RitmoCardiaco INTEGER, "
        "FrecuenciaRespiratoria INTEGER, "
        "Temperatura REAL, "
        "PresionArterial INTEGER, "
        "Caida INTEGER);";
    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        cout << "Error al crear la tabla: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
    else {
        cout << "Tabla 'SignosVitales' creada exitosamente." << endl;
    }
}

void mostrarSignosVitales(sqlite3* db, const string& LoginPass) {
    string sql = "SELECT * FROM SignosVitales WHERE ID = 1";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cout << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        cout << "\tRITMO CARDIACO: " << sqlite3_column_int(stmt, 1) << endl;
        cout << "\tFRECUENCIA RESPIRATORIA: " << sqlite3_column_int(stmt, 2) << endl;
        cout << "\tTEMPERATURA: " << sqlite3_column_double(stmt, 3) << endl;
        cout << "\tPRESION ARTERIAL: " << sqlite3_column_int(stmt, 4) << endl;
        cout << "\tCAIDA: " << sqlite3_column_int(stmt, 5) << endl;
    }
    else {
        cout << "No se encontraron signos vitales. Por favor, registre primero los signos vitales." << endl;
    }

    sqlite3_finalize(stmt);
    // Pausa antes de limpiar la pantalla
    cout << "\n\nPresione Enter para volver...";
    cin.ignore(); // Espera a que el usuario presione Enter

    system("cls");
}

void simularSignos(sqlite3* db, const string& LoginPass) {
    int option;
    int ritmoCardiaco = 0, frecuenciaRespiratoria = 0, presionArterial = 0, caida = 0;
    double temperatura = 0.0;

    do {
        system("cls");

        cout << "\t*-*-*-*-*-*-*\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\t1. Simular Ritmo Cardiaco\t" << endl;
        cout << "\t2. Simular Frecuencia Respiratoria\t" << endl;
        cout << "\t3. Simular Temperatura\t" << endl;
        cout << "\t4. Simular Presion Arterial\t" << endl;
        cout << "\t5. Simular Caida\t" << endl;
        cout << "\t0. Atras\t" << endl;
        cout << "\t*-*-*-*-*-*-*\t" << endl;
        cin >> option;
        cin.ignore();

        switch (option) {
        case 1:
            cout << "\tINGRESE RITMO CARDIACO: ";
            cin >> ritmoCardiaco;
            break;
        case 2:
            cout << "\tINGRESE FRECUENCIA RESPIRATORIA: ";
            cin >> frecuenciaRespiratoria;
            break;
        case 3:
            cout << "\tINGRESE TEMPERATURA: ";
            cin >> temperatura;
            break;
        case 4:
            cout << "\tINGRESE PRESION ARTERIAL: ";
            cin >> presionArterial;
            break;
        case 5:
            simularCaida(db);
            break;
        case 0:
            cout << "\tSaliendo..." << endl;
            break;
        default:
            cout << "\tOpción no permitida\n";
            break;
        }

        string sql = "UPDATE SignosVitales SET RitmoCardiaco = ?, "
            "FrecuenciaRespiratoria = ?, Temperatura = ?, "
            "PresionArterial = ?, Caida = ? WHERE ID = 1";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

        if (rc != SQLITE_OK) {
            cout << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
            return;
        }

        sqlite3_bind_int(stmt, 1, ritmoCardiaco);
        sqlite3_bind_int(stmt, 2, frecuenciaRespiratoria);
        sqlite3_bind_double(stmt, 3, temperatura);
        sqlite3_bind_int(stmt, 4, presionArterial);
        sqlite3_bind_int(stmt, 5, caida);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            cout << "Error al actualizar los signos vitales: " << sqlite3_errmsg(db) << endl;
        }
        else {
            cout << "Signos vitales actualizados correctamente." << endl;
        }

        sqlite3_finalize(stmt);

        system("cls");

    } while (option != 0);
}

void simularCaida(sqlite3* db) {
    int caida;
    do {
        system("cls");
        cout << "\tSimulacion de Caida" << endl;
        cout << "\t1. Simular Caida\n";
        cout << "\t0. Parar Simulacion de Caida\n";
        cin >> caida;
        cin.ignore();

        if (caida == 1) {
            cout << "\tCaida detectada! Actualizando datos..." << endl;

            string sql = "UPDATE SignosVitales SET Caida = Caida + 1 WHERE ID = 1;";
            char* errorMessage = nullptr;
            int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
            if (rc != SQLITE_OK) {
                cout << "Error al actualizar la caída: " << errorMessage << endl;
                sqlite3_free(errorMessage);
            }
            // Pausa antes de limpiar la pantalla
            cout << "\n\nPresione Enter para volver...";
            cin.ignore(); // Espera a que el usuario presione Enter
        }
        else if (caida == 0) {
            cout << "\tSimulacion de caida detenida." << endl;
            // Pausa antes de limpiar la pantalla
            cout << "\n\nPresione Enter para continuar...";
            cin.ignore(); // Espera a que el usuario presione Enter
        }
        else {
            cout << "\tOpción no válida. Inténtelo de nuevo." << endl;
        }

    } while (caida != 0);

    system("cls");
    cout << "Regresando al menú principal..." << endl;
}

#endif
