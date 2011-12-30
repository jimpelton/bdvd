/*
 * PlotViewerMain.cpp
 *
 *  Created on: Dec 27, 2011
 *      Author: jim
 *
 *      purpose: holds business logic for displaying the output of a PlotViewer.
 */

#include "PlotViewerMain.h"

PlotViewerMain::PlotViewerMain(DataReaderFormat drf) {
	m_drf = drf;
	Setup();
}

PlotViewerMain::~PlotViewerMain() {
}

int PlotViewerMain::Setup()
{
	m_plotViewer = new PlotViewer(m_drf, 640, 480);
	this->SetupUi(this, m_drf);

	if (m_plotViewer->Setup()){
		fprintf(stdout, "Setup failed!\n");
		return 1;
	}

	m_plotViewer->GetView()->SetInteractor(plotVtkWidget->GetInteractor());
	plotVtkWidget->SetRenderWindow(m_plotViewer->GetView()->GetRenderWindow());

	return 0;
}

void PlotViewerMain::InitializeRenderer()
{
	m_plotViewer->InitializeRenderer();
}
