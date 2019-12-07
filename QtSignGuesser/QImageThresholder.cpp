#include "QImageThresholder.h"


#include <QImage>


void QImageThresholder::process(QImage & target, QImage const & source, uint8_t channel0Min, uint8_t channel0Max, uint8_t channel1Min, uint8_t channel1Max, uint8_t channel2Min, uint8_t channel2Max)
{
    if (source.format() != QImage::Format_ARGB32 || channel0Min > channel0Max || channel1Min > channel1Max || channel2Min > channel2Max) {
        return; // throw?
    }
    if (target.size() != source.size()) {
        target = source;
    }

    uint32_t const * pixelFrom{ reinterpret_cast<uint32_t const *>(source.constBits()) };
    uint32_t const * pixelFromEnd{ pixelFrom + source.width() * source.height() };
    uint32_t * pixelTo{ reinterpret_cast<uint32_t *>(target.bits()) };

    uint32_t black{ 0xFF000000 };
    while (pixelFrom < pixelFromEnd) {
        uint32_t value{ *pixelFrom };
        uint8_t c0{ (value >> 16) & 0xFF };
        uint8_t c1{ (value >>  8) & 0xFF };
        uint8_t c2{ (value >>  0) & 0xFF };
        *pixelTo = (c0 >= channel0Min && c0 <= channel0Max && c1 >= channel1Min && c1 <= channel1Max && c2 >= channel2Min && c2 <= channel2Max) ? value : black;
        ++pixelFrom;
        ++pixelTo;
    }
}
