#include "QSimpleImageViewer.h"

QSimpleImageViewer::QSimpleImageViewer(QWidget *parent)
	: QLabel(parent)
{
	setAlignment(Qt::AlignCenter);
}

void QSimpleImageViewer::setImage(QImage const & image)
{
	setPixmap(QPixmap::fromImage(image));
}