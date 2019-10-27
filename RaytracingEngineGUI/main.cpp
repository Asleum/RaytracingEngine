#include "RaytracingEngineGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RaytracingEngineGUI w;
	w.show();
	return a.exec();
}
