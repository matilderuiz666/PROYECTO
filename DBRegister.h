#ifndef DBREGISTER_H 
#define DBREGISTER_H
#include <iostream>
#include <string>
using namespace std;

int OpenTable();
void addCuidador(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo);
void addPaciente(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo);
void handleError(int rc, char* errMsg);
bool RepeatUserPacientes(const string& RegisterUser);
bool RepeatUserCuidadores(const string& RegisterUser);
bool readPacientes(const string& LoginUser, const string& LoginPass);
bool readCuidadores(const string& LoginUser, const string& LoginPass);
string buscarPacientePorCodigo(const string& codigo); //nuevo, ....cpp **
string buscarCuidadorPorCodigo(const string& codigo); //nuevo, ....cpp **
void MenuPacientes(const string& Name, const string& UserCode); //nuevo, .......cpp **
void MenuCuidadores(const string& Name, const string& UserCode); //nuevo, .....cpp *
#endif
