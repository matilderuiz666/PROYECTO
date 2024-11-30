#ifndef DATABASEHORARIO_H
#define DATABASEHORARIO_H

#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std;

void crearTablaHorarios(sqlite3* db);
void bdRegistrar(sqlite3* db, const string& contrasenha, const string& actividad, const string& hora);
void bdMostrar(sqlite3* db, const string& contrasenha);

// Función para crear la tabla de horarios
void crearTablaHorarios(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS Horarios ("
        "PacienteCodigo TEXT NOT NULL, "
        "Actividad TEXT NOT NULL, "
        "Hora TEXT NOT NULL);";
    char* errMsg;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error al crear la tabla: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

// Función para registrar actividad en la base de datos
void bdRegistrar(sqlite3* db, const string& contrasenha, const string& actividad, const string& hora) {
    string sql = "INSERT INTO Horarios (PacienteCodigo, Actividad, Hora) VALUES ('" +
        contrasenha + "', '" + actividad + "', '" + hora + "');";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error al registrar la actividad: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "\nActividad registrada correctamente.\n";

        // Pausa antes de limpiar la pantalla
        cout << "\n\nPresione Enter para continuar...";
        cin.ignore(); // Espera a que el usuario presione Enter

        system("cls");
    }
}


// Función para mostrar el horario
void bdMostrar(sqlite3* db, const string& contrasenha) {
    string sql = "SELECT Actividad, Hora FROM Horarios WHERE PacienteCodigo = '" + contrasenha + "' ORDER BY Hora ASC;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "----------------------------------\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* actividad = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* hora = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cout << "Hora: " << hora << " | Actividad: " << actividad << endl;
    }
    cout << "----------------------------------\n";

    sqlite3_finalize(stmt);

    // Pausa para que el usuario pueda leer el horario
    cout << "\n\nPresione Enter para regresar al menu...";
    cin.ignore();  // Limpia el buffer de entrada

    // Limpia la pantalla antes de regresar al menú
    system("cls");
}

void bdEliminar(sqlite3* db, const string& contrasenha, const string& actividad) {
    string sql = "DELETE FROM Horarios WHERE PacienteCodigo = '" + contrasenha + "' AND Actividad = '" + actividad + "';";
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error al eliminar la actividad: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "\nActividad eliminada correctamente.\n";

        // Pausa antes de limpiar la pantalla
        cout << "\n\nPresione Enter para continuar...";
        cin.ignore(); // Espera a que el usuario presione Enter

        system("cls");
    }
}

#endif
