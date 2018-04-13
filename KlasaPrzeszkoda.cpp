#include "KlasaPrzeszkoda.h"
#include "KlasaPocisk.h"
Przeszkoda::Przeszkoda(double _x, double _y, int _wartosc)
{
	x = _x;
	y = _y;
	w = 0.5;
	h = 0.5;
	r = 1;
	g = 0;
	b = 1;
	wartosc = _wartosc;
}

Przeszkoda::Przeszkoda(double _x, double _y, double _w, double _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	r = 1;
	g = 1;
	b = 1;
}
float Przeszkoda::zwrocX()
{
	return x;
}
float Przeszkoda::zwrocY()
{
	return y;
}
float Przeszkoda::zwrocW()
{
	return w;
}
float Przeszkoda::zwrocH()
{
	return h;
}
void Przeszkoda::zmienKolor(float _r, float _g, float _b)
{
	r = _r;
	g = _g;
	b = _b;
}
int Przeszkoda::obnizWartosc()
{
	wartosc = wartosc - 1;
	return wartosc;
}
void Przeszkoda::przesun(float _x, float _y)
{
	x += _x;
	y += _y;
}
void Przeszkoda::renderString()
{
	std::string stringX;
	std::ostringstream convert;
	convert << wartosc;
	stringX = convert.str();

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(x - 0.05, y - 0.05);
	for (int n = 0; n<stringX.size(); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stringX[n]);
	}
}
void Przeszkoda::rysuj2()
{
	if (wartosc > 30)
	{
		r = 0.0, g = 1, b = 0.2;
	}
	else if (wartosc > 10 && wartosc <= 20)
	{
		r = 0.9, g = 0.7, b = 1;
	}
	else if (wartosc <= 10)
	{
		r = 0.95, g = 0.5, b = 1;
	}
	glPushMatrix();
	glTranslated(x, y, -0.001);
	glColor3d(r, g, b);
	glBegin(GL_POLYGON);
	glBegin(GL_POLYGON);
	{
		glColor3d(g, b, r);
		glVertex3d(-w / 2, h / 2, 0);
		glColor3d(r, b, b);
		glVertex3d(w / 2, h / 2, 0);
		glColor3d(r, g, b);
		glVertex3d(w / 2, -h / 2, 0);
		glColor3d(g, b, r);
		glVertex3d(-w / 2, -h / 2, 0);
	}
	glEnd();
	glPopMatrix();
}
void Przeszkoda::rysuj()
{
	glPushMatrix();
	glTranslated(x, y, 0);
	glColor3d(r, g, b);
	glBegin(GL_POLYGON);
	glBegin(GL_POLYGON);
	{

		glVertex3d(-w / 2, h / 2, 0);
		glVertex3d(w / 2, h / 2, 0);
		glVertex3d(w / 2, -h / 2, 0);
		glVertex3d(-w / 2, -h / 2, 0);
	}
	glEnd();
	glPopMatrix();
}
void Przeszkoda::losuj()
{
	x = x*((rand() % 5) - 2.5);
	y = y*((rand() % 5) - 2.5) / 2.0;
}
//bool Przeszkoda::klik(double X, double Y)
//{
//	X = (X - 500) / 500 * 3.34;
//	Y = (-Y + 400) / 400 * 2.5;
//	if (X <= x + (w / 2.0) && X >= x - (w / 2.0) && Y <= y + (h / 2.0) && Y >= y - (h / 2.0))
//	{
//		return true;
//	}
//	return false;
//}
