#include "QSimpleImageGrabber.h"

QSimpleImageGrabber::QSimpleImageGrabber(QObject * parent)
	: QObject(parent)
{
	mCamera = new QCamera(this);
	mCamera->setCaptureMode(QCamera::CaptureStillImage);

	mCameraImageCapture = new QCameraImageCapture(mCamera, this);
	mCameraImageCapture->setBufferFormat(QVideoFrame::Format_ARGB32);
	mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

	QObject::connect(mCameraImageCapture, &QCameraImageCapture::imageCaptured, [this](int id, const QImage & preview) { emit imageCaptured(preview); });
	QObject::connect(mCameraImageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &QSimpleImageGrabber::readyForCaptureChanged);
}

void QSimpleImageGrabber::connect()
{
	mCamera->start();
	if (mCamera->state() == QCamera::ActiveState) {
		emit connected();
	}
}

void QSimpleImageGrabber::disconnect()
{
	mCamera->stop();
	emit disconnected();
}

bool QSimpleImageGrabber::isConnected() const
{
	return mCamera->state() == QCamera::ActiveState;
}

bool QSimpleImageGrabber::isReady() const
{
	QCamera::State s{ mCamera->state() };
	return mCameraImageCapture->isReadyForCapture();
}

void QSimpleImageGrabber::capture()
{
	//if (mCameraImageCapture->isReadyForCapture()) {
		mCameraImageCapture->capture();
	//}
}

