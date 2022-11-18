#include "gmock/gmock.h"
#include "MiLibreria.cpp"

namespace Casos_Base::tests
{
	TEST(LecturaCsv, lecturaCorrecta) { //FUNCIONA TEST +
		//AAA --> Arrange-Act-Assert
		//Arrange
		//generar string randoms para nombre?
		string PacientesA = "hola.?";
		string ConsultasA = "<210ds´+";
		string ContactosA = "sidndan";
		string MedA = "sidndan";
		
		//Act
		Pac* result;
		result = LecturaCsv(PacientesA, ConsultasA, ContactosA, MedA);

		//Assert
		EXPECT_EQ(LecturaCsv("hola.?", "<210ds", "sidndan","sidndan"), result);
	}

	//incorrecta
	TEST(Secretaria, listas)
	{
		//AAA --> Arrange-Act-Assert
		//Arrange
		int x = 10;
		int* n = &x;
		int i = 0;
		int* lista = new int[x];
		Pac* listaPac = new Pac[*n];
		for (i = 0; i < *n; i++)
			lista[i] = i;
		listaPac->DNI = lista[i];

		string nombre = "ABRIR.csv";

		//10 dni ingresadis

		bool expected;

		bool actual = Secretaria(nombre, listaPac);

		EXPECT_TRUE(expected, actual);
		
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