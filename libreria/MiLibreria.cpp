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
	string telefono; //(+54)911-4444-5678
	string celular; //(+54)911-4444-5678
	string direccion;
	string email;

}; typedef struct contacto Cont;

struct medico
{
	string matriculaMed;
	string firstName, lastName;
	string telefono;
	string especialidad;
	int activo;

}; typedef struct medico Med;

struct consulta
{
	unsigned int DNI;
	string ultConsulta; //DD/MM/AA
	string turnoSolicitado; //DD/MM/AA
	int attendance; //0 for True 1 for False
	string matriculaMed;
	Med MedInCharge;

}; typedef struct consulta Cons;

struct paciente
{
	unsigned int DNI;
	string firstName, lastName;
	char gender; //F for female M for male
	string birthDate; //archivo pac tiene formato MM/DD/AA
	string VitalState; //n/c - internado - fallecido
	string insurance;
	contacto Cont;//variable contacto de tipo contacto
	consulta Cons; //variable consulta de tipo consulta

}; typedef struct paciente Pac;


//invocacion funciones
Pac* Lectura(fstream& fp, fstream& fp2, fstream& fp3, fstream& fp4, int &n);
bool readCont(fstream& fp, Pac*& aux, int* tamactual);
bool readCons(fstream& fp, Pac*& aux, int* tamactual);
bool readMed(fstream& fp, Pac*& aux, int* tamactual);
bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual);
bool agregarPac(Pac*& l_Pacientes, Pac paciente, int* tamactual);
bool Busqueda(Pac*& l_Pacientes, int* tamactual, int dni);
time_t convertDateToTimeT(string dato);
bool Secretaria(string NombreArchi, Pac* listRecup, int* tamactual);

Pac* Lectura(fstream& fp, fstream& fp2, fstream& fp3, fstream& fp4, int &n)
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
		getline(fp, aux1.birthDate, ',');
		//fp >> aux1.birthDate->tm_mday >> barra >> aux1.birthDate->tm_mon >> barra >> aux1.birthDate->tm_year;
		getline(fp, aux1.VitalState, ',');
		getline(fp, aux1.insurance, '\n');
		 
		//fp >> aux1.DNI >> coma >> aux1.firstName >> coma >> aux1.lastName >> coma >> aux1.gender >> coma >>
			//aux1.birthDate >> coma >> aux1.birthDate >> coma >> aux1.birthDate >> coma >> aux1.VitalState;
		//recorre con cursor leyendo archivo paciente y guarda en struct paciente
		while (fp2)
		{
			//readCont(fp2, l_Pacientes,&tamactual);
			fp2 >> aux2.DNI >> coma;
			fp2 >> aux2.telefono >> coma;
			fp2 >> aux2.celular >> coma;
			getline(fp2, aux2.direccion, ',');
			getline(fp2, aux2.email, '\n');

			if (aux1.DNI == aux2.DNI)
			{
				//cambio: antes se leia REPETIDO AGAIN el dni, lo saco xq ya no necesita leerlo denuevo. lo mismo con los de abajo
				//fp2 >> aux2.direccion >> coma >> aux2.email >> coma >> aux2.telefono >> coma >> aux2.celular;
				//copia data de contacto en variable en lista pacientes
				aux1.Cont = aux2;
				break;
			}
		}
		while (fp3)
		{
			//readCont(fp3, l_Pacientes,&tamactual);
			fp3 >> aux3.DNI >> coma;
			getline(fp3, aux3.ultConsulta, ',');//ojo que FECHA
			getline(fp3, aux3.turnoSolicitado, ',');//ojo que FECHA
			fp3 >> aux3.attendance >> coma;
			getline(fp3, aux3.matriculaMed, '\n');
			if (aux1.DNI == aux3.DNI)
			{
				//fp3 >> aux3.ultConsulta >> coma >> aux3.turnoSolicitado >> coma >> aux3.ensurance >> coma >>
				//	aux3.matriculaMed >> coma >> aux3.attendance;
				aux1.Cons = aux3;
				break;
			}
		}
		while (fp4)
		{
			//readCont(fp4, l_Pacientes,&tamactual);
			fp4 >> aux4.matriculaMed >> coma;
			getline(fp4, aux4.firstName, ',');
			getline(fp4, aux4.lastName, ',');
			fp4 >> aux4.telefono >> coma;
			getline(fp4, aux4.especialidad, ',');
			fp4 >> aux4.activo;
			if(aux3.matriculaMed == aux4.matriculaMed)
			{
				//fp4 >> aux4.firstName >> coma >> aux4.lastName >> coma >> aux4.telefono >> coma >> aux4.especialidad >> coma >> aux4.activo;
				//copia la info leida del archivo en el apartado de la lista pacientes
				aux1.Cons.MedInCharge = aux4; 
				break;
			}
		}

		fp2.seekg(fp2.beg);//sale del while fp2. vuelve al principio
		fp3.seekg(fp3.beg);
		fp4.seekg(fp4.beg);

		agregarPac(l_Pacientes, aux1, &tamactual);
	}
	//cambio: cierro archivos en main
	n = tamactual;
	return l_Pacientes;	
}

