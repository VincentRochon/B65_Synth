#include "QImageUtilities.h"


#include <cassert>


bool QImageUtilities::validate(bool value)
{
    if (!value) {
        assert(false);
        return false; // throw?
    }
    return value;
}

bool QImageUtilities::validate(QImage const & source)
{
    return validate(source.format() == QImage::Format_ARGB32);
}

inline void QImageUtilities::conformize(QImage const & source, QImage & target)
{
    if (target.size() != source.size() || target.format() != source.format()) {
        target = source.copy();
    }
}

void QImageUtilities::disjunction(QImage const & source, QImage & target)
{
    if (!validate(source)) return;
    if (!validate(target)) return;

    if (source.size() != target.size()) return;

    uint32_t black{ 0xFF000000 };
    uint32_t white{ 0xFFFFFFFF };
    uint32_t const * cur1{ reinterpret_cast<uint32_t const * >(source.bits()) };
    uint32_t * cur2{ reinterpret_cast<uint32_t * >(target.bits()) };
    uint32_t const * end1{ cur1 + source.width() * source.height() };
    while (cur1 < end1) {
        *cur2 = *cur1 != black || *cur2 != black ? white : black;
        ++cur1;
        ++cur2;
    }
}

void QImageUtilities::disjunction(QImage const & source1, QImage const & source2, QImage & target)
{
    if (!validate(source1)) return;
    if (!validate(source2)) return;

    if (source1.size() != source2.size()) return;

    target = source2.copy();

    disjunction(source1, target);
}

void QImageUtilities::invert(QImage & source)
{
    if (!validate(source)) return;

    uint32_t * cur{ reinterpret_cast<uint32_t *>(source.bits()) };
    uint32_t * end{ cur + source.width() * source.height() };
    while (cur < end) {
        *cur = ~*cur | 0xFF000000;
        ++cur;
    }
}

void QImageUtilities::invert(QImage const & source, QImage & target)
{
    if (!validate(source)) return;

    target = source.copy();

    invert(target);
}

void QImageUtilities::drawBorder(QImage & source, uint32_t color)
{
    if (!validate(source)) return;

    uint32_t step{ static_cast<uint32_t>(source.width()) };
    uint32_t * cur1{ reinterpret_cast<uint32_t*>(source.bits()) };
    uint32_t * cur2{ cur1 + source.width() * (source.height() - 1) };
    uint32_t * end1{ cur1 + source.width() };
    while (cur1 < end1) {
        *cur1 = color;
        *cur2 = color;
        ++cur1;
        ++cur2;
    }

    cur1 = reinterpret_cast<uint32_t*>(source.bits()) + source.width();
    cur2 = cur1 + source.width() - 1;
    end1 = reinterpret_cast<uint32_t*>(source.bits()) + source.width() * (source.height() - 1);
    while (cur1 < end1) {
        *cur1 = color;
        *cur2 = color;
        cur1 += step;
        cur2 += step;
    }
}

void QImageUtilities::drawBorder(QImage & source, QImage & target, uint32_t color)
{
    if (!validate(source)) return;

    target = source.copy();

    drawBorder(target, color);
}


void QImageUtilities::threshold(QImage & source, uint8_t channel0Min, uint8_t channel0Max, uint8_t channel1Min, uint8_t channel1Max, uint8_t channel2Min, uint8_t channel2Max, bool keepValue)
{
    if (!validate(source)) return;
    if (!validate(channel0Min <= channel0Max && channel1Min <= channel1Max && channel2Min <= channel2Max)) return;

    uint32_t * pixel{ reinterpret_cast<uint32_t *>(source.bits()) };
    uint32_t * pixelEnd{ pixel + source.width() * source.height() };

    uint32_t black{ 0xFF000000 };
    uint32_t white{ 0xFFFFFFFF };
    if (keepValue) {
        while (pixel < pixelEnd) {
            uint32_t value{ *pixel };
            uint8_t c0{ (value >> 16) & 0xFF };
            uint8_t c1{ (value >> 8) & 0xFF };
            uint8_t c2{ (value >> 0) & 0xFF };
            *pixel = (c0 >= channel0Min && c0 <= channel0Max && c1 >= channel1Min && c1 <= channel1Max && c2 >= channel2Min && c2 <= channel2Max) ? value : black;
            ++pixel;
        }
    } else {
        while (pixel < pixelEnd) {
            uint32_t value{ *pixel };
            uint8_t c0{ (value >> 16) & 0xFF };
            uint8_t c1{ (value >> 8) & 0xFF };
            uint8_t c2{ (value >> 0) & 0xFF };
            *pixel = (c0 >= channel0Min && c0 <= channel0Max && c1 >= channel1Min && c1 <= channel1Max && c2 >= channel2Min && c2 <= channel2Max) ? white : black;
            ++pixel;
        }
    }
}

void QImageUtilities::threshold(QImage const & source, QImage & target, uint8_t channel0Min, uint8_t channel0Max, uint8_t channel1Min, uint8_t channel1Max, uint8_t channel2Min, uint8_t channel2Max, bool keepValue)
{
    if (!validate(source)) return;
    
    target = source.copy();

    threshold(target, channel0Min, channel0Max, channel1Min, channel1Max, channel2Min, channel2Max, keepValue);
}


