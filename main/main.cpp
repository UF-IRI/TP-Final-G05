#include "iri.cpp"
#include <MiLibreria.cpp>
#include <iostream>
#include <ctime>

int tiempo();
/*
bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual);
bool agregar(Pac*& l_Pacientes, Pac paciente, int* tamactual);
bool resize(Pac*& l_Pacientes, int* tamactual, int cantidad_aumentar);
bool Secretaría(Pac*& l_Pacientes, int* tamactual, unsigned int DNI);
*/
Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA, string MedA, int dni);

int main()
{
	time_t mytime;
	mytime = time(NULL); //pido el dia de hoy
	struct tm* hoy = localtime(&mytime);
	int mes = hoy->tm_mon + 1;
	int dia = hoy->tm_mday;
	int anio = hoy->tm_year + 1900;
	int hora = hoy->tm_hour;
	int minuto = hoy->tm_min;
	int segundo = hoy->tm_sec;
	cout << "Estamos en el" << dia << "/" << mes << "/" << anio << endl << "son" << hora << "/" << minuto << "/" << segundo << endl;

	string pathPac, pathCons, pathCont, pathMed;
	
	//PATH Y RUTA DE ARCHIVO	
	pathPac = "..\\..\\..\\C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files";
	pathCons = "C\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files";
	pathCont = "C\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files";
	pathMed = "C\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files";
	//archivo.iri base path
	Pac *check =  LecturaCsv(pathPac, pathCons, pathCont, pathMed, 45296137);
	if (check == nullptr)
		cout << "false";
		return false;

	return 0;	
}

int tiempo()
{
	time_t now;
	time_t timer;
	struct tm TenyAgo = { 0 };
	double seconds;
	time(&now);

	TenyAgo.tm_hour = 0;   TenyAgo.tm_min = 0; TenyAgo.tm_sec = 0;
	TenyAgo.tm_year = TenyAgo.tm_year - 10; TenyAgo.tm_mon = 0; TenyAgo.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(now, mktime(&TenyAgo));
	return 0;
}
