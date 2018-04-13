#pragma once
#include "Header.h"


void mouse(int button, int state, int x, int y);
void RenderString(GLdouble x, GLdouble y, const std::string &string);
void wyswietlPoziom();
void display();
void InitGLUTScene(const char* window_name);
void resize(int width, int height);
void idle();
void generujPociski();
void losujPrzeszkody(int t);
void przesunPrzeszkody(int i);
void Gamelogic(int t);
void keyboard(unsigned char key, int x, int y);
void SetCallbackFunctions();
void ustawObiekty();
