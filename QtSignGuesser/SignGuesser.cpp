#include "SignGuesser.h"

#include <QCameraInfo>
#include <QGridLayout>
#include "QSimpleImageGrabber.h"
#include "InProcess.h"

SignGuesser::SignGuesser(QWidget* parent)
	: QMainWindow(parent),
	mConnectButton{ new QPushButton("Connect") },
	mDisconnectButton{ new QPushButton("Disconnect") },
	mCaptureOneButton{ new QPushButton("Capture one image") },
	mCaptureContinuouslyButton{ new QPushButton("Start capture continuously") },
	mAnalyseButton{ new QPushButton("Analyse Picture") },
	mShapeContourButton{ new QPushButton("Activer le contour de formes") },
	mToggleThresh{ new QPushButton("Activer replacage de pixel") },
	mShowRealImage{ new QPushButton("Afficher la vision normale") },
	mInputImage{ new QSimpleImageViewer },
	mProcessedImage{ new QSimpleImageViewer },
	mProcessedImage2{ new QSimpleImageViewer },
	mProcessedImage3{ new QSimpleImageViewer },
	mCapturingContinuously{ false },
	mHsvIntervals{ new QNIntervalScrollBar(3) },
	mHsvIntervals2{ new QNIntervalScrollBar(3) },
	mFirstSegmentation{new QLabel},
	mSecondSegmentation{ new QLabel },
	mLetterAnalysed{new QLabel },
	mTxtLetterAnalysed{new QLabel}
{
	QSize const imageSize(600, 400);
	int const imageSpacing{ 10 };

	ui.setupUi(this);

	auto setupInterval{ [](QNIntervalScrollBar* i, QVector<QString> const& titles) {
	i->setMinimumWidth(350);
	i->setTitle(titles, 75);
	i->setRange(0, 255);
	i->setIntervalToRange();
} };

	auto setupImageLabel{ [&imageSize](QLabel* label) {
	label->setFixedSize(imageSize);
	label->setFrameShadow(QFrame::Shadow::Plain);
	label->setFrameShape(QFrame::Shape::Box);
} };
	setupImageLabel(mFirstSegmentation);
	setupImageLabel(mSecondSegmentation);
	//setupImageLabel(mDummyLabel);
	setupInterval(mHsvIntervals, { "Hue", "Saturation", "Value" });
	setupInterval(mHsvIntervals2, { "Hue", "Saturation", "Value" });


	QGridLayout* layout{ new QGridLayout };
	layout->addWidget(mConnectButton,0,0);
	layout->addWidget(mDisconnectButton,1,0);
	layout->addWidget(mCaptureOneButton,2,0);
	layout->addWidget(mCaptureContinuouslyButton,3,0);
	layout->addWidget(mInputImage,8,2,8,2);
	layout->addWidget(mProcessedImage,0,1,8,1);
	layout->addWidget(mProcessedImage2, 8, 1, 8, 1);
	layout->addWidget(mProcessedImage3, 0, 2, 8, 2);
	layout->addWidget(addTitle(mFirstSegmentation,"Premiere segmentation : Green"),4,0);
	layout->addWidget(addTitle(mSecondSegmentation, "Deuxieme segmentation : Orange"), 8, 0);
	layout->addWidget(mHsvIntervals, 5, 0);
	layout->addWidget(mToggleThresh, 6, 0);
	layout->addWidget(mHsvIntervals2, 9, 0);
	layout->addWidget(mAnalyseButton,11,0);
	layout->addWidget(mShapeContourButton, 10, 0);
	layout->addWidget(mTxtLetterAnalysed,9,2);
	layout->addWidget(mLetterAnalysed,9,3);
	layout->addWidget(mShowRealImage, 12, 0);


	QWidget* centralWidget{ new QWidget };
	centralWidget->setMinimumSize(1900,1000);
	centralWidget->setLayout(layout);

	setCentralWidget(centralWidget);

	connect(mConnectButton, &QPushButton::clicked, this, &SignGuesser::connectCamera);
	connect(mDisconnectButton, &QPushButton::clicked, this, &SignGuesser::disconnectCamera);
	connect(mCaptureOneButton, &QPushButton::clicked, this, &SignGuesser::captureOne);
	connect(mCaptureContinuouslyButton, &QPushButton::clicked, this, &SignGuesser::captureContinuously);
	connect(mShapeContourButton, &QPushButton::clicked, this, &SignGuesser::toggleShapeContour);
	connect(mToggleThresh, &QPushButton::clicked, this, &SignGuesser::togglePixelSwitch);
	connect(mAnalyseButton, &QPushButton::clicked, this, &SignGuesser::analysePicture);
	connect(mShowRealImage, &QPushButton::clicked, this, &SignGuesser::showRealImage);

	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, mInputImage, &QSimpleImageViewer::setImage);
	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, this, &SignGuesser::process);

	connect(this, &SignGuesser::imageProcessed, mProcessedImage, &QSimpleImageViewer::setImage);
	connect(this, &SignGuesser::imageProcessed2, mProcessedImage2, &QSimpleImageViewer::setImage);
	connect(this, &SignGuesser::imageProcessed3, mProcessedImage3, &QSimpleImageViewer::setImage);
		
	//connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, this, &SignGuesser::processCapturedImage);
	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::readyForCaptureChanged, this, &SignGuesser::processReadyToCapture);

	// Default value
	setupResult();

	updateGui();
}


