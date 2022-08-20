#pragma once
struct Pos
{
	double x;
	double y;
<<<<<<< HEAD
=======
	bool errorPos = false;
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

	void setPos(double inpX, double inpY)
	{
		x = inpX;
		y = inpY;
	}
<<<<<<< HEAD
=======

	void SetErrorPos(bool inp)
	{
		errorPos = inp;
	}
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};