#include <iostream>
#include "sqlite3.h"
#include "DBRegister.h"
#include <string>
#include <cstdlib>
using namespace std;

void ShowMenu();
void RegisterMenu();
void Register(int TypeOfAccount);
void MenuLogin();
void Login(int TypeOfAccount);
bool CheckSpacesAndSize(string Data);
bool CheckSpacesAndSizeName(string Data);
string GenerateNewUserCode(string Name, string PhoneN);

int main() {
    OpenTable();
    int option;
    do {

        ShowMenu();
        cin >> option;
        cin.ignore();
        system("cls");
        switch (option)
        {
        case 1:
            RegisterMenu();
            break;
        case 2:
            MenuLogin();
            break;
        case 0:
            cout << "Saliendo";
            break;
        default:
            cout << "Opcion no permitida";
            break;
        }
    } while (option != 0);
}

//Menu de inicio
void ShowMenu() {
    cout << "\t\t\t\t" << endl;
    cout << "\t*------\t" << endl;
    cout << "\t  Health-Grand  \t" << endl;
    cout << "\t1.Registrarse\t" << endl;
    cout << "\t2.Loguearse\t" << endl;
    cout << "\t0.Salir\t" << endl;
    cout << "\t*------\t" << endl;
    cout << "\t\t\t\t" << endl;
}

//Menu de registro
void RegisterMenu() {
    int TypeOfAccount;
    do {
        cout << "\t\t\t\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\tQue tipo de cuenta va a crear\t" << endl;
        cout << "\t1.Cuenta de paciente\t" << endl;
        cout << "\t2.Cuenta de cuidador\t" << endl;
        cout << "\t0.Salir\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\t\t\t\t" << endl;
        cin >> TypeOfAccount;
        cin.ignore();
        system("cls");
        switch (TypeOfAccount)
        {
        case 1:
            Register(TypeOfAccount);
            break;
        case 2:
            Register(TypeOfAccount);
            break;
        case 0:
            break;
        default:
            cout << "Opcion no permitida";
            break;
        }
    } while (TypeOfAccount != 0);
}

//Registro
void Register(int TypeOfAccount) {
    string Name, PhoneNum, Pass, UserCode;
    bool SpacesAndSize1, SpacesAndSize2, SpacesAndSize3;
    int Option;
    do {
        cout << "\t\t\t\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\t1.Nombre completo\t" << endl;
        cout << "\t" << Name << "\t" << endl;
        cout << "\t2.Numero de telefono\t" << endl;
        cout << "\t" << PhoneNum << "\t" << endl;
        cout << "\t3.Contrasenha\t" << endl;
        cout << "\t" << Pass << "\t" << endl;
        cout << "\t4.Registrarse\t" << endl;
        cout << "\t0.Salir\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\t\t\t\t" << endl;
        cin >> Option;
        cin.ignore();
        system("cls");
        switch (Option) {
        case 1:
            cout << "\tIngrese su nombre completo\t" << endl;
            getline(cin, Name);
            system("cls");
            break;
        case 2:
            cout << "\tIngrese su numero de telefono\t" << endl;
            getline(cin, PhoneNum);
            system("cls");
            break;
        case 3:
            cout << "\tIngrese su contrasenha\t" << endl;
            getline(cin, Pass);
            system("cls");
            break;
        case 4:
            SpacesAndSize1 = CheckSpacesAndSizeName(Name);
            SpacesAndSize2 = CheckSpacesAndSize(PhoneNum);
            SpacesAndSize3 = CheckSpacesAndSize(Pass);
            if (SpacesAndSize1 == 0 && SpacesAndSize2 == 0 && SpacesAndSize3 == 0) {
                cout << "\tRegistro completado" << endl;
                UserCode = GenerateNewUserCode(Name, PhoneNum);
                switch (TypeOfAccount)
                {
                case 1:
                    addPaciente(Name, PhoneNum, Pass, UserCode);
                    break;
                case 2:
                    addCuidador(Name, PhoneNum, Pass, UserCode);
                    break;
                default:
                    break;
                }
            }
        case 0:
            break;
        default:
            cout << "\t*Opcion invalida*\t" << endl;
            break;
        }
    } while (Option != 0);
}

