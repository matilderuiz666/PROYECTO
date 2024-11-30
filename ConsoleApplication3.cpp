#include <iostream>
#include "sqlite3.h"
#include <string>
#include <cstdlib>
#include "DBRegister.h"
#include "Horario.h" //se vincula a este archivo porque es desde aqui que se va al archivo de Horario.h
#include "Medicamentos.h"
using namespace std;

sqlite3* db;

//Abrir tabla y crear tablas
int OpenTable() {
    //abrir tabla
    int rc = sqlite3_open("mi_base_de_datos.db", &db);
    if (rc) {
        cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << endl;
        return rc;
    }
    else {
        cout << "Base de datos abierta correctamente." << endl;
    }

    // Crear las tablas
    const char* sqlCreatePacientes = "CREATE TABLE IF NOT EXISTS Pacientes (" \
        "NOMBRE TEXT NOT NULL," \
        "USUARIO TEXT NOT NULL," \
        "CONTRASENHA TEXT NOT NULL," \
        "CODIGO TEXT NOT NULL);";

    const char* sqlCreateCuidadores = "CREATE TABLE IF NOT EXISTS Cuidadores (" \
        "NOMBRE TEXT NOT NULL," \
        "USUARIO TEXT NOT NULL," \
        "CONTRASENHA TEXT NOT NULL," \
        "CODIGO TEXT NOT NULL);";

    char* errMsg = 0;
    rc = sqlite3_exec(db, sqlCreatePacientes, 0, 0, &errMsg);
    handleError(rc, errMsg);
    rc = sqlite3_exec(db, sqlCreateCuidadores, 0, 0, &errMsg);
    handleError(rc, errMsg);
}

//Mensaje de error sql
void handleError(int rc, char* errMsg) {
    if (rc != SQLITE_OK) {
        cerr << "Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

//Funcion para anhadir un nuevo paciente
void addPaciente(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo) {
    string sql = "INSERT INTO Pacientes (NOMBRE, USUARIO, CONTRASENHA, CODIGO) VALUES ('" +
        nombre + "', '" + usuario + "', '" + contrasenha + "', '" + codigo + "');";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    handleError(rc, errMsg);
}

//Funcion para anhadir un nuevo cuidador
void addCuidador(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo) {
    string sql = "INSERT INTO Cuidadores (NOMBRE, USUARIO, CONTRASENHA, CODIGO) VALUES ('" +
        nombre + "', '" + usuario + "', '" + contrasenha + "', '" + codigo + "');";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    handleError(rc, errMsg);
}

//Leer la base datos y comparar si es correcto las credenciales pacientes
bool readPacientes(const string& LoginUser, const string& LoginPass) {
    const char* sql = "SELECT * FROM Pacientes;";
    sqlite3_stmt* stmt;


    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    bool userFound = false;


    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* NameBase = sqlite3_column_text(stmt, 0);
        const unsigned char* UserBase = sqlite3_column_text(stmt, 1);
        const unsigned char* PassBase = sqlite3_column_text(stmt, 2);

        string User = reinterpret_cast<const char*>(UserBase);
        string Pass = reinterpret_cast<const char*>(PassBase);


        if (LoginUser == User) {
            int opc;
            userFound = true;

            if (LoginPass == Pass) {
                cout << "\t**Bienvenido** " << NameBase << endl;
                do {
                    ShowMenu2();
                    cin >> opc;
                    cin.ignore();
                    system("cls");
                    switch (opc) {
                    case 1:
                        base_datos::Horario(db, LoginPass);
                        break;
                    case 2:
                        base_datos::Medicamentos(db, LoginPass);
                        break;
                    case 0:
                        cout << "saliendo...";
                        break;
                    default:
                        cout << "esta opcion no esta disponible.";
                        break;
                    }            
                } while (opc != 0);
                sqlite3_finalize(stmt);
                return true;
            }
            else {
                cout << "\t**Contrasenha incorrecta**" << endl;
                sqlite3_finalize(stmt);
                return false;
            }
        }
    }


    if (!userFound) {
        cout << "\t**Usuario incorrecto**" << endl;
    }


    sqlite3_finalize(stmt);
    return false;
}

//Leer la base datos y comparar si es correcto las credenciales cuidadores
bool readCuidadores(const string& LoginUser, const string& LoginPass) {
    const char* sql = "SELECT * FROM Cuidadores;";
    sqlite3_stmt* stmt;


    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    bool userFound = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int opc;
        const unsigned char* NameBase = sqlite3_column_text(stmt, 0);
        const unsigned char* UserBase = sqlite3_column_text(stmt, 1);
        const unsigned char* PassBase = sqlite3_column_text(stmt, 2);

        string User = reinterpret_cast<const char*>(UserBase);
        string Pass = reinterpret_cast<const char*>(PassBase);

        if (LoginUser == User) {
            userFound = true;

            if (LoginPass == Pass) {
                cout << "\T**Bienvenido**" << NameBase << endl;
                do {
                    ShowMenu2();
                    cin.ignore();
                    cin >> opc;
                    cin.ignore();
                    switch (opc) {
                    case 1: //horarios
                        base_datos::Horario(db, LoginPass);
                        break;
                    case 2: //Medicamentos
                        base_datos::Medicamentos(db, LoginPass);
                        break;
                    case 0:
                        cout << "Saliendo... ";
                        break;
                    default:
                        cout << "Esta opcion no esta disponible";
                        break;
                    }
                } while (opc != 0);

                sqlite3_finalize(stmt);
                return true;
            }
            else {
                cout << "\T**Contrasenha incorrecta**" << endl;
                sqlite3_finalize(stmt);
                return false;
            }
        }
    }


    if (!userFound) {
        cout << "\t**Usuario incorrecto**" << endl;
    }


    sqlite3_finalize(stmt);
    return false;
}

//PROTOTIPO PARA NO REGISTRAR USUSRAIOS DOBLES
bool RepeatUserPacientes(const string& RegisterUser) {

    const char* sql = "SELECT * FROM Pacientes;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Falla al preparar la consulta:" << sqlite3_errmsg(db) << endl;
        return false;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* UserBase = sqlite3_column_text(stmt, 1);

        string User = reinterpret_cast<const char*>(UserBase);

        if (RegisterUser == User) {
            cout << "\t**Este usuario ya ah sido registrado**" << endl;
            return true;
        }
    }
    return false;
}

// registrar dobles pacientes
bool RepeatUserCuidadores(const string& RegisterUser) {

    const char* sql = "SELECT * FROM Cudiadores;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Falla al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* UserBase = sqlite3_column_text(stmt, 1);

        string User = reinterpret_cast<const char*>(UserBase);

        if (RegisterUser == User) {
            cout << "\t**Este usuario ya ah sido registrado**" << endl;
            return true;
        }
    }
    return false;
}

void ShowMenu2() {
    cout << "\t\t\t\t" << endl;
    cout << "\t*-*-*-*-*-*-*\t" << endl;
    cout << "\t  Health-Grand  \t" << endl;
    cout << "\t1.Horarios\t" << endl;
    cout << "\t2.Medicamentos\t" << endl;
    cout << "\t0.Salir\t" << endl;
    cout << "\t*-*-*-*-*-*-*\t" << endl;
    cout << "\t\t\t\t" << endl;
}
