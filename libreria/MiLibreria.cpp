#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

enum obraSocial
{
	medicus = 1, OSDE, IOSFA, italiano, aleman, espanyol
};

struct fecha
{
	unsigned int dia, mes, anio;
};
struct contacto
{
	unsigned int DNI;
	string direccion;
	string email;
	string telefono; //(+54)911-4444-5678
	string celular;
};
struct consulta
{
	unsigned int DNI;
	fecha ultConsulta;
	fecha turnoSolicitado;
	string ensurance1, ensurance2; // por las dudas
	string matriculaMed;
	bool attendance;
};
struct medico
{
	string matriculaMed;
	string firstName, lastNmae;
	string telefono;
	string especialidad;
	bool activo;
};
struct paciente
{
	unsigned int DNI;
	string firstName, lastName;
	char gender; //F for female M for male
	fecha birthDate; //archivo pac tiene formato MM/DD/AA
	string VitalState; //n/c - internado - fallecido
	int ensurance;
	contacto Cont;//variable contacto de tipo contacto
	consulta Cons; //variable consulta de tipo consulta
}; typedef Pac;

//invocacion funciones
Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA);
bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, contacto* l_Contactos, consulta* l_Consultas, int* tamactual);
bool agregar(Pac*& l_Pacientes, Pac paciente, int* tamactual);
bool resize(Pac*& l_Pacientes, int* tamactual, int cantidad_aumentar);


Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA)
{
	fstream fp;
	fstream fp2;
	fstream fp3;
	fp.open(PacientesA, ios::in);
	fp2.open(ConsultasA, ios::in);
	fp3.open(ContactoA, ios::in);

	if (!((fp.is_open()) && (fp2.is_open()) && (fp3.is_open())))
		return nullptr;

	Pac l_Pacientes = new Pac[0]; //deberia ser tipo puntero, pero así, no me toma error
	Pac aux1;
	consulta aux2;
	contacto aux3;
	// nota naux;//a q equivale en nuestro cod
	string dummy;
	char coma;
	unsigned int dniaux = 0;
	int tamact = 0;

	//leo headers todos archivos (3) - no se leen los ENDL cuando leyendo headers
	fp >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >>
		dummy >> coma >> dummy >> coma >> dummy;
	fp2 >> dummy >> coma >> dummy >> coma >> dummy;
	fp3 >> dummy >> coma >> dummy >> coma >> dummy;

	while (fp)
	{
		fp >> aux1.DNI >> coma >> aux1.firstName >> coma >> aux1.lastName >> coma >> aux1.gender >> coma >>
			aux1.BirthD >> coma >> aux1.BirthM >> coma >> aux1.BirthY >> coma >> aux1.VitalState;
		//recorre, lee archivo paciente y guarda en struct paciente
		while ((dniaux == aux1.DNI) || fp2) {
			fp2 >> dniaux >> coma; //cambiar todos headers de----------------------------------------------
			if (dniaux == aux2.DNI) {
				l_Pacientes.Cons = aux2;
				break;
			}
		}
		while ((dniaux == aux3.DNI) || fp3)
		{
			fp3 >> dniaux >> coma; //cambiar todos headers de------------------------------------------------
			if (dniaux == aux3.DNI) {
				l_Pacientes.Cont = aux3;
				break;
			}
		}
		fp2.seekg(fp2.beg);//sale del while fp2? vuelve al principio
		fp3.seekg(fp3.beg);
		// Volvemos a salter el encabezado de fp2, porque posicionamos el cursor de lectura al inicio del archivo.

		agregar(l_Pacientes, aux1, &tamact);
		//srgun procedimiento l_pacientes deberia llevar una lista tipo pointer, pero al no permitirnos, lleva tipo struct
	}

	fp.close();
	fp2.close();
	fp3.close();

	return l_Pacientes;
}

bool resize(Pac*& l_Pacientes, int* tamactual, int cantidad_aumentar) {

	if (!(l_Pacientes == nullptr) || (tamactual == nullptr))
		return false;
	//no valuo que cantidadAumentar sea negativo xq fx está habilitada a eliminar elementos, resizeando

	*tamactual = *tamactual + cantidad_aumentar;
	int i = 0;
	Pac* aux = new Pac[*tamactual];
	while (i < *tamactual - cantidad_aumentar) {
		aux[i] = l_Pacientes[i];
		i++;
	}

	delete[] l_Pacientes;
	l_Pacientes = aux;

	agregar(l_Pacientes, aux, tamactual);
	return true;
}

bool agregar(Pac*& l_Pacientes, Pac paciente, int* tamactual)
{
	if (!(l_Pacientes == nullptr) || (tamactual == nullptr))
		return false;

	*tamactual = *tamactual + 1;
	int i = 0;
	Pac* aux = new Pac[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = l_Pacientes[i];
		i++;
	}
	aux[i] = paciente;

	delete[] l_Pacientes;
	l_Pacientes = aux;

	return true;
}

bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, contacto* l_Contactos, consulta* l_Consultas, int* tamactual)
{
	Pac* aux = new Pac * [*tamactual];

	fstream OutDataFP;
	OutDataFP.open(NombreArchi, ios::out);

	if (!(OutDataFP.is_open()))
		return false;
}
bool Busqueda(Pac*& l_Pacientes, contacto* l_Contactos, consulta* l_Consultas, int* tamactual, int DNI)
//N es variable entera que viene por funcion como parametro formal
{
	Pac aux;
	int num = 0; //variable para recibir éxito o defecto de funciones de archivos
	int i;
	//implementamos utilización LIBRERIA CTIME entonces transformamos variables segundos con time_t.
	unsigned int diezañosEnSeg = 0;
	unsigned int FechaHoy = 0;
	l_Pacientes = new Pac[*tamactual];//?
	for (i = 0; i < *tamactual; i++)
	{
		if (aux.VitalState == "n/c")
		{

		}
	}

}