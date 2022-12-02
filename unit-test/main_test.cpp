#include "gmock/gmock.h"
#include "MiLibreria.cpp"

namespace foobar::tests
{
	TEST(LecturaCsv, lecturaCorrecta)
	{
		//cambio: supuestamente dice que lo que en realidad retorna la funcion no es lo que esperamos: osea funciona bien
		//AAA --> Arrange-Act-Assert
		//Arrange
		string pathPac, pathCons, pathCont, pathMed;

		pathPac = "C:\\Users\\54232\\Desktop\\Mateo\\2022\\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
		pathCons = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
		pathCont = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";
		pathMed = "C:\\Users\\54232\\Desktop\\Mateo\\2022\BMI\\IRI\\TRABAJO FINAL\\data_files\\input";

		fstream fp;
		fstream fp2;
		fstream fp3;
		fstream fp4;
		int n = 0;

		Pac* expected = nullptr;
		//Act
		Pac* actual;
		actual = Lectura(fp,fp2, fp3, fp4,n);

		//Assert
		EXPECT_NE(expected, actual);
	}

	//incorrecta
	TEST(Secretaria, listas)
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
		bool expected;

		bool actual = Secretaria(nombre, listaPac,&n);

		EXPECT_TRUE(expected, actual);

		delete[]listaInt;
		delete[]listaPac;
	}

	//AGREGAR
	TEST(agregarPac, correcto)
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

	TEST(Busqueda, Funcionalidad)
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

}
