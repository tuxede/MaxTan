#include "Funkcje.h"
#include "Header.h"
#include "KlasaPrzeszkoda.h"
#include "KlasaPocisk.h"

bool gameOn = 0;
int czas = 0;
int ile = 1;


std::vector<Pocisk> pociski;
std::vector<Przeszkoda> sciany;
std::vector<Przeszkoda> przeszkody;
std::vector<Pocisk> kierunek;



void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{

	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}

}
void RenderString(GLdouble x, GLdouble y, const std::string &string)
{
	glColor3d(1.0, 1.0, 1.0);
	glRasterPos2d(x, y);
	for (int n = 0; n < string.size(); ++n)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);
	}
}
void wyswietlPoziom()
{
	std::string stringX;
	std::ostringstream convert;
	convert << ile - 1;
	stringX = "poziom: " + convert.str();
	RenderString(-1.4, 2.35, stringX);
}
void display()
{

	// clear the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	{
		//wyswietlanie poziomu
		wyswietlPoziom();
		//rysowanie strzalki kierunku
		if (gameOn == 0)
		{
			for (int i = 0; i < kierunek.size(); i++)
			{
				kierunek[i].Rysuj();
			}
		}
		//rysowanie scian
		for (int i = 4; i >= 0; i--)
		{
			sciany[i].rysuj();
		}
		//rysowanie przeszkod
		if (!przeszkody.empty())
		{
			for (int i = 0; i < przeszkody.size(); i++)
			{
				przeszkody[i].renderString();
				przeszkody[i].rysuj2();
			}
		}
		//rysowanie pociskow
		if (!pociski.empty())
		{
			for (int j = 0; j < pociski.size(); j++)
			{
				pociski[j].Rysuj();
			}
		}
	}
	glPopMatrix();

	glutSwapBuffers();
}
void InitGLUTScene(const char* window_name)
{
	glutInitWindowSize(700, 933);
	glutInitWindowPosition(40, 40);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow(window_name);

	// set white as the clear colour
	glClearColor(0, 0, 0, 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}
void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void idle()
{
	glutPostRedisplay();
}
void generujPociski()
{

	srand(time(0));
	float randomX = ((rand() % 100) - 50) / 60.0;
	for (int i = 0; i < ile; i++)
	{
		Pocisk p(randomX, -2.2, M_PI / 2, 0.03);
		//p.ZmienKolor(1, 1, 0);
		pociski.push_back(p);
	}
	float x = pociski[0].ZwrocPozycjeX();
	for (int i = 0; i < kierunek.size(); i++)
	{
		kierunek[i].UstawKat(M_PI / 2);
		kierunek[i].MoveCirc(0, 0.7 + (0.5*i), x);
	}
}
void losujPrzeszkody(int t)
{

	srand(time(0));

	for (float i = -1.6; i < 1.6; i += 0.533)
	{
		int random = rand() % 100;
		if (ile < 5)
		{
			if (random > 46)
			{
				Przeszkoda p1(i, 2.1, ile);
				przeszkody.push_back(p1);
			}
		}
		else
		{
			if (random > 46)
			{
				Przeszkoda p1(i, 2.1, ile + random / 40);
				przeszkody.push_back(p1);
			}

		}
	}
}
void przesunPrzeszkody(int i)
{
	int kroki = 30;
	if (i < kroki)
	{
		for (int j = 0; j < przeszkody.size(); j++)
		{
			przeszkody[j].przesun(0, -0.533 / kroki);
		}
		i++;
		glutTimerFunc(20, przesunPrzeszkody, i);
	}
}
void Gamelogic(int t)
{
	if (pociski.empty())
	{

		losujPrzeszkody(0);
		gameOn = 0;
		czas = 0;
		generujPociski();
		przesunPrzeszkody(0);
		ile++;

	}
	if (!pociski.empty())
	{
		//aktualizacja pozycji
		for (int j = 0; j < pociski.size(); j++)
		{
			pociski[j].Update(1);
		}
		//kolizje ze scianami
		for (std::vector<Pocisk>::iterator it = pociski.begin(); it != pociski.end(); it++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (it->czyKolizja(sciany[i]))
				{
					if (i == 0)//sciana gorna
						it->Odbicie(-M_PI / 2);
					else if (i == 1)//sciana dolna
					{
						it = pociski.erase(it);
						czas--;
						break;
					}
					else if (i == 2)
					{	//sciana prawa
						it->Odbicie(M_PI);
					}
					else if (i == 3)
					{//sciana lewa
						it->Odbicie(0);
					}
				}
			}
			if (pociski.empty() || it == pociski.end())
				break;
		}
		//kolizje z przeszkodami
		for (std::vector<Pocisk>::iterator it = pociski.begin(); it != pociski.end(); it++)
		{
			for (std::vector<Przeszkoda>::iterator itPrzeszkoda = przeszkody.begin(); itPrzeszkoda != przeszkody.end(); itPrzeszkoda++)
			{
				if (it->czyKolizja(*itPrzeszkoda))
				{
					it->KolizjaPrzeszkoda(*itPrzeszkoda);
					if (itPrzeszkoda->obnizWartosc() == 0)
					{
						itPrzeszkoda = przeszkody.erase(itPrzeszkoda);
					}
				}
				if (przeszkody.empty() || itPrzeszkoda == przeszkody.end())
					break;
			}
			if (pociski.empty() || it == pociski.end())
				break;
		}
		glutTimerFunc(8, Gamelogic, NULL);
		//sprawdzenie czy nie przegrales
		for (std::vector<Przeszkoda>::iterator itPrzeszkoda = przeszkody.begin(); itPrzeszkoda != przeszkody.end(); itPrzeszkoda++)
		{
			//jesli przegrales
			if (itPrzeszkoda->zwrocY() < -1.65)
			{
				gameOn = 0;
				przeszkody.clear();
				ile = 2;
				glutTimerFunc(300, losujPrzeszkody, 0);
				przesunPrzeszkody(0);

			}
			if (przeszkody.empty() || itPrzeszkoda == przeszkody.end())
				break;
		}
	}

}
void Wystrzel(int t)
{
	if (gameOn == 1) {
		if (czas < pociski.size())
		{
			pociski[czas].Przyspiesz(0.035);
			czas++;
			glutTimerFunc(100, Wystrzel, NULL);
		}

	}
}

