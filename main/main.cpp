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

int main()
{
	LecturaCsv("Hola.csv", "Chau.csv", "Adios.csv", 45296137);
	//Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA, int dni);
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
