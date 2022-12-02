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
	tm* birthDate; //archivo pac tiene formato MM/DD/AA
	string VitalState; //n/c - internado - fallecido
	contacto Cont;//variable contacto de tipo contacto
	consulta Cons; //variable consulta de tipo consulta

}; typedef struct paciente Pac;

//invocacion funciones
Pac* Lectura(fstream& fp, fstream& fp2, fstream& fp3, fstream& fp4, int n);
bool LeerOneByOne(fstream fp, Pac*& aux);
bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual);
bool agregarPac(Pac*& l_Pacientes, Pac paciente, int* tamactual);
bool Busqueda(Pac*& l_Pacientes, int* tamactual, int dni);
bool Secretaria(string NombreArchi, Pac* listRecup, int* tamactual);

Pac* Lectura(fstream& fp, fstream& fp2, fstream& fp3, fstream& fp4, int n)
{
	//cambio: preguntas de si los archivos se abrieron correctamente: en main

	Pac* l_Pacientes = new Pac[0];
	//eliminar listas USELESS: tipo struct. mantener only el auxPac: el omnipotente
	Pac aux1;
	Cont aux2;
	Cons aux3;
	Med aux4;

	string dummy;
	char coma;
	int tamactual = 0;
	char barra = '/';

	getline(fp, dummy, '\n');
	getline(fp2, dummy, '\n');
	getline(fp3, dummy, '\n');
	getline(fp4, dummy, '\n');

	while (fp)
	{
		//cambio: aux.fechas. cambio de struct fecha a time_t 
		fp >> aux1.DNI >> coma;
		getline(fp, aux1.firstName, ',');
		getline(fp, aux1.lastName, ',');
		fp >> aux1.gender >> coma;
		//fp >> aux1.birthDate->tm_mday >> barra >> aux1.birthDate->tm_mon >> barra >> aux1.birthDate->tm_year;
		getline(fp, aux1.VitalState, ',');

		//fp >> aux1.DNI >> coma >> aux1.firstName >> coma >> aux1.lastName >> coma >> aux1.gender >> coma >>
			//aux1.birthDate >> coma >> aux1.birthDate >> coma >> aux1.birthDate >> coma >> aux1.VitalState;
		//recorre con cursor leyendo archivo paciente y guarda en struct paciente
		while (fp2)
		{
			fp2 >> aux2.DNI;
			if (aux1.DNI == aux2.DNI)
			{
				getline(fp2, aux2.direccion, ',');
				getline(fp2, aux2.email, ',');
				fp2 >> aux2.telefono >> coma;
				fp2 >> aux2.celular >> coma;

				//cambio: antes se leia REPETIDO AGAIN el dni, lo saco xq ya no necesita leerlo denuevo. lo mismo con los de abajo
				//fp2 >> aux2.direccion >> coma >> aux2.email >> coma >> aux2.telefono >> coma >> aux2.celular;
				//copia data de contacto en variable en lista pacientes
				aux1.Cont = aux2;
			}
		}
		while (fp3)
		{
			fp3 >> aux3.DNI >> coma;
			if (aux1.DNI == aux3.DNI)
			{
				fp3 >> aux3.ultConsulta >> coma; //ojo que FECHA
				fp3 >> aux3.turnoSolicitado >> coma; //ojo que FECHA
				getline(fp3, aux3.ensurance, ',');
				fp3 >> aux3.matriculaMed >> coma;
				fp3 >> aux3.attendance >> coma;

				//fp3 >> aux3.ultConsulta >> coma >> aux3.turnoSolicitado >> coma >> aux3.ensurance >> coma >>
				//	aux3.matriculaMed >> coma >> aux3.attendance;
				aux1.Cons = aux3;
			}
		}
		while (fp4)
		{
			fp4 >> aux4.matriculaMed >> coma;
			if (aux3.matriculaMed == aux4.matriculaMed)
			{
				getline(fp4, aux4.firstName, ',');
				getline(fp4, aux4.lastName, ',');
				fp4 >> aux4.telefono >> coma;
				getline(fp4, aux4.especialidad, ',');
				fp3 >> aux4.activo >> coma;
				//fp4 >> aux4.firstName >> coma >> aux4.lastName >> coma >> aux4.telefono >> coma >> aux4.especialidad >> coma >> aux4.activo;
				//copia la info leida del archivo en el apartado de la lista pacientes
				l_Pacientes->Cons.MedInCharge = aux4;
			}
		}

		fp2.seekg(fp2.beg);//sale del while fp2? vuelve al principio
		fp3.seekg(fp3.beg);
		fp4.seekg(fp4.beg);

		bool check = true;
		agregarPac(l_Pacientes, aux1, &tamactual);
		if (check == false)
			return nullptr;
	}
	//cambio: cierro archivos en main? definir
	n = tamactual;
	return l_Pacientes;
}

