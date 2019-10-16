#pragma once

#include <QLabel>

class QSimpleImageViewer : public QLabel
{
	Q_OBJECT

public:
	QSimpleImageViewer(QWidget * parent = nullptr);
	~QSimpleImageViewer() = default;

public slots:
	void setImage(QImage const & image);
};
