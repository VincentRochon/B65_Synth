#include "..\..\..\..\B65_Synth\QtSignGuesser\SignGuesser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SignGuesser w;
	w.show();
	return a.exec();
}
