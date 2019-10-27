#pragma once

#include <QtWidgets/QMainWindow>
#include <QFutureWatcher>
#include <QIntValidator>
#include "ui_RaytracingEngineGUI.h"
#include "Scene/Scene.h"


class RaytracingEngineGUI : public QMainWindow
{
	Q_OBJECT
public:
	RaytracingEngineGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::RaytracingEngineGUIClass ui;
	unique_ptr<Scene> m_scene;
	unique_ptr<QFutureWatcher<void>> m_watcher;
	QVector<int> m_pixelsToRender;
	QIntValidator m_validator{1, 9999, this};

private slots:
	void onStartButtonClicked();
	void onBrowseButtonClicked();
	void onRenderFinished();

signals:
	void operate(Scene& scene);
};
