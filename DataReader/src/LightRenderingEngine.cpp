//A. Guayaquil
//10.2015

#if defined _WIN32
#define _AFXDLL
#endif

/// Small engine
#include "LightRenderingEngine.h"
#include "DataReader.h"
#include "Utilities.h"

namespace gg
{
	KeyInteractor GraphicsApp::interaction;
	ReaderRawData GraphicsApp::reader;
	Matrices GraphicsApp::matrices;
	Window GraphicsApp::window;
	Camera GraphicsApp::camera;

	GraphicsApp::GraphicsApp(int argc, char ** argv, const std::string & windowTitle)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
		
		int screenH = glutGet(GLUT_SCREEN_HEIGHT);
		int screenW = glutGet(GLUT_SCREEN_WIDTH);
		glutInitWindowPosition(screenW / 4, screenH / 4);
		glutInitWindowSize(screenW / 2, screenH / 2);
		
		GraphicsApp::window.id = glutCreateWindow(windowTitle.c_str());

		/// http://www.lighthouse3d.com/cg-topics/glut-and-freeglut/
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

		/// Extensions
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			printf("%s", "Error initializing GLEW");
		}

		glutKeyboardFunc(keyboard);
		glutMouseWheelFunc(wheel);
		glutReshapeFunc(reshape);
		glutDisplayFunc(display);
		glutMotionFunc(motion);
		glutMouseFunc(mouse);
		glutIdleFunc(idle);
	}

	void GraphicsApp::readData(const std::string & pathToFile)
	{
		/// Currently support a predefined 256 x 256 x 109
		GraphicsApp::reader.readFile(pathToFile, 256, 256, 109);
	}

	void GraphicsApp::runApp()
	{
		glutMainLoop();
	}

	void idle()
	{
		glm::mat4 modelView = glm::mat4();
		modelView = glm::translate(modelView, glm::vec3(0.0f, 0.0f, GraphicsApp::camera.zoom));
		modelView = glm::rotate(modelView, GraphicsApp::camera.anglex, glm::vec3(1.0f, 0.0f, 0.0f));
		modelView = glm::rotate(modelView, GraphicsApp::camera.angley, glm::vec3(0.0f, 1.0f, 0.0f));
		modelView = glm::rotate(modelView, GraphicsApp::camera.anglez, glm::vec3(0.0f, 0.0f, 1.0f));
		GraphicsApp::matrices.Modelview = modelView;

		glutPostRedisplay();
	}

	void reshape(int w, int h)
	{
		GraphicsApp::window.height = h;
		GraphicsApp::window.width = w;

		glViewport(0, 0, w, h);

		glutPostRedisplay();
	}

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		/// Projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1.0, +1.0, -1.0, +1.0, -1.0, 1.0);
		
		/// Modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, GraphicsApp::interaction.alpha);
		
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		
		glTranslatef(0.5f, 0.5f, 0.5f);
		//glScaled(
		//	+1.0f,
		//	-1.0f * (float)GraphicsApp::reader.m_imageWdith / (float)GraphicsApp::reader.m_imageHeight,
		//	(float)GraphicsApp::reader.m_imageWdith / (float)GraphicsApp::reader.m_imageDepth
		//	);
		glScalef(2.0f, -2.0f, 2.0f);
		glMultMatrixf(glm::value_ptr(GraphicsApp::matrices.Modelview));
		glTranslatef(-0.5f, -0.5f, -0.5f);
		
		glEnable(GL_TEXTURE_3D);
		glBindTexture(GL_TEXTURE_3D, GraphicsApp::reader.m_textureID);
		
		uint numSlices = GraphicsApp::reader.m_imageDepth;
		for (uint textIdx = 0; textIdx < numSlices; ++textIdx)
		{
			/// Index in the z direction
			float zTextureCoordinate = textIdx / float(numSlices - 1);
			float zPosition = (2.0f * zTextureCoordinate) - 1.0f;

			glBegin(GL_QUADS);
			glTexCoord3f(0.0f, 0.0f, zTextureCoordinate);
			glVertex3f(-1.0f, -1.0f, zPosition);
			
			glTexCoord3f(1.0f, 0.0f, zTextureCoordinate);
			glVertex3f(+1.0f, -1.0f, zPosition);
			
			glTexCoord3f(1.0f, 1.0f, zTextureCoordinate);
			glVertex3f(+1.0f, +1.0f, zPosition);
			
			glTexCoord3f(0.0f, 1.0f, zTextureCoordinate);
			glVertex3f(-1.0f, +1.0f, zPosition);
			glEnd();
		}
		glBindTexture(GL_TEXTURE_3D, 0);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		//glLoadMatrixf(glm::value_ptr(GraphicsApp::matrices.Modelview));

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//float size = 0.5f;
		//glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
		//glBegin(GL_QUADS);
		//glVertex3f(-size, -size, -size);
		//glVertex3f(+size, -size, -size);
		//glVertex3f(+size, +size, -size);
		//glVertex3f(-size, +size, -size);

		//glVertex3f(-size, -size, +size);
		//glVertex3f(+size, -size, +size);
		//glVertex3f(+size, +size, +size);
		//glVertex3f(-size, +size, +size);

		//glVertex3f(-size, -size, -size);
		//glVertex3f(+size, -size, -size);
		//glVertex3f(+size, -size, +size);
		//glVertex3f(-size, -size, +size);

		//glVertex3f(+size, +size, -size);
		//glVertex3f(-size, +size, -size);
		//glVertex3f(-size, +size, +size);
		//glVertex3f(+size, +size, +size);
		//glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_ALPHA_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3ub(0, 0, 0);

		std::string stringAlpha = "alpha: " + std::to_string(GraphicsApp::interaction.alpha);
		glutRenderTextf(stringAlpha, -1.0f, -1.0f);
		
		glutSwapBuffers();
	}

	void wheel(int number, int direction, int x, int y)
	{
		GraphicsApp::camera.zoom += (direction > 0) ? +0.01f : -0.01f;
	}

	void keyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
			/// Escape key
		case 27:
			glutLeaveMainLoop();
			GraphicsApp::window.id = -1;
			break;

			/// Space
		case 32:
			GraphicsApp::camera.toggleDebug();
			break;

		case '+':
			GraphicsApp::interaction.alpha += GraphicsApp::interaction.alphaIncrement;
			clamp(GraphicsApp::interaction.alpha);
			break;

		case '-':
			GraphicsApp::interaction.alpha -= GraphicsApp::interaction.alphaIncrement;
			clamp(GraphicsApp::interaction.alpha);
			break;

		case 'r':
			GraphicsApp::camera.defaultValues();
			break;

		case 'f':
			glutFullScreenToggle();
			break;

		default:
			std::cout << "Key pressed : " << key << std::endl;
			break;
		}

		if (GraphicsApp::window.id > 0)
		{
			glutPostRedisplay();
		}
	}

	void mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (button == GLUT_DOWN)
			{
				GraphicsApp::window.mousex = x;
				GraphicsApp::window.mousey = y;
			}
		}
	}

	void motion(int x, int y)
	{
		int dx = (GraphicsApp::window.mousex - x);
		int dy = (GraphicsApp::window.mousey - y);

		GraphicsApp::camera.angley += (0.1f * dx);
		GraphicsApp::camera.anglex += (0.1f * dy);

		GraphicsApp::window.mousex = x;
		GraphicsApp::window.mousey = y;
	}
}