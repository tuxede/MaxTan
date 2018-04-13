#pragma once
#include "Header.h"

class Przeszkoda {
public:
	Przeszkoda(double _x, double _y, int _wartosc);
	Przeszkoda(double _x, double _y, double _w, double _h);
	void renderString();
	void rysuj();
	void rysuj2();
	void losuj();
	float zwrocX();
	float zwrocY();
	float zwrocW();
	float zwrocH();
	void zmienKolor(float _r, float _g, float _b);
	void przesun(float _x, float _y);
	int obnizWartosc();
	//bool klik(double X, double Y);
private:
	double x, y, w, h, r, g, b;
	int wartosc;
};


