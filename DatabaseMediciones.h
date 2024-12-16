#ifndef DATABASEMEDICIONES_H
#define DATABASEMEDICIONES_H

#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std;

void crearTablaMediciones(sqlite3* db);
void bdRegistrarMedicion(sqlite3* db, const string& contrasenha, const string& tipo, const string& valor, const string& fecha, const string& hora);
void bdMostrarMediciones(sqlite3* db, const string& contrasenha);

// Función para crear la tabla de mediciones
void crearTablaMediciones(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS Mediciones ("
        "PacienteCodigo TEXT NOT NULL, "
        "Tipo TEXT NOT NULL, "
        "Valor TEXT NOT NULL, "
        "Fecha TEXT NOT NULL, "
        "Hora TEXT NOT NULL);";
    char* errMsg;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error al crear la tabla de mediciones: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

// Función para registrar la medición en la base de datos
void bdRegistrarMedicion(sqlite3* db, const string& contrasenha, const string& tipo, const string& valor, const string& fecha, const string& hora) {
    string sql = "INSERT INTO Mediciones (PacienteCodigo, Tipo, Valor, Fecha, Hora) VALUES ('" +
        contrasenha + "', '" + tipo + "', '" + valor + "', '" + fecha + "', '" + hora + "');";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error al registrar la medición: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "\nMedicion registrada correctamente.\n";
        // Pausa antes de limpiar la pantalla
        cout << "\n\nPresione Enter para continuar...";
        cin.ignore(); // Espera a que el usuario presione Enter
        system("cls");
    }
}

// Función para mostrar las mediciones recientes
void bdMostrarMediciones(sqlite3* db, const string& contrasenha) {
    string sql = "SELECT Tipo, Valor, Fecha, Hora FROM Mediciones WHERE PacienteCodigo = '" + contrasenha + "' ORDER BY Fecha DESC, Hora DESC;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "----------------------------------\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* tipo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* valor = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* fecha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* hora = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        cout << tipo << ": " << valor << ", " << fecha << ", " << hora << endl;
    }
    cout << "----------------------------------\n";

    sqlite3_finalize(stmt);

    // Pausa para que el usuario pueda leer las mediciones
    cout << "\n\nPresione Enter para regresar al menu...";
    cin.ignore();  // Limpia el buffer de entrada

    // Limpia la pantalla antes de regresar al menú
    system("cls");
}

#endif