bool readCont(fstream &fp2, Pac*& aux, int *tamactual)
{
	Cont auxCont;
	string dummy;
	//lee header
	getline(fp2, dummy, ',');

	while (fp2)
	{
		fp2 >> auxCont.telefono >> dummy;
		fp2 >> auxCont.celular >> dummy;
		getline(fp2, auxCont.direccion, ',');
		getline(fp2, auxCont.email, '\n');
		//agregarPac(aux, auxCont, tamactual); //argumento del medio debe ser tipo Pac
		//condicion en while de si es igual se asigna a l_Pacientes
	}
	return true;
}
bool readCons(fstream& fp3, Pac*& aux, int* tamactual)
{
	Cons auxCons;
	string dummy;
	//lee header
	getline(fp3, dummy, ',');

	while (fp3)
	{
		fp3 >> auxCons.DNI >> dummy;
		getline(fp3, auxCons.ultConsulta, ',');//ojo que FECHA
		getline(fp3, auxCons.turnoSolicitado, ',');//ojo que FECHA
		fp3 >> auxCons.attendance >> dummy;
		getline(fp3, auxCons.matriculaMed, '\n');
		//agregarPac(aux, auxCons, tamactual); //argumento del medio debe ser tipo Pac
		//condicion en while de si es igual se asigna a l_Pacientes
	}
	return true;
}
bool readMed(fstream& fp4, Pac*& aux, int* tamactual)
{
	Med auxMed;
	string dummy;
	//lee header
	getline(fp4, dummy, ',');

	while (fp4)
	{
		getline(fp4, auxMed.matriculaMed, ',');
		fp4 >> auxMed.matriculaMed >> dummy;
		getline(fp4, auxMed.firstName, ',');//ojo que FECHA
		getline(fp4, auxMed.lastName, ',');//ojo que FECHA
		getline(fp4, auxMed.telefono, ',');
		getline(fp4, auxMed.especialidad, '\n');
		fp4 >> auxMed.activo;
		//agregarPac(aux, auxMed, tamactual); //argumento segundo debe ser tipo Pac
		//condicion en while de si es igual se asigna a l_Pacientes
	}
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

time_t convertDateToTimeT(string dato)
{
	int i = 0;
	int day, month, year;
	int cont = 0;
	string auxD{};
	string auxM{};
	string auxY{};
	string aux;
	int cont2 = 0;
	while (i < (dato.length() - 1))
	{

		while (dato[i] != '/')
		{

			if (cont == 0)
			{
				aux = dato[i];
				auxD += aux;
			}
			else if (cont == 1)
			{
				aux = dato[i];
				auxM += aux;
			}
			else
			{
				if (cont2 >= 4)
					break;
				aux = dato[i];
				auxY += aux;
				cont2++;
			}

			i++;

		}
		cont++;
		i++;
	}


	day = stoi(auxD);
	month = stoi(auxM);
	year = stoi(auxY);


	tm date{};
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;
	
	time_t finalDate = mktime(&date);
	return finalDate;
}
//le doy una string y me la devuelve en time_t

bool Busqueda(Pac*& l_Pacientes, int* tamactual, int dni)
{
	if ((l_Pacientes == nullptr) || tamactual == nullptr) //caso: || tamactual ==0 lo marca en verde warning
		return false;

	int i = 0;
	bool check = true;

	//alternativa para poder implementar Agregar y no gastar excesiva memoria
	//MD previas venian con tamaño: tamactual. Pero entrando un solo paciente: MD tamaño 1 (o 0?)
	Pac* AuxErroneos = new Pac[1];
	Pac* listArchivados = new Pac[1];
	Pac* listRecup = new Pac[1];

	//calculamos TIEMPO DE HOY 
	time_t current = time(0);
	//calculamos TIEMPO en segundos FECHA "X"
	time_t DateInSecs = 0;

	for (i = 0; i < *tamactual; i++)
	{
		//generamos listas previas para (archivados recuperables). luego traspaso a archivo

		//pacientes fallecidos/internados = ARCHIVO ARCHIVADOS
		if ((l_Pacientes[i].DNI == dni) && (l_Pacientes[i].VitalState == "Fallecido" || l_Pacientes[i].VitalState == "fallecido"  ||
			l_Pacientes[i].VitalState == "Internado" || l_Pacientes[i].VitalState == "internado"))
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
				//cambio:
				string dato = l_Pacientes[i].Cons.ultConsulta;
				DateInSecs = convertDateToTimeT(dato);
				time_t Dif = difftime(current, DateInSecs); // --> condicion: si dif > a DiezAñosEnSec entonces: entra
				//ULT CONSULTA + 10 AÑOS = IRRECUPERABLE
				//cambio:---------CAMBIAR A ADMITIR DIA MES Y AÑO-----------------	
				if (Dif > 315576000) // 315576000 == 10 años en segundos
				{
					if (l_Pacientes[i].Cons.attendance == 1)
						listArchivados[i] = l_Pacientes[i];
					else
						listRecup[i] = l_Pacientes[i];

				}
				else //ULT CONSULTA - DE 10 AÑOS => RECUPERABLE
					listRecup[i] = l_Pacientes[i];
			}
		break;
	}//TODO en el lugar donde debe estar	

	bool checkSecret = Secretaria("Recuperables.csv", listRecup, tamactual);
	/*
		if (check == false)
		Secretaria("Erroneos.csv", AuxErroneos, tamactual);
	*/
	//traspaso de listas a archivo
	check = EscrituraCsv("Archivados.csv", listArchivados, tamactual);
	
	//no es necesario ya que Secretaria no devuelve false
	/*if (check == false)
	{
		AuxErroneos = listArchivados;
		Secretaria("Erroneos.csv", AuxErroneos, tamactual); //muevo paciente a lista para re-visar los errores durante escritura
	}
	*/
	//explicacion Secretaria: a BORRAR
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

	//for(i=0;i<*tamactual;i++) PARA AMBOS if como alternativa
	/*cambio: cambiar condicion muy inaplicable inflexible
	* IMPLEMENTAR este procedimiento en otra funcion (crearla)
	 */
	//Archivo los archivados
	if (NombreArchi == "Archivados.csv")
	{
		//cambio: eliminamos bucle xq pacientes entran de a uno. y ENDL no permite que se sobreescriba
			//escribo headers
		OutDataFP << "ARCHIVADOS" << endl;
		OutDataFP << "DNI" << "," << "NOMBRE" << "," << "APELLIDO" << "," << "GENERO" << "," << "FECHA" << "," << "ESTADO VITAL" << "," << "OBRA SOCIAL" << endl;
		OutDataFP << "," << "TELEFONO" << "," << "CELULAR" << "," << "DIRECCION" << "," << "EMAIL" << endl;
		OutDataFP << "," << "ULTIMA CONSULTA" << "," << "TURNO SOLICITADO" << "," << "OBRA SOCIAL " << "," << "ASISTENCIA" << endl;
		for (i = 0; i < *tamactual; i++) //tamaactual por tam de irrecup
		{
			OutDataFP << l_Pacientes[i].DNI << "," << l_Pacientes[i].firstName << "," << l_Pacientes[i].lastName << "," << l_Pacientes[i].gender
				<< "," << l_Pacientes[i].birthDate << "," << l_Pacientes[i].VitalState << "," << l_Pacientes[i].insurance << "," << endl;
			OutDataFP /* << l_Pacientes[i].DNI << ","*/ <<  l_Pacientes[i].Cont.telefono << "," << l_Pacientes[i].Cont.celular << "," <<
				l_Pacientes[i].Cont.direccion << "," << l_Pacientes[i].Cont.email << "," << endl;
			OutDataFP << l_Pacientes[i].Cons.ultConsulta << "," << l_Pacientes[i].Cons.turnoSolicitado << "," <<
				l_Pacientes[i].Cons.matriculaMed << "," << l_Pacientes[i].Cons.attendance << endl;
		}
	}
	else if (NombreArchi == "Recuperables.csv") 
	{
		for (i = 0; i < *tamactual; i++) //tamaactual por tam de irrecup
		{	//escribe headers
			OutDataFP << "DNI(...)";
			//requiere: DATOS MEDICO (l_Contactos.MedInCharge...) + (l_Pacientes.(nombre,apellido,telefono)
			OutDataFP << l_Pacientes->firstName << "," << l_Pacientes->lastName << "," << l_Pacientes->Cont.celular << endl;
			OutDataFP << l_Pacientes[i].Cons.MedInCharge.matriculaMed << "," << l_Pacientes[i].Cons.MedInCharge.firstName << "," <<
				l_Pacientes[i].Cons.MedInCharge.lastName << "," << l_Pacientes[i].Cons.MedInCharge.especialidad << "," <<
				l_Pacientes[i].Cons.MedInCharge.activo << "," << l_Pacientes[i].Cons.MedInCharge.telefono << endl;
		}
	}
	return true;
}

bool Secretaria(string NombreArchi, Pac* listRecup, int* tamactual)
{
	if (listRecup == nullptr)
		return false;
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
	Pac* UltimatelyRecup = new Pac[*tamactual];
	Pac* UltimatelyIrrecup = new Pac[*tamactual];
	for(i=0;i < *tamactual; i++) //cambio: *tamactual por tamaño listRecup debería ser
	{
		cout << "Escriba si retorna o no: [SI]/[NO]?" << endl;
		cin >> respuesta;

		if (respuesta == "si" || respuesta == "Si" || respuesta == "SI" || respuesta == "sI")
		{
			cout << "Vuelve el paciente" << endl;
			
			cout << "Ingrese su obra social" << endl;
			cin >> checkEnssurance;
			if (listRecup[i].insurance != checkEnssurance)
			{
				listRecup[i].insurance = checkEnssurance;
			}
			UltimatelyRecup[i] = listRecup[i];
			EscrituraCsv("Recuperables.csv", UltimatelyRecup,tamactual);
		}
		else
		{
			cout << "No vuelve el paciente" << endl;
			UltimatelyIrrecup[i] = listRecup[i];
			EscrituraCsv("Archivados.csv", UltimatelyIrrecup,tamactual);
		}
	}
	return true;
}
