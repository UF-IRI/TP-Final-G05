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

}; typedef struct fecha fecha;

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
	fecha ultConsulta; //DD/MM/AA
	fecha turnoSolicitado; //DD/MM/AA
	string ensurance1, ensurance2; // por las dudas
	string matriculaMed;
	int attendance; //0 for True 1 for False
	Med MedInCharge;

}; typedef struct consulta Cons;	

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
Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA, string MedA);
bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual);
bool agregarPac(Pac*& l_Pacientes, Pac paciente, int* tamactual);
bool resize(Pac*& l_Pacientes, int* tamactual, int cantidad_aumentar);//des-uso
bool Busqueda(Pac*& l_Pacientes, int* tamactual, int dni);
bool Secretaria(string NombreArchi, Pac* AuxErroneos);

Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactosA, string MedA)
{
	fstream fp;
	fstream fp2;
	fstream fp3;
	fstream fp4;
	fp.open(PacientesA, ios::in);
	fp2.open(ConsultasA, ios::in);
	fp3.open(ContactosA, ios::in);
	fp4.open(MedA, ios::in);

	if (!(fp.is_open()) )
		return nullptr;
	if (!(fp2.is_open()))
		return nullptr;
	if (!(fp3.is_open()))
		return nullptr;
	if (!(fp4.is_open()))
		return nullptr;

	Pac* l_Pacientes = new Pac[0];
	Pac aux1;
	Cont aux2;
	Cons aux3;
	Med aux4;

	string dummy;
	char coma;
	int tamactual = 0;

	//leo headers todos archivos (3) ARREGLAR- no se leen los ENDL cuando leyendo headers
	fp >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >>
		dummy >> coma >> dummy >> coma >> dummy;
	fp2 >> dummy >> coma >> dummy >> coma >> dummy;
	fp3 >> dummy >> coma >> dummy >> coma >> dummy;
	fp4 >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy; //(MED=5)

	while (fp)
	{
		fp >> aux1.DNI >> coma >> aux1.firstName >> coma >> aux1.lastName >> coma >> aux1.gender >> coma >>
			aux1.birthDate.dia >> coma >> aux1.birthDate.mes >> coma >> aux1.birthDate.anio >> coma >> aux1.VitalState;
		//recorre, lee archivo paciente y guarda en struct paciente
		while (fp2) 
		{
			fp2 >> aux2.DNI;
			if (aux1.DNI == aux2.DNI)
				fp2 >> aux2.telefono; //desarrollar las variables
			//copia la info leida del archivo en el apartado de la lista pacientes
			aux1.Cont = aux2;
			
		}
		while (fp3)
		{
			fp3 >> aux3.DNI >> coma;
			if (aux1.DNI == aux3.DNI)
			fp3>> aux3.matriculaMed; //desarrollar las variables
			aux1.Cons = aux3;
		}
		while (fp4)
		{
			fp4 >> aux4.matriculaMed >> coma;
			if (aux3.matriculaMed == aux4.matriculaMed)
				//copia la info leida del archivo en el apartado de la lista pacientes
				l_Pacientes->Cons.MedInCharge = aux4;
		}

		fp2.seekg(fp2.beg);//sale del while fp2? vuelve al principio
		fp3.seekg(fp3.beg);
		fp4.seekg(fp4.beg);

		agregarPac(l_Pacientes, aux1, &tamactual);

	}

	fp.close();
	fp2.close();
	fp3.close();
	fp4.close();

	delete[]l_Pacientes;
	return l_Pacientes;
}

