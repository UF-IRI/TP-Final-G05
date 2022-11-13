#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

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
}; typedef struct paciente Pac;

//invocacion funciones
Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA);
bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes,int* tamactual);
bool agregar(Pac*& l_Pacientes, Pac paciente, int* tamactual);
bool resize(Pac*& l_Pacientes, int* tamactual, int cantidad_aumentar);
bool Secretar�a(Pac*&l_Pacientes, int *tamactual,unsigned int DNI);

Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA, int DNI)
{
	fstream fp;
	fstream fp2;
	fstream fp3;
	fp.open(PacientesA, ios::in);
	fp2.open(ConsultasA, ios::in);
	fp3.open(ContactoA, ios::in);

	if (!((fp.is_open()) && (fp2.is_open()) && (fp3.is_open())))
		return nullptr;

	Pac *l_Pacientes = new Pac[0]; //deberia ser tipo puntero, pero as�, no me toma error
	Pac aux1;
	consulta aux2;
	contacto aux3;
	// nota naux;//a q equivale en nuestro cod
	string dummy;
	char coma;
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
		while ((DNI == aux1.DNI) || fp2) {
			fp2 >> DNI >> coma; //cambiar todos headers de----------------------------------------------
			if (DNI == aux2.DNI) {
				l_Pacientes->Cons = aux2;
				break; //no necesario? condicion while
			}
		}
		while ((DNI == aux3.DNI) || fp3)
		{
			fp3 >> DNI >> coma; //cambiar todos headers de------------------------------------------------
			if (dniaux == aux3.DNI) {
				l_Pacientes->Cont = aux3;
				break; //no necesario? condicion while
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
	//no valuo que cantidadAumentar sea negativo xq fx est� habilitada a eliminar elementos, resizeando

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

bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual)	
{
	if (l_Pacientes == nullptr)
		return false;
	Pac* aux = new Pac * [*tamactual];

	fstream OutDataFP;
	OutDataFP.open(NombreArchi, ios::out);

	if (!(OutDataFP.is_open()))
		return false;

}

bool Secretar�a(Pac*& PacAux, int* tamactual, unsigned int DNI)
{

}

bool Busqueda(Pac*& l_Pacientes, contacto* l_Contactos, consulta* l_Consultas, int* tamactual, int DNI)
//N es variable entera que viene por funcion como parametro formal
{ 
	int num = 0; //variable para recibir �xito o defecto de funciones de archivos
	int i;

	bool check = true;
	Pac AuxErroneos; //ENVEZ = implementar funcion AGREGAR

	//implementamos utilizaci�n LIBRERIA CTIME entonces transformamos variables segundos con time_t.
	time_t now;
	time_t timer;
	struct tm TenyAgo = { 0 };
	double seconds;
	time(&now);

	TenyAgo.tm_hour = 0;   TenyAgo.tm_min = 0; TenyAgo.tm_sec = 0;
	TenyAgo.tm_year = TenyAgo.tm_year - 10; TenyAgo.tm_mon = 0; TenyAgo.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(now, mktime(&TenyAgo));
	
	Pac *PacAux = new Pac[*tamactual];//?
	PacAux = l_Pacientes;
	for (i = 0; i < *tamactual; i++)
	{
		//pacientes fallecidos
		if ((PacAux[i].VitalState == "Fallecido") && (PacAux[i].DNI == DNI))
		{//mismo proceso pero en diferente archivo: "Dead.csv"
			//a fx escritura le llega por nombre tipo string (dead.csv) y la fx tiene q aplicar a q escriba en ese archivo correctly
			//(l_Pacientes.VitalState == "fallecido") || (l_Pacientes.VitalState == "Fallecido")
			// O CONTROLAR con TLOWER en ingreso de data
			check = fxEscrituraCsv("Fallecidos.csv", PacAux, int* tamactual);
			if (check == false)
				AuxErroneos[i] = PacAux[i];//muevo el paciente a lista para re-visar los errores
		}
		else
			if ((PacAux[i].VitalState == "Internado") && (PacAux[i].DNI == DNI))
			{//(l_Pacientes.VitalState == "internado") || (l_Pacientes.VitalState == "Internado")
				// O CONTROLAR con TLOWER en ingreso de data
				check = fxEscrituraCsv("Archivados.csv", PacAux, int* tamactual);
				if (check == false)
					AuxErroneos[i].DNI = PacAux.DNI[i];//muevo dni del paciente a lista para re-visar los errores de escritura
			}
			else
				//posibles recuperables
				if (PacAux[i].VitalState == "n/c" && (PacAux[i].DNI == DNI)) //Paciente desconocida vitalidad = potrencial recuperable
				{
					//NO TIENE SENTIDO ALGUNO MANEJAR DATA, si NO SABES SI VIVEN
					if ((PacAux[i].Cons + 10a�osEnSeg < now) && (PacAux[i].DNI == DNI))
					{
						check = fxEscrituraCsv("Archivados.csv", PacAux, int* tamactual);
						if (check == false)
						else
							AuxErroneos[i].DNI = PacAux.DNI[i];//muevo dni del paciente a lista para re-visar los errores de escritura
					}
				}
				else
					if (PacAux[i].attendance == true)
					{		//lama a fxEscritura y escribe en archivo RECUPERABLES
							//archivo recuperables ya existe (caso contrario, lo crea)
						check = fxEscrituraCsv("Recuperables.csv", PacAux, int* tamactual);
						if (check == true)
						{	//llama funcion secretaria en donde la secretaria contacta al paciente 
							//funcion secretaria recibe un array de tipo Paciente y Consulta para editarlos
							check = Secretar�a(PacAux, tamactual, DNI);
								if (check == false)
								AuxErroneos[i].DNI = PacAux.DNI[i];//muevo dni del paciente a lista para re-visar los errores de escritura
							/*en la cual el desarrollo incluir�a :
							* decisi�n: retorno/no retorna
							* posible fallo: paciente no responde solucion:volver a contactar en tiempo
							* posible cambio obra social. caso positivo/negativo: informa y actualiza
							* OBRA SOCIAL 2 DEBER�A ESTAR EN BLANK
							* genera y escribe archivos pertinentes
							* envia
							* IGUALAR fxSecretaria a variable NUM
							* si num == 1, proceso exitoso, si num==0, error
							*/
						}
						else
							AuxErroneos[i].DNI = PacAux.DNI[i];//muevo dni del paciente a lista para re-visar los errores de escritura
					}
	}
}
