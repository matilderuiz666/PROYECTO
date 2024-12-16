#ifndef ALERTAS_H
#define ALERTAS_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void recMedicamentoPaciente() {
    int opcion;
    cout << "¿Ya tomaste tu medicamento?" << endl;
    do {
        cout << "1. Si, ya lo he tomado" << endl;
        cout << "0. Salir" << endl;
        cin >> opcion;
        system("cls");
        switch (opcion) {
        case 1:
            cout << "Notificacion enviada al cuidador..." << endl;
            cout << "    " << endl;
            break;
        case 0:
            cout << "Saliendo del menu de medicamentos..." << endl;
            cout << "    " << endl;
            break;

        default:
            cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
            cout << "    " << endl;
        }
    } while (opcion != 0 && opcion != 1);

}

void recMedicamentoCuidador() {
    cout << "**El paciente ha tomado el medicamento Paracetamol, 500 mg." << endl;
    cout << "    " << endl;
}

void recConsultaPaciente() {
    cout << "**Tiene consulta con Dr. Lopez a las 10:00 AM." << endl;
    cout << "    " << endl;
}

void recConsultaCuidador() {
    cout << "**El paciente tiene consulta con Dr. Lopez a las 10:00 AM." << endl;
    cout << "    " << endl;
}

void alertaPaciente() {
    string confirmacion, nombreConfirmacion, edadConfirmacion;
    int confirma;
    cout << "*SE HA DETECTADO UNA IRREGULARIDAD EN signos vitales*" << endl;
    cout << "Se encuentra usted consciente? (si/no): ";
    cin >> confirmacion;
    cin.ignore();
    system("cls");

    if (confirmacion == "si") {
        cout << "Escriba su nombre por favor: ";
        cin >> nombreConfirmacion;
        cout << "Escriba su edad por favor: ";
        cin >> edadConfirmacion;
        cin.ignore();
        system("cls");
        cout << "Gracias por la confirmacion, desea comunicarse con su cuidador?" << endl;
        do {
            cout << "1. Si" << endl;
            cout << "2. No" << endl;
            cin >> confirma;
            system("cls");
            switch (confirma) {
            case 1:
                cout << "Contactando cuidador..." << endl;
                break;
            case 2:
                cout << "Saliendo del menu de alertas..." << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
            }
        } while (confirma != 1 && confirma != 2);
    }
    else {
        cout << "Contactando cuidador automaticamente..." << endl;
    }

}

void alertaCuidador() {
    int opcion;
    cout << "*Paciente: SE HA DETECTADO UNA IRREGULARIDAD EN signos vitales*" << endl;
    cout << "Informar al medico?" << endl;
    do {
        cout << "1. Si" << endl;
        cout << "2. No" << endl;
        cin >> opcion;
        system("cls");
        switch (opcion) {
        case 1:
            cout << "Informando al medico..." << endl;
            break;

        case 2:
            cout << "Saliendo del menu de alertas..." << endl;
            break;

        default:
            cout << "Opcion no valida. Por favor, seleccione una opción valida.\n";
        }
    } while (opcion != 2);
}


void alertasPa() {
    recMedicamentoPaciente();
    recConsultaPaciente();
    alertaPaciente();
}
void alertasCui() {
    recMedicamentoCuidador();
    recConsultaCuidador();
    alertaCuidador();
}
#endif