bool LeerOneByOne(fstream fp, Pac*& aux)
{
	/*cambio
	Pac aux1;

	string dummy;
	char coma;

	//lee el header que le toca (ANALIZAR POSIBLES FALLOS
	fp >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy; //(8)
	fp >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy; //(Contacto=5)
	fp >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy; //(Consulta=6)
	fp >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy; //(MED=5)

	 while (fp)
	{
		//cambio: aux.fechas. cambio de struct fecha a time_t
		fp >> aux->DNI >> coma >> aux->firstName >> coma >> aux->lastName >> coma >> aux->gender >> coma >>
			aux->birthDate >> coma >> aux->birthDate >> coma >> aux->birthDate >> coma >> aux->VitalState;
		//recorre con cursor leyendo archivo paciente y guarda en struct paciente
		while (fp2)
		{
			fp2 >> aux.Cont.DNI;
			if (aux.DNI == aux2.Cont.DNI)
			{
				//cambio: antes se leia REPETIDO AGAIN el dni, lo saco xq ya no necesita leerlo denuevo. lo mismo con los de abajo
				fp2 >> aux2.direccion >> coma >> aux2.email >> coma >> aux2.telefono >> coma >> aux2.celular;
				//copia data de contacto en variable en lista pacientes
				aux1.Cont = aux2;
			}
		}
		while (fp3)
		{
			fp3 >> aux3.DNI >> coma;
			if (aux1.DNI == aux3.DNI)
			{
				fp3 >> aux3.ultConsulta >> coma >> aux3.turnoSolicitado >> coma >> aux3.ensurance >> coma >>
					aux3.matriculaMed >> coma >> aux3.attendance;
				aux1.Cons = aux3;
			}
		}
		while (fp4)
		{
			fp4 >> aux4.matriculaMed >> coma;
			if (aux3.matriculaMed == aux4.matriculaMed)
			{
				fp4 >> aux4.lastName >> coma >> aux4.telefono >> coma >> aux4.especialidad >> coma >> aux4.activo;
				//copia la info leida del archivo en el apartado de la lista pacientes
				l_Pacientes->Cons.MedInCharge = aux4;
			}
		}

		fp2.seekg(fp2.beg);//sale del while fp2? vuelve al principio
		fp3.seekg(fp3.beg);
		fp4.seekg(fp4.beg);
	*/
	return true;
}

bool agregarPac(Pac*& l_Pacientes, Pac aux1, int* tamactual)
{
	if ((l_Pacientes == nullptr) || (tamactual == nullptr))
		return false;

	*tamactual = *tamactual + 1;
	int i = 0;
	Pac* NewListPac = new Pac[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		NewListPac[i] = l_Pacientes[i];
		i++;
	}
	NewListPac[i] = aux1;

	delete[] l_Pacientes;
	l_Pacientes = NewListPac;

	return true;
}

