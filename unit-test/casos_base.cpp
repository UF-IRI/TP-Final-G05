#include "gmock/gmock.h"
#include "MiLibreria.cpp"

namespace Casos_Base::tests
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
		
		Pac* expected = nullptr;
		//Act
		Pac* actual;
		actual = LecturaCsv(pathPac, pathCons, pathCont, pathMed);

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


		bool expected;

		bool actual = Secretaria(nombre, listaPac);

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
		bool actual= agregarPac(lista, lista2, N);

		EXPECT_EQ(expected, actual);
	}

	TEST(Busqueda, Funcionalidad)
	{
		Pac* lista = nullptr;
		int* tamaño = {};
		int dni = 33532434;
	
		bool expected = false;
		bool actual = Busqueda(lista, tamaño, dni);

		EXPECT_FALSE(expected,actual);
	}
}