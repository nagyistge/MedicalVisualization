//A. Guayaquil
//10.2015

#pragma once

/// Note (alejandro) -> Deprecate the library ...
#include <teem/nrrd.h>

/// C++ interface
#include <iostream>
#include <string>

/// Possibly will derive different tyoe of data
/// to read such as: nrrd, vtk, obj, stl ... 
/// Note (alejandro) -> Expand description
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