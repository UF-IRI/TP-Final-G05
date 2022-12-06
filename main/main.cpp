#include "iri.cpp"
#include <MiLibreria.cpp>
#include <iostream>

using namespace std;

int main()
{
	//calculamos TIEMPO DE HOY otherway
	/*time_t current = time(0);
	time_t timer;
	double seconds;

	seconds= time(&timer);

	cout << seconds;
	
	return 0;
	*/

	//cambio: funcion LECTURA llamada en main y apertura

	//PATH Y RUTA DE ARCHIVO	
	string pathPac, pathCons, pathCont, pathMed;
	//..\\..\\..\\

	pathPac = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input\\Pacientes.csv";
	pathCons = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input\\Consultas.csv";
	pathCont = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input\\Contactos.csv";
	pathMed = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input\\Medicos.csv";

	fstream fp;
	fstream fp2;
	fstream fp3;
	fstream fp4;

	fp.open(pathPac, ios::in);
	fp2.open(pathCont, ios::in);
	fp3.open(pathCons, ios::in);
	fp4.open(pathMed, ios::in);

	if (!(fp.is_open()))
		return -1;
	if (!(fp2.is_open()))
		return -1;
	if (!(fp3.is_open()))
		return -1;
	if (!(fp4.is_open()))
		return -1;
	
	//traemos al main por derecha la info que se obtiene en lectura. 
	//al traerla, repartirla donde requerida : BUSQUEDA, Secretaria, Escritura(?)
	//Pac * &listaDePacientes, int* tamactual
	int n = 0;
	Pac* check = Lectura(fp, fp2, fp3, fp4, n);
	if (check != nullptr)
		cout << "true" << endl;

	//cambio: los saco dentro de la fx
	fp.close();
	fp2.close();
	fp3.close();
	fp4.close();

	//llamando a funcion BUSQUEDA con argumentos
	//check(lista con Data, N(tamaño de lista asignado en lectura) y DNI  x de pacientes.csv
	bool checkBool;
	checkBool = Busqueda(check, &n, 10242582);
	if (checkBool == true)
		cout << "Encontre al paciente";
	else
		cout << "No encontre al paciente";
	//dentro de BUSQUEDA, ocurre SECRETARIA, y así tambien, ESCRITURA, respectivamente
	return 0;
}