bool Busqueda(Pac*& l_Pacientes, int* tamactual, int dni)
{
	if ((l_Pacientes == nullptr) || tamactual == nullptr || tamactual ==0)
		return false;

	int i = 0;
	bool check = true;

	//alternativa para poder implementar Agregar y no gastar excesiva memoria
	Pac* AuxErroneos = new Pac[*tamactual];
	Pac* listArchivados = new Pac[*tamactual];
	Pac* listRecup = new Pac[*tamactual];

	//implementamos LIBRERIA CTIME
	time_t mytime;
	mytime = time(NULL); //pido el dia de hoy
	struct tm* hoy = localtime(&mytime);
	int mes = hoy->tm_mon + 1;
	int dia = hoy->tm_mday;
	int anio = hoy->tm_year + 1900;
	int hora = hoy->tm_hour;
	int minuto = hoy->tm_min;
	int segundo = hoy->tm_sec;


	for (i = 0; i < *tamactual; i++)
	{
		//generamos listas previas para (archivados recuperables). luego traspaso a archivo

		//pacientes fallecidos/internados = ARCHIVO ARCHIVADOS
		if ((l_Pacientes[i].DNI == dni) && (l_Pacientes[i].VitalState == "Fallecido" || l_Pacientes[i].VitalState == "Internado"))
		{
			listArchivados[i] = l_Pacientes[i];
			/*
			*	(l_Pacientes.VitalState == "fallecido") || (l_Pacientes.VitalState == "Fallecido")
			*	 CONTROLAR con TLOWER en ingreso de data
			*/
		}
		else
			//POSIBLES recuperables n/c (recup/irrecup)
			if (l_Pacientes[i].DNI == dni) //ELSE ADMITE la condicion de n/c
			{
				//ULT CONSULTA + 10 AÑOS = IRRECUPERABLE
				//cambio:---------CAMBIAR A ADMITIR DIA MES Y AÑO-----------------	
				if (l_Pacientes[i].Cons.ultConsulta + 10 < hoy->tm_year)
				{
					if (l_Pacientes[i].Cons.attendance == 1)
						listArchivados[i] = l_Pacientes[i];
					else
						listRecup[i] = l_Pacientes[i];

				}
				else //ULT CONSULTA - DE 10 AÑOS => RECUPERABLE
					listRecup[i] = l_Pacientes[i];
			}
	}//TODO en el lugar donde debe estar	

	bool checkSecret = Secretaria("Recuperables.csv", listRecup, tamactual);
	//traspaso de listas a archivo
	check = EscrituraCsv("Archivados.csv", listArchivados, tamactual);
	if (check == false)
		AuxErroneos[i] = l_Pacientes[i];//muevo paciente a lista para re-visar los errores de escritura

	check = EscrituraCsv("Recuperables.csv", listRecup, tamactual);
	if (check == false)
		AuxErroneos[i] = l_Pacientes[i];//muevo paciente a lista para re-visar los errores de escritura

	check = Secretaria("Erroneos.csv", AuxErroneos, tamactual);
	//ERRONEOS se envian todos juntos de una, acá hacia secretaria, SE BORRA MEMORIA LUEGO, debajo de tal instruccion
	/*funcion secretaria recibe un array de tipo Paciente
	*en la cual el desarrollo incluiría :
	* decisión: retorno/no retorna
	* posible fallo: paciente no responde solucion:volver a contactar en tiempo
	* posible cambio obra social. caso positivo/negativo: informa y actualiza
	* OBRA SOCIAL 2 DEBERÍA ESTAR EN BLANK
	* genera y escribe archivos pertinentes
	* envia
	* IGUALAR fxSecretaria a variable NUM
	* si num == 1, proceso exitoso, si num==0, error
	*/

	delete[]AuxErroneos;
	delete[]listArchivados;
	delete[]listRecup;
	//cambio:desreferencia asi no dejar en uso la memoria ocupada por las dinamicas
	AuxErroneos = nullptr;
	listArchivados = nullptr;
	listRecup = nullptr;

	return true;
}

bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual)
{
	if ((l_Pacientes == nullptr) || tamactual == nullptr)
		return false; //AMBAS listas nulas: NADA que hacer

	fstream OutDataFP; //maneja data de PACIENTES
	OutDataFP.open(NombreArchi, ios::app); //APP x cada vez que lo llamen, no sobreescriba

	if (!(OutDataFP.is_open()))
		return false;

	int i = 0;

	//escribe headers
	if (NombreArchi == "Archivados.csv")
		/*cambio: cambiar condicion muy inaplicable inflexible
		* IMPLEMENTAR este procedimiento en otra funcion (crearla)
		 */
	{
		OutDataFP << "ARCHIVADOS" << endl;
		OutDataFP << "DNI" << "," << "NOMBRE" << "," << "APELLIDO" << "," << "GENERO" << "," << "FECHA" << "," << "ESTADO VITAL" << "," << "OBRA SOCIAL";
		OutDataFP << "," << "DIRECCION" << "," << "EMAIL" << "," << "TELEFONO" << "," << "CELULAR";
		OutDataFP << "," << "ULTIMA CONSULTA" << "," << "TURNO SOLICITADO" << "," << "OBRA SOCIAL 1" << "," << "OBRA SOCIAL2" << "," << "PRESENTISMO" << endl;
		while (i < *tamactual)
		{ //cambio: para leer fechas con time_t: es necesario poner que lea 3 variables o que lea una sola
			OutDataFP << l_Pacientes[i].DNI << "," << l_Pacientes[i].firstName << "," << l_Pacientes[i].lastName << "," << l_Pacientes[i].gender
				<< "," << l_Pacientes[i].birthDate << "/" << l_Pacientes[i].birthDate << "/" << l_Pacientes[i].birthDate << "," <<
				l_Pacientes[i].VitalState << "," << endl;
			OutDataFP << "," << l_Pacientes[i].Cont.direccion << "," << l_Pacientes[i].Cont.email << "," << l_Pacientes[i].Cont.telefono
				<< "," << l_Pacientes[i].Cont.celular << "," << endl;
			OutDataFP << l_Pacientes[i].Cons.ultConsulta << "/" << l_Pacientes[i].Cons.ultConsulta << "/" << l_Pacientes[i].Cons.ultConsulta
				<< "/" << l_Pacientes[i].Cons.turnoSolicitado << "/" << l_Pacientes[i].Cons.turnoSolicitado << "/" <<
				l_Pacientes[i].Cons.turnoSolicitado << "," << l_Pacientes[i].Cons.ensurance << "," << "," << l_Pacientes[i].Cons.matriculaMed
				<< "," << l_Pacientes[i].Cons.attendance << endl;
			i++;
		}

		return true;
	}

	//ARCHIVO PARA SECRETARIA
	//requiere: DATOS MEDICO (l_Contactos.MedInCharge...) + (l_Pacientes.(nombre,apellido,telefono)
	else if (NombreArchi == "Recuperables.csv")
		/*cambio: cambiar condicion muy inaplicable inflexible
		* IMPLEMENTAR este procedimiento en otra funcion (crearla)
		 */
	{
		fstream OutDataFP2;
		OutDataFP2.open(NombreArchi, ios::app); //APP x cada vez que lo llamen, no sobreescriba

		if (!(OutDataFP2.is_open()))
			return false;

		int i = 0;

		//escribe headers
		OutDataFP2 << "DNI(...)";
		while (i < *tamactual)
		{
			OutDataFP2 << l_Pacientes->firstName << "," << l_Pacientes->lastName << "," << l_Pacientes->Cont.celular << endl;
			OutDataFP2 << l_Pacientes[i].Cons.MedInCharge.matriculaMed << "," << l_Pacientes[i].Cons.MedInCharge.firstName << "," <<
				l_Pacientes[i].Cons.MedInCharge.lastName << "," << l_Pacientes[i].Cons.MedInCharge.especialidad << "," <<
				l_Pacientes[i].Cons.MedInCharge.activo << "," << l_Pacientes[i].Cons.MedInCharge.telefono << endl;
			i++;
		}

		return true;

	}

	return true;

}

bool Secretaria(string NombreArchi, Pac* listRecup, int* tamactual)
{
	/*
	if (AuxErroneos == nullptr)
		return false;
	/*
	* fstream FSecret;
		FSecret.open(NombreArchi, ios::in);

		if (!(FSecret.is_open()))
			return false;

		Pac* LeeSecret = new Pac[0];
		Cons* LeeSecret2 = new Cons[0];


		while (FSecret)
		{
			FSecret >> LeeSecret->firstName >> LeeSecret->lastName >> LeeSecret->Cont.celular;
			FSecret >> LeeSecret2->MedInCharge.matriculaMed >> LeeSecret2->MedInCharge.firstName >> LeeSecret2->MedInCharge.lastName >>
				LeeSecret2->MedInCharge.especialidad >> LeeSecret2->MedInCharge.activo >> LeeSecret2->MedInCharge.telefono;

			if(string respuesta == "si")
			cout << "retorna";
			else
			cout << "no retorna";

	//secretaria ESCRIBE en archivo ROTULO ARCHIVADO

	*/
	int i = 0;
	string respuesta;
	string checkEnssurance;
	for(i=0;i <*tamactual; i++)
	{
		cout << "Escriba si retorna o no: [SI]/[NO]?";
		cin >> respuesta;

		if (respuesta == "si" || respuesta == "Si" || respuesta == "SI" || respuesta == "sI")
		{
			cout << "Vuelve el paciente";
			
			cout << "Ingrese su obra social";
			cin >> checkEnssurance;
			if (listRecup[i].Cons.ensurance != checkEnssurance)
			{
				listRecup[i].Cons.ensurance = checkEnssurance;
			}
			EscrituraCsv("Recuperables.csv", listRecup,tamactual);
		}
		else
		{
			//cout << "No vuelve el paciente";
			EscrituraCsv("Archivados.csv", listRecup,tamactual);
		}
	}
	return true;
}
