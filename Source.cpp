#include "Header.h"
#include "KlasaPocisk.h"
#include "KlasaPrzeszkoda.h"
#include "Funkcje.h"



int main(int argc, char *argv[])
{
	ustawObiekty();
	
	std::cout << "Witaj w grze MaxTAnXDDD" << std::endl;
	std::cout << "'a' i 'd' zmieniaje kierunek wystrzeliwanie pociskow, 'w' umozliwa ich wystrzelenie " << std::endl;
	std::cout << "zmieniac kierunek pociskow mozna takze po ich wystrzeleniu" << std::endl;
	std::cout << "wcisnij enter" << std::endl;
	std::getchar();


	glutInit(&argc, argv);
	InitGLUTScene("MaxTanXDDD");
	SetCallbackFunctions();
	glutMainLoop();
	return 0;
}