uint32_t const * QImageUtilities::mSourceBegin{};
uint32_t const * QImageUtilities::mSourceEnd{};
uint32_t QImageUtilities::mSourceWidth{};
uint32_t QImageUtilities::mSourceHeight{};
uint32_t QImageUtilities::mFromColor{};
uint32_t QImageUtilities::mToColor{};
QImageUtilities::BlobInfo QImageUtilities::mCurrentBlob;

void QImageUtilities::fill(QImage & source, uint32_t x, uint32_t y, QColor const & color)
{
    if (!validate(source)) return;
    if (!validate(x < source.width() && y < source.height())) return;

    if (source.pixel(x, y) == color.rgb()) {
        return;
    }

    mSourceBegin = reinterpret_cast<uint32_t *>(source.bits());
    mSourceEnd = mSourceBegin + source.width() * source.height();
    mSourceWidth = source.width();
    mFromColor = source.pixel(x, y);
    mToColor = color.rgb();

    fill(reinterpret_cast<uint32_t *>(source.bits()) + y * source.width() + x);
}

void QImageUtilities::fill(QImage const & source, QImage & target, uint32_t x, uint32_t y, QColor const & color)
{
    if (!validate(source)) return;

    target = source.copy();

    fill(target, x, y, color);
}

void QImageUtilities::fillHole(QImage const & source, QImage & target, QColor const & backgroundColor)
{
    if (!validate(source)) return;

    uint32_t color{ backgroundColor.rgb() };

    target = source.copy();
    drawBorder(target, color);
    fill(target, 0, 0, Qt::white);
    invert(target);
    disjunction(source, target);
}

void QImageUtilities::applyMask(QImage & source, QImage const & toApply, QImage const & mask)
{
    if (!validate(source)) return;
    if (!validate(toApply)) return;
    if (!validate(&mask)) return;
    if (source.size() != toApply.size() || source.size() != mask.size()) return;

    uint32_t * cur{ reinterpret_cast<uint32_t *>(source.bits()) };
    uint32_t * end{ cur + source.width() * source.height() };
    uint32_t const * src{ reinterpret_cast<uint32_t const *>(toApply.bits()) };
    uint32_t const * msk{ reinterpret_cast<uint32_t const *>(mask.bits()) };
    uint32_t white{ 0xFFFFFFFF };
    while (cur < end) {
        if (*msk == white) *cur = *src;
        ++cur;
        ++src;
        ++msk;
    }
}


QImageUtilities::BlobList QImageUtilities::blobize(QImage const & source, QImage & target, QColor const & signalColor, uint32_t minBlobAreaAccepted)
{
    BlobList blobList;

    if (!validate(source)) return blobList;

    target = source.copy();

    mSourceBegin = reinterpret_cast<uint32_t const *>(target.bits());
    mSourceEnd = mSourceBegin + target.width() * target.height();
    mSourceWidth = target.width();
    mSourceHeight = target.height();
    mFromColor = signalColor.rgb();
    mToColor = 0xFF000001;

    uint32_t * cur{ const_cast<uint32_t *>(mSourceBegin) };
    uint32_t * end{ const_cast<uint32_t *>(mSourceEnd) };
    while (cur < end) {
        if (*cur == mFromColor) {
            uint32_t const x{ static_cast<uint32_t>(cur - mSourceBegin) % mSourceWidth };
            uint32_t const y{ static_cast<uint32_t>(cur - mSourceBegin) / mSourceWidth };

            mCurrentBlob.startPixel(x, y);
            blobize(cur, x, y);
            mCurrentBlob.finalize();
            
            if (mCurrentBlob.area() >= minBlobAreaAccepted) {
                blobList.push_back(mCurrentBlob);
            }
            ++mToColor;
        }
        ++cur;
    }

    return blobList;
}


void QImageUtilities::BlobInfo::draw(QPainter & painter, QColor const & boxColor, QColor const & geometricCenterColor, QColor const & centroidColor, int32_t centerSize) const
{
    painter.setPen(boxColor);
    painter.drawRect(mBoundingBox);

    if (centerSize > 0) {
        painter.setPen(geometricCenterColor);
        painter.drawLine(mBoundingBox.center().x(), mBoundingBox.center().y() - centerSize, mBoundingBox.center().x(), mBoundingBox.center().y() + centerSize);
        painter.drawLine(mBoundingBox.center().x() - centerSize, mBoundingBox.center().y(), mBoundingBox.center().x() + centerSize, mBoundingBox.center().y());

        painter.setPen(centroidColor);
        painter.drawLine(mCentroid.x(), mCentroid.y() - centerSize, mCentroid.x(), mCentroid.y() + centerSize);
        painter.drawLine(mCentroid.x() - centerSize, mCentroid.y(), mCentroid.x() + centerSize, mCentroid.y());
    }
}

void QImageUtilities::BlobList::draw(QImage & image, QColor const & boxColor, QColor const & geometricCenterColor, QColor const & centroidColor, int32_t centerSize)
{
    QPainter painter(&image);
    for (auto const & blob : *this) {
        blob.draw(painter, boxColor, geometricCenterColor, centroidColor, centerSize);
    }
}
