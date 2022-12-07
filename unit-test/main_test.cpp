#include "gmock/gmock.h"
#include "MiLibreria.cpp"

namespace foobar::tests
{
	TEST(Lectura, lectura1)
	{
		//AAA --> Arrange-Act-Assert
		//Arrange
		string pathPac, pathCons, pathCont, pathMed;

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
			return;
		if (!(fp2.is_open()))
			return;
		if (!(fp3.is_open()))
			return;
		if (!(fp4.is_open()))
			return;

		int n = 0;
		Pac* expected = nullptr;
		//Act
		Pac* actual=new Pac[10];
		actual = Lectura(fp,fp2, fp3, fp4,n);

		//Assert puntuales
		int dni = actual[0].DNI;
		ASSERT_EQ(dni, 10242582);

		int dni2 = actual[1].DNI;
		ASSERT_NE(dni2, 10242584);

		string prueba = actual[0].firstName;
		ASSERT_EQ(prueba, " Cersty ");
		
		int dniGT1 = actual[1].DNI;
		int dniGT2 = actual[0].DNI;
		EXPECT_GT(dniGT1, dniGT2);

		//assertion resultado funcion
		EXPECT_NE(expected, actual);
	}

	//incorrecta
	TEST(Secretaria, listaNoNula)
	{
		//AAA --> Arrange-Act-Assert
		//Arrange
		int x = 10;
		int i = 0;
		int* listaInt = new int[x];
		Pac* listaPac = new Pac[x];
		for (i = 0; i < x; i++)
		{
			listaInt[i] = i;
			listaPac->DNI = listaInt[i];
		}
		//10 dni ingresados

		string nombre = "ABRIR.csv";

		int n = 0;
		bool actual = false;
		actual = Secretaria(nombre, listaPac,&n);

		EXPECT_TRUE(actual);

		delete[]listaInt;
		delete[]listaPac;
	}

	//AGREGAR
	TEST(agregarPac, nulo)
	{
		//AAA --> Arrange-Act-Assert
		//Arrange

		Pac* lista = nullptr;
		Pac lista2 = {};
		int* N = 0;

		//Act
		bool expected = false; //alguna lista es nula= correcto
		bool actual = agregarPac(lista, lista2, N);

		EXPECT_EQ(expected, actual);
	}

	TEST(Busqueda, nulo)
	{
		Pac* lista = nullptr;
		int* tamaño = {};
		int dni = 33532434;

		bool expected = true;
		bool actual = Busqueda(lista, tamaño, dni);

		//cambio: arreglo de aserciones
		EXPECT_NE(expected, actual);
		EXPECT_FALSE(actual);
	}
	TEST(Busqueda, NoNulo)
	{
		string pathPac, pathCons, pathCont, pathMed;

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
			return;
		if (!(fp2.is_open()))
			return;
		if (!(fp3.is_open()))
			return;
		if (!(fp4.is_open()))
			return;

		int n = 0;
		Pac* actual = new Pac[10];
		actual = Lectura(fp, fp2, fp3, fp4, n);
		
		bool expected = true;
		bool actualBus = Busqueda(actual, &n, 10242582);

		ASSERT_THAT(expected, actual);

		string dato = actual[0].Cons.ultConsulta;
		string dato2= actual[1].Cons.ultConsulta;

		EXPECT_NE(dato, dato2);
	}

}