void keyboard(unsigned char key, int x, int y)
{
	std::cout << key << std::endl;
	if (key == 'a'/*&&gameOn == 0*/)
	{
		for (int j = 0; j < pociski.size(); j++)
		{
			pociski[j].Rotate(1 * (M_PI / 180.0));
		}
		for (int i = 0; i < kierunek.size(); i++)
		{
			kierunek[i].MoveCirc(-1 * (M_PI / 180.0), 0.7 + (float)(0.5*i), pociski[0].ZwrocPozycjeX());
		}

	}
	if (key == 'w'&&gameOn == 0)
	{
		glutTimerFunc(100, Wystrzel, NULL);
		gameOn = 1;

	}
	if (key == 'd'/*&&gameOn==0*/)
	{
		for (int j = 0; j < pociski.size(); j++)
		{
			pociski[j].Rotate(-1 * (M_PI / 180.0));
		}
		for (int i = 0; i < kierunek.size(); i++)
		{
			kierunek[i].MoveCirc(1 * (M_PI / 180.0), 0.7 + (float)(0.5*i), pociski[0].ZwrocPozycjeX());

		}

	}
	if (key == ' ')
	{
		for (int j = 0; j < pociski.size(); j++)
		{
			pociski[j].Przyspiesz(0.05);
		}
	}
}

void SetCallbackFunctions()
{
	glutTimerFunc(10, Gamelogic, NULL);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
}

void ustawObiekty()
{
	Przeszkoda ScianaG(0, 2.2, 4, 0.03);//scianaG pelni tylko funkcje ozdobna
	Przeszkoda ScianaG2(0, 2.33, 4, 0.30);
	ScianaG2.zmienKolor(0, 0, 0);
	Przeszkoda ScianaD(0, -2.6, 4, 0.3);
	Przeszkoda ScianaP(2.05, 0, 0.3, 7);
	Przeszkoda ScianaL(-2.05, 0, 0.3, 7);
	sciany.push_back(ScianaG2); // gora - 0
	sciany.push_back(ScianaD); //dol -1
	sciany.push_back(ScianaP); //prawa -2
	sciany.push_back(ScianaL); //lewa - 3
	sciany.push_back(ScianaG);
	for (int i = 0; i < 4; i++)//strza³ka kierunku
	{
		Pocisk k(0, -1.5 + (i*0.5), M_PI / 2, 0.02);
		k.ZmienKolor(0.7, 0.0, 0.7);
		kierunek.push_back(k);
	}
}