void SignGuesser::connectCamera()
{
	mSimpleImageGrabber.connect();
	updateGui();
}

void SignGuesser::disconnectCamera()
{
	mSimpleImageGrabber.disconnect();
	updateGui();
}

void SignGuesser::captureOne()
{
	mSimpleImageGrabber.capture();
	updateGui();
}

void SignGuesser::captureContinuously()
{
	mCapturingContinuously = !mCapturingContinuously;
	mSimpleImageGrabber.capture();
	updateGui();
}

void SignGuesser::processReadyToCapture(bool ready)
{
	if (ready && mCapturingContinuously) {
		mSimpleImageGrabber.capture();
	}
}

void SignGuesser::toggleShapeContour()
{
	mToggleShapeContour = !mToggleShapeContour;
	updateGui();
}

void SignGuesser::togglePixelSwitch()
{
	mTogglePixelSwitching = !mTogglePixelSwitching;
	updateGui();
}

void SignGuesser::analysePicture() {

	// merge blob list
	mBlobListMerged = mBlobList1;
	mBlobListMerged += mBlobList2;
	BlobAnalyser::sortList(mBlobListMerged); // good blob list
	BlobAnalyser::trimList(mBlobListMerged,5); // trim of blobs ( max 5)

	// Eval Positions
	mLetterAnalysed->setText(BlobAnalyser::analysePosition(mBlobListMerged));

	showResult();

}

void SignGuesser::showRealImage() {

	mInputImage->setVisible(true);
	mTxtLetterAnalysed->setVisible(false);
	mLetterAnalysed->setVisible(false);
	updateGui();
}

void SignGuesser::showResult()
{
	mInputImage->setVisible(false);
	mTxtLetterAnalysed->setVisible(true);
	mLetterAnalysed->setVisible(true);
	updateGui();
}

void SignGuesser::setupResult()
{
	mTxtLetterAnalysed->setVisible(false);
	mTxtLetterAnalysed->setText("Resultat : ");
	mLetterAnalysed->setVisible(false);
	QFont newFont = mTxtLetterAnalysed->font();
	newFont.setPointSizeF(36);
	newFont.setBold(true);
	mTxtLetterAnalysed->setFont(newFont);
	newFont.setPointSizeF(60);
	mLetterAnalysed->setFont(newFont);
}


