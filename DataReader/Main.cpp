//A. Guayaquil
//10.2015

/// Note (alejandro) -> Deprecate the library ...
#include <teem/nrrd.h>

/// Beautiful visualization
#include <GL/freeglut.h>

/// Math, awesome templated linear algebra and geometry
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <cstdlib>
#include <string>

///// Possibly will derive different tyoe of data
///// to read such as: nrrd, vtk, obj, stl ... 
///// Note (alejandro) -> Expand description
//class DataReader
//{
//public:
//	DataReader() {}
//	virtual ~DataReader() {}
//
//	virtual void readFile(const std::string & fileName) = 0;
//	virtual void printDataInformation() = 0;
//
//protected:
//	bool m_loaded = false;
//	const char * m_fileName;
//};
//
///// Implementation for nrrd data
///// http://teem.sourceforge.net/nrrd/
//class ReaderNRRD : public DataReader
//{
//public:
//	ReaderNRRD()
//	{
//		m_nrrdReader = nrrdNew();
//	}
//
//	~ReaderNRRD()
//	{
//		nrrdNuke(m_nrrdReader);
//	}
//
//	inline void readFile(const std::string & fileName)
//	{
//		m_fileName = fileName.c_str();
//
//		if (nrrdLoad(m_nrrdReader, m_fileName, NULL))
//		{
//			std::cout << "some error, do handling" << std::endl;
//			return;
//		}
//
//		m_loaded = true;
//	}
//
//	inline void printDataInformation()
//	{
//		if (m_loaded)
//		{
//			printf("%s is a %d-dimensional nrrd of type %d\n", m_fileName, m_nrrdReader->dim, m_nrrdReader->type);
//		}
//	}
//
//private:
//	Nrrd * m_nrrdReader;
//};

glm::mat4 Projection = glm::mat4();
glm::mat4 Modelview = glm::mat4();
float zoom = -1.0f;

void idle()
{
	Modelview = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, zoom));		
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	/// Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	Projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
	glLoadMatrixf(glm::value_ptr(Projection));

	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	/// Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLoadMatrixf(glm::value_ptr(Modelview));

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
	zoom += (direction > 0) ? +0.1f : -0.1f;
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

int main(int argc, char ** argv)
{
	std::string file = "hi.png";

	//ReaderNRRD reader;
	//reader.readFile(file);
	//reader.printDataInformation();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("");

	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseWheelFunc(wheel);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return EXIT_SUCCESS;
}