#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

enum obraSocial
{
	medicus = 1, OSDE, IOSFA, italiano, aleman, espanyol
};

struct contacto
{
	unsigned int DNI;
	string direccion;
	string email;
	string telefono; //(+54)911-4444-5678
	string celular; //(+54)911-4444-5678

}; typedef struct contacto Cont;

struct medico
{
	string matriculaMed;
	string firstName, lastName;
	string telefono;
	string especialidad;
	bool activo;

}; typedef struct medico Med;

struct consulta
{
	unsigned int DNI;
	time_t ultConsulta; //DD/MM/AA
	time_t turnoSolicitado; //DD/MM/AA
	string ensurance; //cambio: ahora, una sola enssurance(), en secretaria, cambiar valor de variable, si cambio
	string matriculaMed;
	int attendance; //0 for True 1 for False
	Med MedInCharge;

}; typedef struct consulta Cons;

struct paciente
{
	unsigned int DNI;
	string firstName, lastName;
	char gender; //F for female M for male
	time_t birthDate; //archivo pac tiene formato MM/DD/AA
	string VitalState; //n/c - internado - fallecido
	contacto Cont;//variable contacto de tipo contacto
	consulta Cons; //variable consulta de tipo consulta

}; typedef struct paciente Pac;

//invocacion funciones
Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA, string MedA);
bool LeerOneByOne(string NombreArchi, fstream fp, Pac*& aux);
bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual);
bool agregarPac(Pac*& l_Pacientes, Pac paciente, int* tamactual);
bool Busqueda(Pac*& l_Pacientes, int* tamactual, int dni);
bool Secretaria(string NombreArchi, Pac* AuxErroneos);