void SignGuesser::updateGui()
{
	mConnectButton->setEnabled(!mSimpleImageGrabber.isConnected());
	mDisconnectButton->setEnabled(mSimpleImageGrabber.isConnected());
	mCaptureOneButton->setEnabled(mSimpleImageGrabber.isConnected() && !mCapturingContinuously);
	mCaptureContinuouslyButton->setEnabled(mSimpleImageGrabber.isConnected());
	mCaptureContinuouslyButton->setText(mCapturingContinuously ? "Stop capture continuously" : "Start capture continuously");
	mShapeContourButton->setText(mToggleShapeContour ? "Desactiver le contour de formes" : "Activer le contour de formes");
	mToggleThresh->setText(mTogglePixelSwitching ? "Desactiver le remplacage de pixel" : "Activer le remplacage de pixel");
}

void SignGuesser::process(QImage const& image)
{

	InProcess listOfProcess(image);


	listOfProcess.addMaximumFilter(1);
	// listOfProcess.addMedianFilter(1);
	// listOfProcess.addUniformeConvolution(1);
	listOfProcess.addGaussianConvolution(1);
	// listOfProcess.addNormalisation(255);
	// listOfProcess.addMoyenneImage();
	// listOfProcess.addUniformisation();
	// listOfProcess.addSegmentation(10, 100, 10, 255, 10, 100);
	listOfProcess.Process();
	QImage imageThresh{ listOfProcess.getImageToProcess()[0] };

	mRGB_HSV_Converter.rgb2hsv(imageThresh, imageThresh);

	QImage imageThreshCopy{ imageThresh };

	if (mTogglePixelSwitching) {


		QImageThresholder::process(imageThresh, imageThresh, 
			mHsvIntervals->interval(0).lower(), mHsvIntervals->interval(0).upper(),
			mHsvIntervals->interval(1).lower(), mHsvIntervals->interval(1).upper(),
			mHsvIntervals->interval(2).lower(), mHsvIntervals->interval(2).upper());
	
		QImageThresholder::process(imageThreshCopy, imageThreshCopy,
			mHsvIntervals2->interval(0).lower(), mHsvIntervals2->interval(0).upper(),
			mHsvIntervals2->interval(1).lower(), mHsvIntervals2->interval(1).upper(),
			mHsvIntervals2->interval(2).lower(), mHsvIntervals2->interval(2).upper());
	}
	else {

		QImageThresholder::process(imageThresh, imageThresh,
			mHsvIntervals->interval(0).lower(), mHsvIntervals->interval(0).upper(),
			mHsvIntervals->interval(1).lower(), mHsvIntervals->interval(1).upper(),
			mHsvIntervals->interval(2).lower(), mHsvIntervals->interval(2).upper(),0xFF'FF'FF'FF);

		QImageThresholder::process(imageThreshCopy, imageThreshCopy,
			mHsvIntervals2->interval(0).lower(), mHsvIntervals2->interval(0).upper(),
			mHsvIntervals2->interval(1).lower(), mHsvIntervals2->interval(1).upper(),
			mHsvIntervals2->interval(2).lower(), mHsvIntervals2->interval(2).upper(),0xFF'FF'FF'FF);
	}



	if (mToggleShapeContour) {

		mBlobList1 = QImageUtilities::blobize(imageThresh, imageThresh, Qt::white, 625);
		mBlobList2 = QImageUtilities::blobize(imageThreshCopy, imageThreshCopy, Qt::white, 625);

		mBlobList1.draw(imageThresh);
		mBlobList2.draw(imageThreshCopy);

	}
	   
	emit imageProcessed(imageThresh);
	emit imageProcessed2(imageThreshCopy);
	emit imageProcessed3(ImageMerger::merge(imageThresh, imageThreshCopy));

}


QWidget* SignGuesser::addTitle(QWidget* widget, QString const& title)
{
	QLabel* titleWidget{ new QLabel(title) };
	titleWidget->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	QVBoxLayout* layout{ new QVBoxLayout };
	layout->addWidget(titleWidget);

	QWidget* w{ new QWidget };
	w->setLayout(layout);

	return w;
}
