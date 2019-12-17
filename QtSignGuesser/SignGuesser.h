#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SignGuesser.h"

#include <QPushButton>
#include <QTimer>
#include "QSimpleImageGrabber.h"
#include "QSimpleImageViewer.h"
#include "UnaryProcess.h"
#include "QColorSpaceConvertor_RGB_HSV.h"
#include "QImageThresholder.h"
#include "QNIntervalScrollBar.h"
#include "ImageMerger.h"
#include "BlobExtractor.h"
#include "QImageUtilities.h"
#include "BlobAnalyser.h"

class SignGuesser : public QMainWindow
{
	Q_OBJECT

public:
	SignGuesser(QWidget *parent = Q_NULLPTR);

private:
	Ui::SignGuesserClass ui;

	QPushButton* mConnectButton, *mDisconnectButton, *mCaptureOneButton, *mCaptureContinuouslyButton, *mAnalyseButton, *mShapeContourButton, *mToggleThresh, *mShowRealImage;
	QSimpleImageGrabber mSimpleImageGrabber;
	QSimpleImageViewer* mInputImage, *mProcessedImage, *mProcessedImage2, *mProcessedImage3;
	QImageUtilities::BlobList mBlobList1, mBlobList2, mBlobListMerged;

	QTimer mTimer;
	bool mCapturingContinuously;
	bool mToggleShapeContour = false;
	bool mTogglePixelSwitching = false;
	QColorSpaceConvertor_RGB_HSV mRGB_HSV_Converter;
	QNIntervalScrollBar* mHsvIntervals, *mHsvIntervals2;
	QLabel* mFirstSegmentation, *mSecondSegmentation, *mLetterAnalysed, *mTxtLetterAnalysed;

	QWidget* addTitle(QWidget* widget, QString const& title);
	QImage mMergedImage;

private slots:
	void connectCamera();
	void disconnectCamera();
	void captureOne();
	void captureContinuously();
	void processReadyToCapture(bool ready);
	void toggleShapeContour();
	void togglePixelSwitch();
	void analysePicture();
	void showRealImage();
	void showResult();
	void setupResult();

	virtual void process(QImage const& image);

	void updateGui();

	signals:
		void imageProcessed(QImage const & image);
		void imageProcessed2(QImage const& image);
		void imageProcessed3(QImage const& image);
};

