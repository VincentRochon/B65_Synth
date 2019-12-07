#pragma once


class QImage;
#include <cstdint>


class QImageThresholder
{
public:
    QImageThresholder() = delete;
    QImageThresholder(QImageThresholder const &) = delete;
    QImageThresholder(QImageThresholder &&) = delete;
    QImageThresholder& operator=(QImageThresholder const &) = delete;
    QImageThresholder& operator=(QImageThresholder &&) = delete;
    ~QImageThresholder() = delete;

    static void process(QImage & target, QImage const & source, uint8_t channel0Min, uint8_t channel0Max, uint8_t channel1Min, uint8_t channel1Max, uint8_t channel2Min, uint8_t channel2Max);
};

