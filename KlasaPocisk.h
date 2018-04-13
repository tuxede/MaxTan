#pragma once
#include "Header.h"

class Pocisk
{
public:
	Pocisk(double _x, double _y, double _angle, double _r);
	void Rysuj();
	void Move(double distance);
	void Rotate(double _angle);
	void Update(double dt);
	void Przyspiesz(double v);
	void MoveCirc(double _angle, float radius, float _x);
	bool czyKolizja(Przeszkoda p);
	void KolizjaPrzeszkoda(Przeszkoda p);
	void ZmienKolor(float _r, float _g, float _b);
	void Odbicie(float alfa_n);
	void UstawKat(float _angle);
	float ZwrocKat();
	float ZwrocPozycjeX();
private:
	double x, y, angle, r, v = 0, red, green, blue;

};

