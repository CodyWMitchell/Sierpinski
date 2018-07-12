#include "stdafx.h"
#include "Turtle.h"
#include <math.h>
using namespace std;

# define PI           3.14159265358979323846  /* pi */

Turtle::Turtle(HDC hdc)
{
	x = 0;
	y = 0;
	turtAngle = 0;
	penEnabled = true;
	// Sets turtle's graphics
	turtHdc = hdc;
	// Sets default drawing pen
	SelectObject(turtHdc, GetStockObject(DC_PEN));
}

Turtle::~Turtle()
{
}

void Turtle::forward(double distance) {
	double dx = cos(turtAngle*(PI*2.0)/360.0) * distance;
	double dy = sin(turtAngle*(PI*2.0) / 360.0) * distance;
	MoveToEx(turtHdc, (int) x, (int) y, (LPPOINT)NULL);
	x += dx;
	y += dy;
	if (penEnabled) {
		LineTo(turtHdc, (int)x, (int)y);
	}
}

void Turtle::goTo(double xloc, double yloc) {
	if (!penEnabled) {
		MoveToEx(turtHdc, (int)xloc, (int)yloc, (LPPOINT)NULL);
		x = xloc;
		y = yloc;
	} else {
		x = xloc;
		y = yloc;
		LineTo(turtHdc, (int)x, (int)y);
	}
}

void Turtle::right(double angle) {
	turtAngle += angle;
}

void Turtle::left(double angle) {
	turtAngle -= angle;
}

void Turtle::setColor(int r, int g, int b) {
	SetDCPenColor(turtHdc, RGB(r,g,b));
}

void Turtle::penUp() {
	penEnabled = false;
}

void Turtle::penDown() {
	penEnabled = true;
}

// Enter functions to be used with turtle here
void drawTriangle(double points[3][2], Turtle myTurtle) {
	myTurtle.penUp();
	myTurtle.goTo(points[0][0], points[0][1]);
	myTurtle.penDown();
	myTurtle.goTo(points[1][0], points[1][1]);
	myTurtle.goTo(points[2][0], points[2][1]);
	myTurtle.goTo(points[0][0], points[0][1]);
	return;
}

double getMid(double p1,double p2) {
	double result = (p1 + p2) / 2.0;
	return result;
}

void sierpinski(double points[3][2], int degree, Turtle myTurtle) {
	drawTriangle(points, myTurtle);
	if (degree > 0) {
		double mid1[2] = { getMid(points[0][0],points[1][0]),getMid(points[0][1],points[1][1]) };
		double mid2[2] = { getMid(points[1][0],points[2][0]),getMid(points[1][1],points[2][1]) };
		double mid3[2] = { getMid(points[0][0],points[2][0]),getMid(points[0][1],points[2][1]) };

		double triangle1[3][2] = { points[0][0],points[0][1],mid1[0],mid1[1],mid3[0],mid3[1] };
		double triangle2[3][2] = { points[1][0],points[1][1],mid1[0],mid1[1],mid2[0],mid2[1] };
		double triangle3[3][2] = { points[2][0],points[2][1],mid2[0],mid2[1],mid3[0],mid3[1] };

		sierpinski(triangle1, degree - 1, myTurtle);
		sierpinski(triangle2, degree - 1, myTurtle);
		sierpinski(triangle3, degree - 1, myTurtle);
	}
		
		return;
}

// Enter turtle commands here
void turtleDraw(HDC hdc) {
	Turtle t(hdc);

	t.penUp();
	t.goTo(500, 250);

	double points[3][2] = { { 200,490 },{ 500,10 },{ 800,490 } };
	sierpinski(points, 7, t);
}