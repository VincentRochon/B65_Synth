#pragma once

#include <QCamera>
#include <QCameraImageCapture>

class QSimpleImageGrabber : public QObject
{
	Q_OBJECT

public:
	QSimpleImageGrabber(QObject * parent = nullptr);
	~QSimpleImageGrabber() = default;

	bool isConnected() const;
	bool isReady() const;

public slots:
	void connect();
	void disconnect();
	void capture();

signals:
	void connected();
	void disconnected();
	void imageCaptured(QImage const & image);
	void readyForCaptureChanged(bool ready);

private:
	QCamera * mCamera;
	QCameraImageCapture * mCameraImageCapture;
};
