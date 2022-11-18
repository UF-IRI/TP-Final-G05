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
		int DNI = 45296137;
		
		//Act
		Pac* result;
		result = LecturaCsv(PacientesA, ConsultasA, ContactosA, MedA, DNI);

		//Assert
		EXPECT_EQ(LecturaCsv("hola.?", "<210ds", "sidndan","sidndan", 45296137), result);
	}

	//incorrecta
	TEST(LecturaCsv, lecturaINCorrecta)
	{
		//AAA --> Arrange-Act-Assert
		//Arrange
		string PacientesA = "";
		string ConsultasA = "/0" ;
		string ContactosA;
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