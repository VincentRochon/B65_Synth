#include "Distribution_Uniforme.h"

Distribution_Uniforme::Distribution_Uniforme(int windowSize)
	:mWindowSize(windowSize)
{
}

std::vector<int> Distribution_Uniforme::fillKernel()
{
	std::vector<int> ConvolutionArray(mWindowSize * 2 + 1);


	int* curData{ ConvolutionArray.data() };


	return ConvolutionArray;
}

QImage Distribution_Uniforme::ProcessImage(QImage const& image)
{
	return QImage();
}
