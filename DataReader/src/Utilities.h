//A. Guayaquil
//10.2015

#pragma once

/// Beautiful rendering
#include <GL/freeglut.h>
#include <string>

namespace gg
{
	template<typename T>
	void clamp(T & number, T a = T(0.0), T b = T(1.0))
	{
		number = (number > b) ? b : number;
		number = (number < a) ? a : number;
	}

	void glutRenderTextf(const std::string & text, float x, float y)
	{
		glRasterPos2f(x, y);
		for (char character : text)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, character);
		}
	}
}