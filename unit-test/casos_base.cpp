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
		
		int DNI = 45296137;

		//Act
		bool result = true;
		result = ProtoLectura(PacientesA, ConsultasA, ContactosA, DNI);

		//Assert
		EXPECT_EQ(ProtoLectura("hola.?", "<210ds´+", "sidndan", 45296137), result);
	}

	TEST(LecturaCsv, lecturaINCorrecta)
	{
		//AAA --> Arrange-Act-Assert
		//Arrange
		string PacientesA = "";
		string ConsultasA = "/0" ;
		string ContactosA;
	}
	TEST(Casos_Base, Test_Caso2) {
		ASSERT_THAT(1, 1);
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