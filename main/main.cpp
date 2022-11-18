#include "iri.cpp"
#include <MiLibreria.cpp>
#include <iostream>
#include <ctime>

/*
bool EscrituraCsv(string NombreArchi, Pac*& l_Pacientes, int* tamactual);
bool agregarPac(Pac*& l_Pacientes, Pac paciente, int* tamactual);
bool resize(Pac*& l_Pacientes, int* tamactual, int cantidad_aumentar);
bool Secretaría(Pac*& l_Pacientes, int* tamactual, unsigned int DNI);
*/
Pac* LecturaCsv(string PacientesA, string ConsultasA, string ContactoA, string MedA, int dni);

int main()
{
	//PATH Y RUTA DE ARCHIVO	
	string pathPac, pathCons, pathCont, pathMed;
	//..\\..\\..\\

	pathPac = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
	pathCons = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
	pathCont = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
	pathMed = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
	//archivo.iri base path

	bool check =  LecturaCsv(pathPac, pathCons, pathCont, pathMed);
	if (check == true)
		cout << "true";

	return 0;	
}