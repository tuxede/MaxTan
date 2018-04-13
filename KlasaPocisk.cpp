#include "KlasaPrzeszkoda.h"
#include "KlasaPocisk.h"
Pocisk::Pocisk(double _x, double _y, double _angle, double _r)
{
	x = _x;
	y = _y;
	angle = _angle;
	r = _r;
	red = 1;
	green = 1;
	blue = 1;
}
void Pocisk::UstawKat(float _angle)
{
	angle = _angle;
}
float Pocisk::ZwrocKat()
{
	return angle;
}
float Pocisk::ZwrocPozycjeX()
{
	return x;
}
void Pocisk::ZmienKolor(float _r, float _g, float _b)
{
	red = _r;
	green = _g;
	blue = _b;
}
void Pocisk::Move(double distance)
{
	x = x + distance*cos(angle);
	y = y + distance*sin(angle);
}
void Pocisk::MoveCirc(double _angle, float radius, float _x)
{
	angle = angle + _angle;
	x = (sin(angle - M_PI / 2)*radius) + _x;
	y = (cos(angle - M_PI / 2)*radius) - 2.2;
}

void Pocisk::Rotate(double _angle)
{
	angle = angle + _angle;
}
void Pocisk::Update(double dt)
{

	x = x + v*dt*cos(angle);
	y = y + v*dt*sin(angle);
}
void Pocisk::Przyspiesz(double _v)
{
	v = v + _v;
}

void Pocisk::Rysuj()
{
	//glPushMatrix();
	//glTranslated(x, y, 0);
	//glRotated(angle*(180 / M_PI), 0.0, 0.0, 1.0);
	//glColor3d(red, green, blue);
	//glBegin(GL_TRIANGLE_FAN);
	//{

	//	for (int i = 0; i <= 360; i++)
	//	{
	//		// 180 - pi
	//		// i - degInRad

	//		double degInRad = i*M_PI / 180;
	//		glVertex2f(cos(degInRad)*r, sin(degInRad)*r);
	//	}
	//}
	//glEnd();
	//glPopMatrix();
	glPushMatrix();
	{
		glTranslated(x, y, 0.0);
		glRotated(angle*(180 / M_PI), 0.0, 0.0, 1.0);

		glColor3d(red, green, blue);

		glBegin(GL_TRIANGLE_FAN);
		{

			for (int i = 0; i <= 360; i++)
			{
				// 180 - pi
				// i - degInRad

				double degInRad = i*M_PI / 180;
				glVertex2f(cos(degInRad)*r, sin(degInRad)*r);
			}
		}
		glEnd();

	}
	glPopMatrix();
}

bool Pocisk::czyKolizja(Przeszkoda p)
{
	if (x - r > (p.zwrocX() + p.zwrocW() / 2) || x + r < (p.zwrocX() - p.zwrocW() / 2)
		|| y - r >(p.zwrocY() + p.zwrocH() / 2) || y + r < (p.zwrocY() - p.zwrocH() / 2)) {
		return false;
	}
	else
		return true;


}
void Pocisk::Odbicie(float alfa_n)
{

	if (abs(alfa_n - angle) > M_PI / 2)
	{
		angle = alfa_n - (M_PI + angle - alfa_n);
	}
}
void Pocisk::KolizjaPrzeszkoda(Przeszkoda p)
{

	float dx = x - p.zwrocX();
	float dy = y - p.zwrocY();


	if (dy / dx > -1 && dy / dx < 1 && dx >= 0)//uderzenie w sciane lewa
	{
		this->Odbicie(0);
	}
	else if (dy / dx > -1 && dy / dx < 1 && dx < 0)//uderzenie w sciane prawa
	{
		this->Odbicie(M_PI);
	}
	else if (dy / dx < -1 && dy / dx>1 || dy >= 0)//uderzenie w sciane gorna
	{
		this->Odbicie(M_PI / 2);
	}
	else if (dy / dx < -1 && dy / dx>1 || dy < 0)//uderzenie w sciane dolna
	{
		this->Odbicie(-M_PI / 2);
	}


	//if (i == 0)//sciana gorna
	//	it->Odbicie(-M_PI / 2);
	//else if (i == 1)//sciana dolna
	//{
	//	it = pociski.erase(it);
	//	czas--;
	//	break;
	//}
	//else if (i == 2)
	//{	//sciana prawa
	//	it->Odbicie(M_PI);
	//}
	//else if (i == 3)
	//{//sciana lewa
	//	it->Odbicie(0);
	//}

}
