#ifndef DATABASEHABITOS_H
#define DATABASEHABITOS_H

#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std;

void crearTablaHabitos(sqlite3* db);
void bdRegistrarHabito(sqlite3* db, const string& contrasenha, const string& pasos, const string& agua, const string& sueño, const string& fecha);
void bdMostrarProgreso(sqlite3* db, const string& contrasenha);

// Función para crear la tabla de hábitos
void crearTablaHabitos(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS Habitos ("
        "PacienteCodigo TEXT NOT NULL, "
        "Pasos TEXT NOT NULL, "
        "Agua TEXT NOT NULL, "
        "Sueno TEXT NOT NULL, "
        "Fecha TEXT NOT NULL);";
    char* errMsg;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error al crear la tabla de hábitos: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

// Función para registrar el hábito en la base de datos
void bdRegistrarHabito(sqlite3* db, const string& contrasenha, const string& pasos, const string& agua, const string& sueño, const string& fecha) {
    string sql = "INSERT INTO Habitos (PacienteCodigo, Pasos, Agua, Sueno, Fecha) VALUES ('" +
        contrasenha + "', '" + pasos + "', '" + agua + "', '" + sueño + "', '" + fecha + "');";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error al registrar el habito: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "\nHabito registrado correctamente.\n";
        // Pausa antes de limpiar la pantalla
        cout << "\n\nPresione Enter para continuar...";
        cin.ignore(); // Espera a que el usuario presione Enter
        system("cls");
    }
}

// Función para mostrar el progreso semanal
void bdMostrarProgreso(sqlite3* db, const string& contrasenha) {
    string sql = "SELECT Pasos, Agua, Sueno, Fecha FROM Habitos WHERE PacienteCodigo = '" + contrasenha + "' ORDER BY Fecha DESC;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "----------------------------------\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* pasos = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* agua = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* sueno = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* fecha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        cout << "Fecha: " << fecha << " | Pasos: " << pasos << " | Agua: " << agua << "L | Suenho: " << sueno << " horas\n";
    }
    cout << "----------------------------------\n";

    sqlite3_finalize(stmt);

    // Pausa para que el usuario pueda leer el progreso
    cout << "\n\nPresione Enter para regresar al menu...";
    cin.ignore();  // Limpia el buffer de entrada

    // Limpia la pantalla antes de regresar al menú
    system("cls");
}

#endif

