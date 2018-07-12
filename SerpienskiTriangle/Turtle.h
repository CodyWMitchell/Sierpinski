// A Simple Turtle Class using HDC
// Cody Mitchell codymitchell1997@gmail.com July, 2018
// Github: CodyWMitchell
// This work is licensed under a Creative Commons Attribution 3.0 United States License.

#pragma once
class Turtle
{
public:
	private:
	double x;
	double y;
	double turtAngle;
	bool penEnabled;
	HDC turtHdc;

	public:
	Turtle(HDC hdc);
	~Turtle();
	void forward(double distance);
	void goTo(double xloc, double yloc);
	void right(double angle);
	void left(double angle);
	void setColor(int r, int g, int b);
	void penUp();
	void penDown();
};