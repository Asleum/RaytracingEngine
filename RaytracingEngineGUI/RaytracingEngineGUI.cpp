#include "RaytracingEngineGUI.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrent>


RaytracingEngineGUI::RaytracingEngineGUI(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
	ui.resolutionXBox->setValidator(&m_validator);
	ui.resolutionYBox->setValidator(&m_validator);
	ui.imageLabel->setVisible(false);
	resize(sizeHint());
}

void RaytracingEngineGUI::onStartButtonClicked() 
{
	ui.startButton->setEnabled(false);
	try {
		m_scene = make_unique<Scene>(ui.sceneFileBox->text().toStdString());
		int resolutionX = ui.resolutionXBox->text().toInt();
		int resolutionY = ui.resolutionYBox->text().toInt();

		m_scene->prepareRendering(resolutionX, resolutionY);
		m_pixelsToRender.clear();
		for (int i = 0; i != resolutionX * resolutionY; ++i)
			m_pixelsToRender.push_back(i);
		auto task = [this](const int& i) { m_scene->renderPixel(i); };

		m_watcher = make_unique<QFutureWatcher<void>>();
		connect(m_watcher.get(), SIGNAL(finished()), this, SLOT(onRenderFinished()));
		connect(m_watcher.get(), SIGNAL(progressRangeChanged(int, int)), ui.progressBar, SLOT(setRange(int, int)));
		connect(m_watcher.get(), SIGNAL(progressValueChanged(int)), ui.progressBar, SLOT(setValue(int)));
		m_watcher->setFuture(QtConcurrent::map(m_pixelsToRender, task));
	}
	catch (runtime_error e)
	{
		QMessageBox::critical(this, "Error", e.what());
		ui.startButton->setEnabled(true);
	}
}

void RaytracingEngineGUI::onBrowseButtonClicked()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open scene file", "", "Scene files (*.xml)");
	ui.sceneFileBox->setText(filename);
}

void RaytracingEngineGUI::onRenderFinished()
{ 
	assert(m_scene);
	QString outFilename = QString::fromStdString(m_scene->finalizeRendering());
	ui.startButton->setEnabled(true);
	ui.progressBar->setValue(0);
	QMessageBox::information(this, "Done", "Successfully generated scene image " + outFilename);
	QImage image{ outFilename };
	ui.imageLabel->setVisible(true);
	ui.imageLabel->setPixmap(QPixmap::fromImage(image));
}
