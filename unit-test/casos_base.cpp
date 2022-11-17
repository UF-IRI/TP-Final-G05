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
		bool result = true;
		result = ProtoLectura(PacientesA, ConsultasA, ContactosA, MedA, DNI);

		//Assert
		EXPECT_EQ(ProtoLectura("hola.?", "<210ds", "sidndan","sidndan", 45296137), result);
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
	TEST(agregar, correcto) 
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

	TEST(Casos_Base, Test_Caso3) {
		ASSERT_THAT(1, 1);
	}

	TEST(explicacion, suma) {
		//AAA --> Arrange-Act-Assert
		//Arrange
		int a = 4;
		int b = 4;
		int expected = 8;
		
		//Act
		int actual = suma(a, b);

		ASSERT_EQ(expected, actual);
	}
}