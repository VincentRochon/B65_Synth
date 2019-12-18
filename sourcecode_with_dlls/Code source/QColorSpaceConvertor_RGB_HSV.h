#pragma once


#include <array>
#include <QColor>
#include <QImage>
#include <QDir>


class QColorSpaceConvertor_RGB_HSV
{
public:
    QColorSpaceConvertor_RGB_HSV(QString const & fileSourceDirectory = QDir::currentPath());
    QColorSpaceConvertor_RGB_HSV(QColorSpaceConvertor_RGB_HSV const &) = delete;
    QColorSpaceConvertor_RGB_HSV(QColorSpaceConvertor_RGB_HSV &&) = delete;
    QColorSpaceConvertor_RGB_HSV& operator=(QColorSpaceConvertor_RGB_HSV const &) = delete;
    QColorSpaceConvertor_RGB_HSV& operator=(QColorSpaceConvertor_RGB_HSV &&) = delete;
    ~QColorSpaceConvertor_RGB_HSV() = default;

    void rgb2hsv(QImage const & from, QImage & to);
    void hsv2rgb(QImage const & from, QImage & to);

private:
    static constexpr size_t sLutSize{ 256 * 256 * 256 };
    std::array<uint32_t, sLutSize> mRgb2Hsv;
    std::array<uint32_t, sLutSize> mHsv2Rgb;
};

