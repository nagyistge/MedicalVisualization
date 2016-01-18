//A. Guayaquil
//10.2015

#include "LightRenderingEngine.h"

int main(int argc, char ** argv)
{
	gg::GraphicsApp medicalVisualization(argc, argv);
	medicalVisualization.readData("head");

	medicalVisualization.runApp();
	return EXIT_SUCCESS;
}