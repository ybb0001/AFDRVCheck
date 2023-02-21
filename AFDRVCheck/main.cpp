#include "AFDRVCheck.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AFDRVCheck w;
	w.show();
	return a.exec();
}
