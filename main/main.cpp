#include "iri.cpp"
#include <MiLibreria.cpp>
#include <iostream>

using namespace std;

int main()
{
	//cambio: funcion LECTURA llamada en main y apertura

	//PATH Y RUTA DE ARCHIVO	
	string pathPac, pathCons, pathCont, pathMed;
	//..\\..\\..\\

	pathPac = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input\\IRI_Pacientes.csv";
	pathCons = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input\\IRI_Consultas.csv";
	pathCont = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input\\IRI_Contactos.csv";
	pathMed = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input\\IRI_Medicos.csv";

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
	bool checkFun = true;
	Lectura(fp, fp2, fp3, fp4);
	Pac* check = Lectura(fp, fp2, fp3, fp4);
	if (check != nullptr)
		cout << "true";

	//cambio: los saco dentro de la fx
	fp.close();
	fp2.close();
	fp3.close();
	fp4.close();

	//Necesitamos traer al main las info que se obtiene en lectura
	//checkFun = Busqueda(Pac * &l_Pacientes, int* tamactual, int dni);

	//cambio: TRAER A MAIN LISTA PACIENTES, desde funciones, por derecha
	//al traerlas, repartirla para donde deba ir: BUSQUEDA, Secretaria, Escritura(?)

	return 0;
}