bool resize(Pac*& l_Pacientes, int* tamactual, int cantidad_aumentar) {

	if (!(l_Pacientes == nullptr) || (tamactual == nullptr))
		return false;
	//no valuo que cantidadAumentar sea negativo xq fx está habilitada a eliminar elementos, resizeando

	*tamactual = *tamactual + cantidad_aumentar;
	int i = 0;
	Pac* NewListResi = new Pac[*tamactual];
	while (i < *tamactual - cantidad_aumentar) 
	{
		NewListResi[i] = l_Pacientes[i];
		i++;
	}

	delete[] l_Pacientes;
	l_Pacientes = NewListResi;

	//implementacion de AGREGAR?

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
	if ((l_Pacientes == nullptr) || tamactual == nullptr)
		return false; 

	int i = 0;
	bool check = true;

	//ya que implementar funcion AGREGAR no es posible: :(
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
		//PARA NO LLAMAR A ESCRITURA CONTINUOUSLY. generar lista previa para fallecidos archivados recuperables
		//EN VEZ DE COPIAR A LISTA ACÁ. GENERAR LISTAS DINAMICAS Y LLAMARA AGREGAR implementandola dandole uso en programa

		//pacientes fallecidos/internados --> ARCHIVO ARCHIVADOS
		if ((l_Pacientes[i].DNI == dni) && (l_Pacientes[i].VitalState == "Fallecido" || l_Pacientes[i].VitalState == "Internado"))
		{	
			listArchivados[i] = l_Pacientes[i];
			/*a fx escritura le llega por nombre tipo string(dead.csv) y la fx tiene q aplicar a q escriba en ese archivo correctly
			//(l_Pacientes.VitalState == "fallecido") || (l_Pacientes.VitalState == "Fallecido")
			// O CONTROLAR con TLOWER en ingreso de data
			check = agregarPac(listArchivados,PacAux2,tamactual); //INTENCION es que PacAux2 tenga info de l_Pacientes
			listArchivados[i] = l_Pacientes[i];
			check = EscrituraCsv("Fallecidos.csv", l_Pacientes,l_Consultas, tamactual);
			if (check == false)
				AuxErroneos[i] = l_Pacientes[i];//muevo el paciente a lista para re-visar los errores
			*/
		}
		else
			//POSIBLES recuperables n/c (recup/irrecup) - Paciente desconocida vitalidad = potencial recuperable
			if (l_Pacientes[i].DNI == dni) //ELSE ADMITE la condicion de n/c
			{	
				//ULT CONSULTA + 10 AÑOS => IRRECUPERABLE
				if (l_Pacientes[i].Cons.ultConsulta.anio + 10 < hoy->tm_year)
				{
					if (l_Pacientes[i].Cons.attendance == 1)
						listArchivados[i] = l_Pacientes[i];	
					else
						listRecup[i] = l_Pacientes[i];
					/*Necesario SOLO AL FINAL
					check = EscrituraCsv("Archivados.csv", PacAux, l_Consultas, tamactual);
					if (check == false)
						AuxErroneos[i].DNI = l_Pacientes[i].DNI;//muevo dni del paciente a lista para re-visar los errores de escritura
					*/
				}

				else //ULT CONSULTA - DE 10 AÑOS => RECUPERABLE
						/*lama a fxEscritura y escribe en archivo RECUPERABLES
						//archivo recuperables ya existe (caso contrario, lo crea)
						check = EscrituraCsv("Recuperables.csv", PacAux, l_Consultas, tamactual);
						if (check == true)
						{	//llama funcion secretaria en donde la secretaria contacta al paciente
							//funcion secretaria recibe un array de tipo Paciente y Consulta para editarlos
							check = Secretaría(PacAux, tamactual, dni);
							if (check == false)
								AuxErroneos[i].DNI = PacAux[i].DNI;//muevo dni del paciente a lista para re-visar los errores de escritura
							/*en la cual el desarrollo incluiría :
							* decisión: retorno/no retorna
							* posible fallo: paciente no responde solucion:volver a contactar en tiempo
							* posible cambio obra social. caso positivo/negativo: informa y actualiza
							* OBRA SOCIAL 2 DEBERÍA ESTAR EN BLANK
							* genera y escribe archivos pertinentes
							* envia
							* IGUALAR fxSecretaria a variable NUM
							* si num == 1, proceso exitoso, si num==0, error
							*/
						listRecup[i] = l_Pacientes[i];
			}
	}//todo en el lugar donde debe estar	

	//traspaso de listas a archivo
	check = EscrituraCsv("Archivados.csv", listArchivados, tamactual);
	if (check == false)
		AuxErroneos[i] = l_Pacientes[i];//muevo paciente a lista para re-visar los errores de escritura

	check = EscrituraCsv("Recuperables.csv", listRecup, tamactual);
	if (check == false)
		AuxErroneos[i] = l_Pacientes[i];//muevo paciente a lista para re-visar los errores de escritura
		
	check = Secretaria("Erroneos.csv", AuxErroneos);
	//ERRONEOS se envian todos juntos de una, acá hacia secretaria, SE BORRA MEMORIA LUEGO, debajo de tal instruccion
	
	delete[]AuxErroneos;
	delete[]listArchivados;
	delete[]listRecup;
	
	return true;
}

bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual)
{
	if ((l_Pacientes == nullptr) || tamactual == nullptr)
		return false; //ambas listas nulas entonces nada que hacer

	fstream OutDataFP; //maneja data de PACIENTES
	OutDataFP.open(NombreArchi, ios::app); //APP x cada vez que lo llamen, no sobreescriba

	if (!(OutDataFP.is_open()))
		return false;

	int i = 0;

	//escribe headers
	if (NombreArchi == "Archivados.csv")
	{
		OutDataFP << "ARCHIVADOS" << endl;
		OutDataFP << "DNI" << "," << "NOMBRE" << "," << "APELLIDO" << "," << "GENERO" << "," << "FECHA" << "," << "ESTADO VITAL" << "," << "OBRA SOCIAL";
		OutDataFP << "," << "DIRECCION" << "," << "EMAIL" << "," << "TELEFONO" << "," << "CELULAR";
		OutDataFP << "," << "ULTIMA CONSULTA" << "," << "TURNO SOLICITADO" << "," << "OBRA SOCIAL 1" << "," << "OBRA SOCIAL2" << "," << "PRESENTISMO" << endl;
		while (i < *tamactual)
		{
			OutDataFP << l_Pacientes[i].DNI << "," << l_Pacientes[i].firstName << "," << l_Pacientes[i].lastName << "," << l_Pacientes[i].gender << "," <<
				l_Pacientes[i].birthDate.dia << "/" << l_Pacientes[i].birthDate.mes << "/" << l_Pacientes[i].birthDate.anio << "," <<
				l_Pacientes[i].VitalState << "," << l_Pacientes[i].ensurance << endl;
			OutDataFP << "," << l_Pacientes[i].Cont.direccion << "," << l_Pacientes[i].Cont.email << "," << l_Pacientes[i].Cont.telefono << "," <<
				l_Pacientes[i].Cont.celular << "," << endl;
			OutDataFP << l_Pacientes[i].Cons.ultConsulta.dia << "/" << l_Pacientes[i].Cons.ultConsulta.mes << "/" << l_Pacientes[i].Cons.ultConsulta.anio
				<< "/" << l_Pacientes[i].Cons.turnoSolicitado.dia << "/" << l_Pacientes[i].Cons.turnoSolicitado.mes
				<< "/" << l_Pacientes[i].Cons.turnoSolicitado.anio << "," << l_Pacientes[i].Cons.ensurance1 << "," << l_Pacientes[i].Cons.ensurance2
				<< "," << l_Pacientes[i].Cons.matriculaMed << "," << l_Pacientes[i].Cons.attendance << endl;
			i++;
		}

		return true;
	}

	//ARCHIVO PARA SECRETARIA
	//requiere: DATOS MEDICO (l_Contactos.MedInCharge...) + (l_Pacientes.(nombre,apellido,telefono)
	if (NombreArchi == "Recuperables.csv")
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

bool Secretaria(string NombreArchi, Pac *AuxErroneos)
{
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

*/
	//secretaria ESCRIBE en archivo ROTULO ARCHIVADO
	return true;
}