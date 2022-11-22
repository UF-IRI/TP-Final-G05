#include "iri.cpp"
#include <MiLibreria.cpp>
#include <iostream>
#include <MiLibreria.h>

using namespace std;

int main()
{
	//cambio: funcion LECTURA llamada en main y apertura
	
	//PATH Y RUTA DE ARCHIVO	
	string pathPac, pathCons, pathCont, pathMed;
	//..\\..\\..\\

	pathPac = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
	pathCons = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
	pathCont = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
	pathMed = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";

	fstream fp;
	fstream fp2;
	fstream fp3;
	fstream fp4;
	fp.open(pathPac, ios::in);
	fp2.open(pathCons, ios::in);
	fp3.open(pathCont, ios::in);
	fp4.open(pathMed, ios::in);

	if (!(fp.is_open()))
		return -1;
	if (!(fp2.is_open()))
		return -1;
	if (!(fp3.is_open()))
		return -1;
	if (!(fp4.is_open()))
		return -1;
	//archivo.iri base path

	Pac* check =  LecturaCsv(pathPac, pathCons, pathCont, pathMed);
	if (check != nullptr)
		cout << "true";

	//cambio: los saco dentro de la fx
	fp.close();
	fp2.close();
	fp3.close();
	fp4.close();

	return 0;	
}
