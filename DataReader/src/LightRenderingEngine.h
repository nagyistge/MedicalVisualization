//A. Guayaquil
//10.2015

#pragma once

/// Math, awesome templated linear algebra and geometry
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

/// C++ interface
#include <iostream>
#include <string>

namespace gg
{
	class Matrices
	{
	public:
		glm::mat4 Projection = glm::mat4();
		glm::mat4 Modelview = glm::mat4();
	};

	class Camera
	{
	public:
		float zoom = -1.0f;
	};

	class GraphicsApp
	{
	public:
		GraphicsApp(int argc, char ** argv, const std::string & windowTitle = "");
		void run();

		/// Instantiate one per objects
		static Matrices matrices;
		static Camera camera;
	};

	/// Callbacks
	void keyboard(unsigned char, int, int);
	void wheel(int, int, int, int);
	void reshape(int, int);
	void display();
	void idle();
}
