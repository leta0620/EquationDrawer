#pragma once
struct Pos
{
	double x;
	double y;
	bool errorPos = false;

	void setPos(double inpX, double inpY)
	{
		x = inpX;
		y = inpY;
	}

	void SetErrorPos(bool inp)
	{
		errorPos = inp;
	}
};