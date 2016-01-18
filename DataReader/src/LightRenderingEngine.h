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
	class ReaderRawData;

	class IOStream
	{
	public:
		void toggleDebug()
		{
			m_flushToConsole = !m_flushToConsole;
		}

		bool isConsoleDebugEnabled()
		{
			return m_flushToConsole;
		}

		virtual void flushConsole() = 0;

	private:
		bool m_flushToConsole = false;
	};

	class Matrices
	{
	public:
		glm::mat4 Projection = glm::mat4();
		glm::mat4 Modelview = glm::mat4();
	};

	class Camera
		: public IOStream
	{
	public:
		Camera()
		{
			defaultValues();
		}

		void flushConsole()
		{
			printf("Zoom : %2.4f\n", zoom);
		}

		void defaultValues()
		{
			anglex = 0.0f;
			angley = 0.0f;
			anglez = 0.0f;
			zoom = 0.0f;
		}

		float anglex;
		float angley;
		float anglez;
		float zoom;
	};

	class Window
	{
	public:
		int mousex = 0;
		int mousey = 0;
		int height = 0;
		int width = 0;
		int id = -1;
	};

	class KeyInteractor
	{
	public:
		const float alphaIncrement = 0.01f;
		float alpha = 0.0f;
	};

	class GraphicsApp
	{
	public:
		GraphicsApp(int argc, char ** argv, const std::string & windowTitle = "");
		void readData(const std::string & pathFile);
		void runApp();

		/// Instantiate one per objects
		static KeyInteractor interaction;
		static ReaderRawData reader;
		static Matrices matrices;
		static Window window;
		static Camera camera;
	};

	/// Callbacks
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void wheel(int, int, int, int);
	void reshape(int, int);
	void motion(int, int);
	void display();
	void idle();
}
