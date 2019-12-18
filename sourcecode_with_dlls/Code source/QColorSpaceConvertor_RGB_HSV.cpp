#include "QColorSpaceConvertor_RGB_HSV.h"


#include <QFileInfo>
#include <QFile>
#include <QByteArray>
#include <QDebug>


QColorSpaceConvertor_RGB_HSV::QColorSpaceConvertor_RGB_HSV(QString const & fileSourceDirectory)
{
    QString const raw_data_source_file_name("rgb_hsv_converter_lut.bin");
    QFileInfo fileInfo(QDir(fileSourceDirectory), raw_data_source_file_name);
    if (fileInfo.exists()) {
        QFile file(fileInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly)) {
            qint64 r1{ file.read(reinterpret_cast<char *>(mRgb2Hsv.data()), sizeof uint32_t * mRgb2Hsv.size()) };
            qint64 r2{ file.read(reinterpret_cast<char *>(mHsv2Rgb.data()), sizeof uint32_t * mHsv2Rgb.size()) };
            if (r1 == -1 || r2 == -1) {
                qDebug() << "Error loading rgb_hsv_converter_lut.bin file. Removing and recreating file.";
                file.close();
            } else {
                qDebug() << "rgb_hsv_converter_lut.bin file read with success.";
                file.close();
                return; // success
            }
        } else {
            qDebug() << "Cannot read from rgb_hsv_converter_lut.bin file. Removing and recreating file.";
            QFile::remove(fileInfo.absoluteFilePath());
        }
    }
        
    memset(mRgb2Hsv.data(), 0, sizeof uint32_t * mRgb2Hsv.size());

    for (int r{}; r < 256; ++r) {
        for (int g{}; g < 256; ++g) {
            for (int b{}; b < 256; ++b) {
                QColor c(r, g, b);
                mRgb2Hsv[r << 16 | g << 8 | b] = 0xFF000000 |
                    static_cast<uint8_t>(c.hsvHueF() * 255) << 16 |
                    static_cast<uint8_t>(c.hsvSaturationF() * 255) << 8 |
                    static_cast<uint8_t>(c.valueF() * 255) << 0;

                QColor d(QColor::fromHsvF(r / 255.0, g / 255.0, b / 255.0));
                mHsv2Rgb[r << 16 | g << 8 | b] = 0xFF000000 |
                    static_cast<uint8_t>(d.redF() * 255) << 16 |
                    static_cast<uint8_t>(d.greenF() * 255) << 8 |
                    static_cast<uint8_t>(d.blueF() * 255) << 0;
            }
        }
    }

    QFile file(fileInfo.absoluteFilePath());
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot create rgb_hsv_converter_lut.bin file.";
    } else {
        qint64 r1{ file.write(reinterpret_cast<char *>(mRgb2Hsv.data()), sizeof uint32_t * mRgb2Hsv.size()) };
        qint64 r2{ file.write(reinterpret_cast<char *>(mHsv2Rgb.data()), sizeof uint32_t * mHsv2Rgb.size()) };
        if (r1 == -1 || r2 == -1) {
            qDebug() << "Error writing rgb_hsv_converter_lut.bin file.";
        } else {
            qDebug() << "rgb_hsv_converter_lut.bin file written with success.";
        }
    }
    file.close();
}

void QColorSpaceConvertor_RGB_HSV::rgb2hsv(QImage const & from, QImage & to)
{
    if (from.size() != to.size() || from.format() != to.format() || from.format() != QImage::Format_ARGB32) {
        return; // throw ?
    }

    uint32_t const * pixelFrom{ reinterpret_cast<uint32_t const *>(from.constBits()) };
    uint32_t const * pixelFromEnd{ pixelFrom + from.width() * from.height() };
    uint32_t * pixelTo{ reinterpret_cast<uint32_t *>(to.bits()) };

    while (pixelFrom < pixelFromEnd) {
        *pixelTo = mRgb2Hsv[*pixelFrom & 0x00FFFFFF];
        ++pixelFrom;
        ++pixelTo;
    }
}

void QColorSpaceConvertor_RGB_HSV::hsv2rgb(QImage const & from, QImage & to)
{
    if (from.size() != to.size() || from.format() != to.format() || from.format() != QImage::Format_ARGB32) {
        return; // throw ?
    }

    uint32_t const * pixelFrom{ reinterpret_cast<uint32_t const *>(from.constBits()) };
    uint32_t const * pixelFromEnd{ pixelFrom + from.width() * from.height() };
    uint32_t * pixelTo{ reinterpret_cast<uint32_t *>(to.bits()) };

    while (pixelFrom < pixelFromEnd) {
        *pixelTo = mHsv2Rgb[*pixelFrom & 0x00FFFFFF];
        ++pixelFrom;
        ++pixelTo;
    }
}