//Menu login
void MenuLogin() {
    string User, Pass, Data;
    int TypeOfAccount;
    bool UserExist = 1;
    do {
        cout << "\t\t\t\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\tComo Ingresar\t" << endl;
        cout << "\t1.Ingresar como paciente\t" << endl;
        cout << "\t2.Ingresar como cuidador\t" << endl;
        cout << "\t0.Salir\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\t\t\t\t" << endl;
        cin >> TypeOfAccount;
        cin.ignore();
        system("cls");
        switch (TypeOfAccount)
        {
        case 1:
            Login(TypeOfAccount);
            break;
        case 2:
            Login(TypeOfAccount);
            break;
        case 0:
            break;
        default:
            cout << "Opcion no permitida";
            break;
        }
    } while (TypeOfAccount != 0);
}

//Login
void Login(int TypeOfAccount) {
    string User, Pass, Data;
    bool UserExist;
    int Option;
    do {
        cout << "\t\t\t\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\t1.Numero de telefono\t" << endl;
        cout << "\t" << User << "\t" << endl;
        cout << "\t2.Contrasenha\t" << endl;
        cout << "\t" << Pass << "\t" << endl;
        cout << "\t3.Loguearse\t" << endl;
        cout << "\t0.Salir\t" << endl;
        cout << "\t*------\t" << endl;
        cout << "\t\t\t\t" << endl;
        cin >> Option;
        cin.ignore();
        system("cls");
        switch (Option)
        {
        case 1:
            cout << "\tIngrese su numero de telefono\t" << endl;
            getline(cin, User);
            system("cls");
            break;
        case 2:
            cout << "\tIngrese su contrasenha\t" << endl;
            getline(cin, Pass);
            system("cls");
            break;
        case 3:
            if (TypeOfAccount == 1) {
                UserExist = readPacientes(User, Pass);
            }
            else
                UserExist = readCuidadores(User, Pass);
            break;

        case 0:
            break;
        default:
            cout << "Opcion no permitida";
            break;
        }
    } while (Option != 0);
}

//Verificar espacios
bool CheckSpacesAndSize(string Data) {
    int Size;
    char Letter;
    if (Data.empty())
        return true;
    Size = Data.length();
    if (Size < 8) {
        cout << "\t*Tus datos deben tener mas de 8 digitos*";
        return true;
    }
    if (Data.at(0) == ' ' || Data.at(Size - 1) == ' ') {
        cout << "\t*No puede tener espacios ni al inicio ni al final*" << endl;
        return true;
    }
    for (int i = 0;i < Size;i++) {
        Letter = Data.at(i);
        if (Letter == ' ') {
            cout << "\t*Porfavor no utilice espacios*" << endl;
            return true;
        }
    }
    return false;
}

//verificar 1 espacio solamente
bool CheckSpacesAndSizeName(string Data) {
    int Size;
    char Letter1, Letter2;
    if (Data.empty() == 1)
        return true;
    Size = Data.length();
    if (Size < 8) {
        cout << "\t*Debe tener mas de 8 digitos*" << endl;
        return true;
    }
    if (Data.at(0) == ' ' || Data.at(Size - 1) == ' ') {
        cout << "\t*no puede tener espacios ni al inicio ni al final*" << endl;
        return true;
    }
    for (int i = 0;i < Size - 1;i++) {
        Letter1 = Data.at(i);
        Letter2 = Data.at(i + 1);
        if (Letter1 == ' ' && Letter2 == ' ') {
            cout << "\t*Porfavor solo utilize un espacio para separar los nombres*" << endl;
            return true;
        }
    }
    return false;
}

//Generar codigo de usuario
string GenerateNewUserCode(string Name, string PhoneN) {
    string UserCode;
    char Letter;
    for (int i = 0;i < 3;i++) {
        Letter = Name.at(i);
        Letter = toupper(Letter);
        UserCode += Letter;
        Letter = PhoneN.at(i);
        UserCode += Letter;
    }
    return UserCode;
}
