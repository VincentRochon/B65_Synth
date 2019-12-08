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
	mInputImage{ new QSimpleImageViewer },
	mProcessedImage{ new QSimpleImageViewer },
	mCapturingContinuously{ false },
	hsvIntervals{ new QNIntervalScrollBar(3) }
{
	ui.setupUi(this);

	auto setupInterval{ [](QNIntervalScrollBar* i, QVector<QString> const& titles) {
	i->setMinimumWidth(350);
	i->setTitle(titles, 75);
	i->setRange(0, 255);
	i->setIntervalToRange();
} };

	setupInterval(hsvIntervals, { "Hue", "Saturation", "Value" });

	QGridLayout* layout{ new QGridLayout };
	layout->addWidget(mConnectButton,0,0);
	layout->addWidget(mDisconnectButton,1,0);
	layout->addWidget(mCaptureOneButton,2,0);
	layout->addWidget(mCaptureContinuouslyButton,3,0);
	layout->addWidget(mInputImage,0,1,8,1);
	layout->addWidget(mProcessedImage,8,1,8,1);
	layout->addWidget(hsvIntervals, 4, 0);

	QWidget* centralWidget{ new QWidget };
	centralWidget->setMinimumSize(1200,1000);
	centralWidget->setLayout(layout);

	setCentralWidget(centralWidget);

	connect(mConnectButton, &QPushButton::clicked, this, &SignGuesser::connectCamera);
	connect(mDisconnectButton, &QPushButton::clicked, this, &SignGuesser::disconnectCamera);
	connect(mCaptureOneButton, &QPushButton::clicked, this, &SignGuesser::captureOne);
	connect(mCaptureContinuouslyButton, &QPushButton::clicked, this, &SignGuesser::captureContinuously);

	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, mInputImage, &QSimpleImageViewer::setImage);
	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, this, &SignGuesser::process);

	connect(this, &SignGuesser::imageProcessed, mProcessedImage, &QSimpleImageViewer::setImage);
		
	//connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, this, &SignGuesser::processCapturedImage);
	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::readyForCaptureChanged, this, &SignGuesser::processReadyToCapture);

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

void SignGuesser::updateGui()
{
	mConnectButton->setEnabled(!mSimpleImageGrabber.isConnected());
	mDisconnectButton->setEnabled(mSimpleImageGrabber.isConnected());
	mCaptureOneButton->setEnabled(mSimpleImageGrabber.isConnected() && !mCapturingContinuously);
	mCaptureContinuouslyButton->setEnabled(mSimpleImageGrabber.isConnected());
	mCaptureContinuouslyButton->setText(mCapturingContinuously ? "Stop capture continuously" : "Start capture continuously");
}

void SignGuesser::process(QImage const& image)
{
	//QImage::Format f{ image.format() };
	//QImage im(image);


	InProcess listOfProcess(image);


	listOfProcess.addMaximumFilter(1);
	//listOfProcess.addMedianFilter(1);
	//listOfProcess.addUniformeConvolution(2);
	listOfProcess.addGaussianConvolution(1);
	// listOfProcess.addNormalisation(255);
	// listOfProcess.addMoyenneImage();
	// listOfProcess.addUniformisation();
	//listOfProcess.addSegmentation(10, 100, 10, 255, 10, 100);
	listOfProcess.Process();
	QImage imageThresh{ listOfProcess.getImageToProcess()[0] };

	mRGB_HSV_Converter.rgb2hsv(imageThresh, imageThresh);

	QImageThresholder::process(imageThresh, imageThresh, 
		hsvIntervals->interval(0).lower(), hsvIntervals->interval(0).upper(),
		hsvIntervals->interval(1).lower(), hsvIntervals->interval(1).upper(),
		hsvIntervals->interval(2).lower(), hsvIntervals->interval(2).upper());

	// good values h {0,29} s{0,7} v{250,255}
	// withn target uv light with distinctions between green / orange h {0,196} s{0,14} v{248,255}




	emit imageProcessed(imageThresh);


	// analyse picture
}
