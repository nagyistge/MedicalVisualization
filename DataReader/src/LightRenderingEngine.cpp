//A. Guayaquil
//10.2015

/// Beautiful rendering
#include <GL/freeglut.h>

/// Small engine
#include "LightRenderingEngine.h"

namespace gg
{
	Matrices GraphicsApp::matrices;
	Camera GraphicsApp::camera;

	GraphicsApp::GraphicsApp(int argc, char ** argv, const std::string & windowTitle)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutCreateWindow(windowTitle.c_str());

		glutKeyboardFunc(keyboard);
		glutMouseWheelFunc(wheel);
		glutReshapeFunc(reshape);
		glutDisplayFunc(display);
		glutIdleFunc(idle);
	}

	void GraphicsApp::run()
	{
		glutMainLoop();
	}

	void idle()
	{
		GraphicsApp::matrices.Modelview = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, GraphicsApp::camera.zoom));
		glutPostRedisplay();
	}

	void reshape(int w, int h)
	{
		glViewport(0, 0, w, h);

		/// Projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		GraphicsApp::matrices.Projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
		glLoadMatrixf(glm::value_ptr(GraphicsApp::matrices.Projection));

		glutPostRedisplay();
	}

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		/// Modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLoadMatrixf(glm::value_ptr(GraphicsApp::matrices.Modelview));

		/// Data
		glBegin(GL_TRIANGLES);
		glColor3ub(255, 0, 0);
		glVertex3fv(glm::value_ptr(glm::vec3(+1.0f, -1.0f, 0.0f)));

		glColor3ub(0, 255, 0);
		glVertex3fv(glm::value_ptr(glm::vec3(-1.0f, -1.0f, 0.0f)));

		glColor3ub(0, 0, 255);
		glVertex3fv(glm::value_ptr(glm::vec3(+0.0f, +1.0f, 0.0f)));

		glEnd();

		glutSwapBuffers();
	}

	void wheel(int number, int direction, int x, int y)
	{
		GraphicsApp::camera.zoom += (direction > 0) ? +0.1f : -0.1f;
	}

	void keyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
			/// Escape key, ASCII 
			/// http://www.asciitable.com/
		case 27:
			/// Handle properly later ... 
			std::exit(EXIT_SUCCESS);
			break;

		default:
			std::cout << "Key pressed : " << key << std::endl;
			break;
		}

		glutPostRedisplay();
	}
}