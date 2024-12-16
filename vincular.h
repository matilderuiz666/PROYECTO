#ifndef VINCULAR_H
#define VINCULAR_H

#include <iostream>
#include "DbRegister.h"

using namespace std;

inline void Perfil(string Name, string UserCode);
void vincularPaciente();
inline void vincularCuidadorParaPaciente(string Name, string UserCode);

inline void Perfil(string Name, string UserCode) {
    int option;
    do {
        cout << "\t\t\t\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\t" << Name << endl;
        cout << "\tCodigo:" << UserCode << endl;
        cout << "\t1.Cerrar Sesion\t" << endl;
        cout << "\t0.Salir\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\t\t\t\t" << endl;
        cin >> option;
        cin.ignore();
        system("cls");
        switch (option) {
        case 1:
            cout << "Regresando al menu principal..." << endl;
            break;
        case 0:
            break;
        default:
            cout << "\tOpcion no permitida";
            break;
        }
    } while (option != 0);
}



// Función principal para vincular al paciente
void vincularPaciente() {
    string codigoPaciente;
    cout << "Ingrese el codigo del paciente: ";
    cin >> codigoPaciente;
    system("cls");
    string nombrePaciente = buscarPacientePorCodigo(codigoPaciente);

    if (!nombrePaciente.empty()) {
        cout << "Exitosamente vinculado a " << nombrePaciente << "." << endl;
    }
    else {
        cout << "No se encontro un paciente con el código ingresado." << endl;
    }

}

void vincularCuidadorParaPaciente(string Name, string UserCode) {
    int option;
    do {
        cout << "\t*------\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\t" << Name << endl;
        cout << "\t 1.Descarga app Healt-Grand, Cuidadores\t" << endl;
        cout << "\t 2.Ingresa el codigo de un paciente\t" << endl;
        cout << "\tTu Codigo de Paciente es:" << UserCode << endl;
        cout << "\t0.Salir\t" << endl;
        cout << "\t*------\t" << endl;
        cin >> option;
        cin.ignore();
        system("cls");
        switch (option) {
        case 0:
            break;
        default:
            cout << "\tOpcion no permitida";
            break;
        }
    } while (option != 0);
}

#endif
