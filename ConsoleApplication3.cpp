#include <iostream>
#include "sqlite3.h"
#include <string>
#include <cstdlib>
#include "DBRegister.h"
#include "Horario.h" //se vincula a este archivo porque es desde aqui que se va al archivo de Horario.h
#include "Medicamentos.h"
#include "DetectorDeCaidas.h"
#include "vincular.h"// incluir ******
#include "vincularCuidador.h"//incluir****
#include "Alertas.h"//incluir***
#include "Habitos.h"
#include "Mediciones.h"
#include "ContactosEmergencia.h"

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
        const unsigned char* CodeBase = sqlite3_column_text(stmt, 3); //para codigo****

        string User = reinterpret_cast<const char*>(UserBase);
        string Pass = reinterpret_cast<const char*>(PassBase);


        if (LoginUser == User) {
            userFound = true;

            if (LoginPass == Pass) {
                //nueva declaracion***
                string Name = reinterpret_cast<const char*>(NameBase);
                string UserCode = reinterpret_cast<const char*>(CodeBase);

                cout << "\t*Bienvenido* " << Name << endl;

                int opc;
                do {
                    //nuevo menu solo para Pacientes
                    MenuPacientes(Name, UserCode); // Pasar los valores como parámetros
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
                    case 3: //Signos
                        base_datos::DetectorCaidas(db, LoginPass);
                        break;
                    case 4: //habitos
                        base_datos::Habitos(db, LoginPass);
                        break;
                    case 5: //nueva opcion****
                        Perfil(Name, UserCode); // Llamar a Perfil con los valores correctos
                        break;
                    case 6: //Mediciones
                        base_datos::Mediciones(db, LoginPass);
                        break;
                    case 7://nueva opcion****
                        vincularCuidadorParaPaciente(Name, UserCode);
                        break;
                    case 8://nueva opcion****
                        alertasPa();
                        break;
                    case 9: //Contactos
                        base_datos::ContactosEmergencia(db, LoginPass);
                        break;
                    case 0:
                        cout << "Saliendo...";
                        break;
                    default:
                        cout << "Esta opción no está disponible.";
                        break;
                    }
                } while (opc != 0);

                sqlite3_finalize(stmt);
                return true;
            }
            else {
                cout << "\t*Contraseña incorrecta*" << endl;
                sqlite3_finalize(stmt);
                return false;
            }
        }

    }


    if (!userFound) {
        cout << "\t*Usuario incorrecto*" << endl;
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
        const unsigned char* CodeBase = sqlite3_column_text(stmt, 3); //para codigo****

        string User = reinterpret_cast<const char*>(UserBase);
        string Pass = reinterpret_cast<const char*>(PassBase);

        if (LoginUser == User) {
            userFound = true;

            if (LoginPass == Pass) {

                //nueva declaracion***
                string Name = reinterpret_cast<const char*>(NameBase);
                string UserCode = reinterpret_cast<const char*>(CodeBase);

                cout << "\t*Bienvenido*" << NameBase << endl;
                do {
                    MenuCuidadores(Name, UserCode); //nuevo menu solo para cuidadores
                    cin >> opc;
                    cin.ignore();
                    system("cls");
                    switch (opc) {
                    case 1: //horarios
                        base_datos::Horario(db, LoginPass);
                        break;
                    case 2: //Medicamentos
                        base_datos::Medicamentos(db, LoginPass);
                        break;
                    case 3: //Signos
                        base_datos::DetectorCaidas(db, LoginPass);
                        break;
                    case 4: //datos cuidador
                        Perfil(Name, UserCode);
                        break;
                    case 5: //nueva opcion***
                        vincularPaciente();
                        break;
                    case 6: //nueva opcion****
                        vincularCuidadores();
                        break;
                    case 7: //nueva opcion***
                        alertasCui();
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
                cout << "\t*Contrasenha incorrecta*" << endl;
                sqlite3_finalize(stmt);
                return false;
            }
        }
    }


    if (!userFound) {
        cout << "\t*Usuario incorrecto*" << endl;
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
            cout << "\t*Este usuario ya ah sido registrado*" << endl;
            return true;
        }
    }
    return false;
}

// registrar dobles pacientes
bool RepeatUserCuidadores(const string& RegisterUser) {

    const char* sql = "SELECT * FROM Cuidadores;";
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
            cout << "\t*Este usuario ya ah sido registrado*" << endl;
            return true;
        }
    }
    return false;
}

//nuevo menu solo para pacientes***
void MenuPacientes(const string& Name, const string& UserCode) {
    cout << "\t\t\t\t" << endl;
    cout << "\t*------\t" << endl;
    cout << "\t  Health-Grand  \t" << endl;
    cout << "\t1.Horarios\t" << endl;
    cout << "\t2.Medicamentos\t" << endl;
    cout << "\t3.Signos\t" << endl;
    cout << "\t4.Habitos\t" << endl;
    cout << "\t5.perfil\t" << endl;
    cout << "\t6.Mediciones\t" << endl;
    cout << "\t7.Vincular con Cuidador\t" << endl;
    cout << "\t8.Notificacion/Alertas\t" << endl;
    cout << "\t9.Contactos de Emergencia\t" << endl;
    cout << "\t0.Salir\t" << endl;
    cout << "\t*------\t" << endl;
    cout << "\t\t\t\t" << endl;
}
//nuevo menu solo para Cuidadores*****
void MenuCuidadores(const string& Name, const string& UserCode) {
    cout << "\t\t\t\t" << endl;
    cout << "\t*------\t" << endl;
    cout << "\t  Health-Grand  \t" << endl;
    cout << "\t1.Horarios\t" << endl;
    cout << "\t2.Medicamentos\t" << endl;
    cout << "\t3.Signos\t" << endl;
    cout << "\t4.perfil\t" << endl;
    cout << "\t5.Vincular con Pacientes\t" << endl;
    cout << "\t6.Vincular con Cuidadores\t" << endl;
    cout << "\t7.Notificacion/Alertas\t" << endl;
    cout << "\t0.Salir\t" << endl;
    cout << "\t*------\t" << endl;
    cout << "\t\t\t\t" << endl;
}

// buscar paciente***
string buscarPacientePorCodigo(const string& codigo) {
    extern sqlite3* db;
    const char* sql = "SELECT NOMBRE FROM Pacientes WHERE CODIGO = ?;";
    sqlite3_stmt* stmt;
    string nombrePaciente;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return "";
    }

    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        nombrePaciente = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);

    return nombrePaciente;
}
//buscar cuidadores **
string buscarCuidadorPorCodigo(const string& codigo) {
    extern sqlite3* db;
    const char* sql = "SELECT NOMBRE FROM Cuidadores WHERE CODIGO = ?;";
    sqlite3_stmt* stmt;
    string nombreCuidador;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return "";
    }

    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        nombreCuidador = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);

    return nombreCuidador;
}
