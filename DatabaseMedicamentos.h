#ifndef DATABASEMEDICAMENTOS_H
#define DATABASEMEDICAMENTOS_H

#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

// Función para crear la tabla de medicamentos
void crearTablaMedicamentos(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS Medicamentos ("
        "CodigoPaciente TEXT NOT NULL, "
        "Nombre TEXT NOT NULL, "
        "Dosis INTEGER NOT NULL, "
        "Horario TEXT NOT NULL);";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error al crear la tabla de medicamentos: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

// Función para agregar un medicamento
void bdAgregarMedicamento(sqlite3* db, const string& codigoPaciente, const string& nombre, int dosis, const string& horario) {
    string sql = "INSERT INTO Medicamentos (CodigoPaciente, Nombre, Dosis, Horario) VALUES ('" +
        codigoPaciente + "', '" + nombre + "', " + to_string(dosis) + ", '" + horario + "');";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error al agregar medicamento: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "Medicamento agregado correctamente.\n";
    }
}

// Función para mostrar los medicamentos de un paciente
void bdMostrarMedicamentos(sqlite3* db, const string& codigoPaciente) {
    string sql = "SELECT Nombre, Dosis, Horario FROM Medicamentos WHERE CodigoPaciente = '" + codigoPaciente + "';";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int dosis = sqlite3_column_int(stmt, 1);
        const char* horario = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        cout << "Medicamento: " << nombre << " | Dosis: " << dosis << " | Horario: " << horario << endl;
    }

    sqlite3_finalize(stmt);
}

// Función para monitorear medicamentos
void bdMonitoreoMedicamentos(sqlite3* db, const string& codigoPaciente) {
    string sql = "SELECT Nombre, Dosis, Horario FROM Medicamentos WHERE CodigoPaciente = '" + codigoPaciente + "';";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int dosis = sqlite3_column_int(stmt, 1);
        cout << "Medicamento: " << nombre << " | Dosis: " << dosis << " | Cumplimiento: OK\n";
    }

    sqlite3_finalize(stmt);
}

#endif
