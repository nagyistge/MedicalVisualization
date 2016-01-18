//A. Guayaquil
//10.2015

#pragma once
#include "Definitions.h"
#include "Histogram.h"

/// Note (alejandro) -> Deprecate the library ...
#if defined _WIN32
#include <afxwin.h>
#else
#include <teem/nrrd.h>
#endif

/// 3D textures
#include <GL/glew.h>

/// C++ interface
#include <iostream>
#include <string>

/// Possibly will derive different tyoe of data
/// to read such as: nrrd, vtk, obj, stl ... 
/// Note (alejandro) -> Expand description
namespace gg
{
	class DataReader
	{
	public:
		DataReader() {}
		virtual ~DataReader() {}

		virtual void readFile(const std::string & fileName, const int width, const int height, const int depth) = 0;
		virtual void printDataInformation() = 0;

	protected:
		bool m_loaded = false;
		const char * m_fileName;
	};

	/// Implementation for nrrd data
	/// http://teem.sourceforge.net/nrrd/
	class ReaderRawData : public DataReader
	{
	public:

		/// Not robust but for testing the rendering of a texture :)
		/// Old OpenGL, later to use new OpenGL
		inline void readStackImages(const std::string & fileName, const int width, const int height, const int count)
		{
			CFile file;
			if (!file.Open(fileName.c_str(), CFile::modeRead))
			{
				return;
			}
			
			int imageDataSize = (width * height);
			m_imageHeight = height;
			m_imageWdith = width;
			m_imageDepth = count;

			/// Create buffer indices
			m_textureIDs = new int[count];
			glGenTextures(m_imageDepth, (GLuint *)m_textureIDs);

			/// Hold luminance buffer
			char * data = new char[imageDataSize];
			
			/// Read each frame each frame
			for (int idx = 0; idx < m_imageDepth; ++idx)
			{
				file.Read(data, imageDataSize);

				/// Set properties of the texture
				glBindTexture(GL_TEXTURE_2D, m_textureIDs[idx]);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				/// Convert data to RGBA
				char * rgba = new char[imageDataSize * 4];
				for (int idxImage = 0; idxImage < imageDataSize; ++idxImage)
				{
					int padding = (idxImage * 4);
					char intensity = data[idxImage];

					rgba[padding + 0] = intensity;
					rgba[padding + 1] = intensity;
					rgba[padding + 2] = intensity;
					rgba[padding + 3] = intensity;
				}

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imageWdith, m_imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)rgba);
				glBindTexture(GL_TEXTURE_2D, 0);

				delete[] rgba;
			}

			delete[] data;
		}

		/// Usage of 3D textures
		inline void readFile(const std::string & fileName, const int width, const int height, const int depth)
		{
#if defined _WIN32
			CFile file;
			if (!file.Open(fileName.c_str(), CFile::modeRead))
			{
				return;
			}

			/// Assign values of the image
			int volumeDataSize = (width * height * depth);
			m_imageHeight = height;
			m_imageWdith = width;
			m_imageDepth = depth;

			/// Hold the luminance, actual data
			char * dataBuffer = new char[volumeDataSize];

			/// Hold RGBA values
			char * rgbaBuffer = new char[volumeDataSize * 4];

			/// Read the file
			file.Read(dataBuffer, volumeDataSize);

			/// Assign to the RGBA buffer the luminance
			for (int n = 0; n < volumeDataSize; n++)
			{
				int padding = (n * 4);
				rgbaBuffer[padding + 0] = dataBuffer[n];
				rgbaBuffer[padding + 1] = dataBuffer[n];
				rgbaBuffer[padding + 2] = dataBuffer[n];
				rgbaBuffer[padding + 3] = dataBuffer[n];
			}

			glGenTextures(1, (GLuint *)&m_textureID);
			glBindTexture(GL_TEXTURE_3D, m_textureID);

			/// Check again with the OpenGL documentation about the parameters
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, m_imageWdith, m_imageHeight, m_imageDepth, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)rgbaBuffer);
			glBindTexture(GL_TEXTURE_3D, 0);

			delete[] dataBuffer;
			delete[] rgbaBuffer;
#else
			/// Not robust, not working
			m_fileName = fileName.c_str();

			if (nrrdLoad(m_nrrdReader, m_fileName, NULL))
			{
				std::cout << "some error, do handling" << std::endl;
				return;
			}

			m_loaded = true;
#endif
		}

		inline void printDataInformation()
		{
#if defined _WIN32
#else
			if (m_loaded)
			{
				printf("%s is a %d-dimensional nrrd of type %d\n", m_fileName, m_nrrdReader->dim, m_nrrdReader->type);
			}
#endif
		}

	public:
		int m_imageHeight = 0;	// x
		int m_imageWdith = 0;	// y
		int m_imageDepth = 0;	// z

		int * m_textureIDs = nullptr;
		int m_textureID = -1;
	};
}