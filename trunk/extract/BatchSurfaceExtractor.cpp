/*
 * SurfaceExtractor.cpp
 *
 *  Created on: Dec 19, 2011
 *      Author: jim
 */


#include "BatchSurfaceExtractor.h"

#include <SurfaceUtil.h>

#include <vtkPolyDataReader.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QString>
#include <QRegExp>

std::string strFileName;

BatchSurfaceExtractor::BatchSurfaceExtractor(DataReaderFormat drf,
		int *isoVals, int numIsoVals, char *outpath,
		bool noextract)
: m_drf(drf)
, m_isoVals(isoVals)
, m_numIsoVals(numIsoVals)
, m_outpath(outpath)
, m_noextract(noextract)
{


	if (m_noextract)
	{

		strFileName = outpath;
		DoCalcs();
	}
	else
	{
		DoExtract();
	}
}

BatchSurfaceExtractor::~BatchSurfaceExtractor()
{}

void BatchSurfaceExtractor::makeReader()
{
	reader = vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFilePrefix(m_drf.filePrefix);

	reader->SetAllow8BitBMP(1);

	reader->SetFileNameSliceOffset(0);
	reader->SetDataExtent( 0, m_drf.dimX,
			0, m_drf.dimY,
			m_drf.imgRngStart,
			m_drf.imgRngEnd);

	reader->SetDataOrigin(0.,0.,0.);
	reader->SetDataScalarTypeToUnsignedChar();
	reader->SetDataByteOrderToBigEndian();
}

void BatchSurfaceExtractor::DoExtract()
{
	makeReader();
	SurfaceUtil::BatchExtractAndSaveIsoSurface(
			reader->GetOutputPort(),
			m_isoVals, m_numIsoVals,
			m_drf.fileName, m_outpath );
}

//TODO: change to pure stl and move to vv.
void BatchSurfaceExtractor::DoCalcs()
{
	ofstream outfile(strFileName.c_str());

	vtkSmartPointer<vtkPolyDataReader> pdr =
			vtkSmartPointer<vtkPolyDataReader>::New();

	QDir dir;
	dir.setPath(QString(m_drf.filePrefix));
	if (!dir.exists())
	{
		fprintf(stdout, "Yeah...%s doesn't exist...", m_drf.filePrefix);
	}

	dir.setFilter(QDir::Files);
	dir.setSorting(QDir::Name);

	QFileInfoList flist = dir.entryInfoList();

	QRegExp regex("^iso([0-9]+)");
	for (int i=0; i<flist.size(); ++i)
	{
		QFileInfo finfo = flist[i];
		QString name = finfo.fileName();

		fprintf(stdout, "   %d: Processing file: %s\n", i, name.toAscii().data());

		int in = regex.indexIn(name);
		if (in != 0){
			fprintf(stdout, "%s is missing required \"isoXXX\" at front, skipping.\n", name.toStdString().c_str());
			continue;
		}

		bool res=false;
		QString strIso = regex.cap(1);
		int nIso = strIso.toInt(&res, 10);
		if (!res){
			fprintf(stdout, "Couldn't extract iso value %s from file name %s, skipping.\n",
					strIso.toStdString().c_str(),
					name.toStdString().c_str());
			continue;
		}
		if (finfo.suffix().compare("vtk") != 0) {
			fprintf(stdout, "%s does not have a .vtk suffix, skipping.\n", name.toStdString().c_str());
			continue;
		}

		pdr->SetFileName(finfo.absoluteFilePath().toAscii().data());
		pdr->Update();
		if (!pdr->IsFilePolyData()){
			fprintf(stdout, "%s is not a polydata file, skipping.\n", name.toAscii().data());
			continue;
		}


		//double avgEdgeLength = SurfaceUtil::TriangleAvgEdgeLength(pdr->GetOutput());
		double connectedComps = SurfaceUtil::NumOfConnectedComponents(pdr->GetOutput());
		outfile << nIso << ":" << connectedComps << "\n";
		outfile.flush();
	}

	outfile.close();


}
