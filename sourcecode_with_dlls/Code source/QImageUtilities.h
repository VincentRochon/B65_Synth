#pragma once

// 
//   ___        _          __               ___  ___                                 _    ____   ____ ____    _________    _     _ _          __                            _   
//  / _ \ _ __ | |_   _   / _| ___  _ __   / _ \|_ _|_ __ ___   __ _  __ _  ___     / \  |  _ \ / ___| __ )  |___ /___ \  | |__ (_) |_ ___   / _| ___  _ __ _ __ ___   __ _| |_ 
// | | | | '_ \| | | | | | |_ / _ \| '__| | | | || || '_ ` _ \ / _` |/ _` |/ _ \   / _ \ | |_) | |  _|  _ \    |_ \ __) | | '_ \| | __/ __| | |_ / _ \| '__| '_ ` _ \ / _` | __|
// | |_| | | | | | |_| | |  _| (_) | |    | |_| || || | | | | | (_| | (_| |  __/  / ___ \|  _ <| |_| | |_) |  ___) / __/  | |_) | | |_\__ \ |  _| (_) | |  | | | | | | (_| | |_ 
//  \___/|_| |_|_|\__, | |_|  \___/|_|     \__\_\___|_| |_| |_|\__,_|\__, |\___| /_/   \_\_| \_\\____|____/  |____/_____| |_.__/|_|\__|___/ |_|  \___/|_|  |_| |_| |_|\__,_|\__|
//                |___/                                              |___/                                                                                                      
// 

#include <QImage>
#include <QList>
#include <QPainter>


class QImageUtilities // only for ARGB32 format
{
public:
    QImageUtilities() = delete;
    QImageUtilities(QImageUtilities const &) = delete;
    QImageUtilities(QImageUtilities &&) = delete;
    QImageUtilities& operator=(QImageUtilities const &) = delete;
    QImageUtilities& operator=(QImageUtilities &&) = delete;
    ~QImageUtilities() = delete;

    static void disjunction(QImage const & source, QImage & target);
    static void disjunction(QImage const & source1, QImage const & source2, QImage & target);
    
    static void invert(QImage & source);
    static void invert(QImage const & source, QImage & target);
        
    static void drawBorder(QImage & source, uint32_t color);
    static void drawBorder(QImage & source, QImage & target, uint32_t color);

    static void threshold(QImage & source, uint8_t channel0Min, uint8_t channel0Max, uint8_t channel1Min, uint8_t channel1Max, uint8_t channel2Min, uint8_t channel2Max, bool keepValue = true);
    static void threshold(QImage const & source, QImage & target, uint8_t channel0Min, uint8_t channel0Max, uint8_t channel1Min, uint8_t channel1Max, uint8_t channel2Min, uint8_t channel2Max, bool keepValue = true);

    static void fill(QImage & source, uint32_t x, uint32_t y, QColor const & color);
    static void fill(QImage const & source, QImage & target, uint32_t x, uint32_t y, QColor const & color);

    static void fillHole(QImage const & source, QImage & target, QColor const & backgroundColor);

    static void applyMask(QImage & source, QImage const & toApply, QImage const & mask);

    class BlobInfo
    {
    private:
        uint32_t mX, mY, mM00, mM01, mM10, mBoundingBoxTopLeftX, mBoundingBoxTopLeftY, mBoundingBoxBottomRightX, mBoundingBoxBottomRightY;
        QPointF mCentroid;
        QRect mBoundingBox;

        void startPixel(int32_t x, int32_t y);
        void addPixel(int32_t x, int32_t y);
        void reset();
        void finalize();

        friend class QImageUtilities;

    public:
        uint32_t topLeftX() const { return mX; }
        uint32_t topLeftY() const { return mY; }
        QRect const & boundingRect() const { return mBoundingBox; }
        QPointF centroid() const { return mCentroid; }
        uint32_t area() const { return mM00; }

        void draw(QPainter & painter, QColor const & boxColor = Qt::magenta, QColor const & geometricCenterColor = Qt::blue, QColor const & centroidColor = Qt::red, int32_t centerSize = 10) const;
    };
    class BlobList : public QList<BlobInfo>
    {
    public:
        void draw(QImage & image, QColor const & boxColor = Qt::magenta, QColor const & geometricCenterColor = Qt::blue, QColor const & centroidColor = Qt::red, int32_t centerSize = 10);
    };
    
    static BlobList blobize(QImage const & source, QImage & target, QColor const & signalColor, uint32_t minBlobAreaAccepted = 1);

private:
    static uint32_t const * mSourceBegin;
    static uint32_t const * mSourceEnd;
    static uint32_t mSourceWidth;
    static uint32_t mSourceHeight;
    static uint32_t mFromColor;
    static uint32_t mToColor;
    static BlobInfo mCurrentBlob;

    static bool validate(bool value);
    static bool validate(QImage const & source);
    static void conformize(QImage const & source, QImage & target);
    static void fill(uint32_t * sourcePos);
    static void blobize(uint32_t * sourcePos, int32_t x, int32_t y);
};


































//
//  _       _ _              _                 _                           _        _   _             
// (_)_ __ | (_)_ __   ___  (_)_ __ ___  _ __ | | ___ _ __ ___   ___ _ __ | |_ __ _| |_(_) ___  _ __  
// | | '_ \| | | '_ \ / _ \ | | '_ ` _ \| '_ \| |/ _ \ '_ ` _ \ / _ \ '_ \| __/ _` | __| |/ _ \| '_ \ 
// | | | | | | | | | |  __/ | | | | | | | |_) | |  __/ | | | | |  __/ | | | || (_| | |_| | (_) | | | |
// |_|_| |_|_|_|_| |_|\___| |_|_| |_| |_| .__/|_|\___|_| |_| |_|\___|_| |_|\__\__,_|\__|_|\___/|_| |_|
//                                      |_|                                                           
//

#pragma inline_recursion(on)
#pragma inline_depth(255)
inline void QImageUtilities::fill(uint32_t * sourcePos)
{
    if (sourcePos >= mSourceBegin && sourcePos < mSourceEnd && *sourcePos == mFromColor) {
        *sourcePos = mToColor;

        fill(sourcePos - 1);
        fill(sourcePos - mSourceWidth);
        fill(sourcePos + 1);
        fill(sourcePos + mSourceWidth);
    }
}


inline void QImageUtilities::blobize(uint32_t * sourcePos, int32_t x, int32_t y)
{
    if (x >= 0 && x < mSourceWidth && y >= 0 && y < mSourceHeight && *sourcePos == mFromColor) {
        *sourcePos = mToColor;

        mCurrentBlob.addPixel(x, y);

        blobize(sourcePos - 1,              x - 1,  y    );
        blobize(sourcePos - mSourceWidth,   x,      y - 1);
        blobize(sourcePos + 1,              x + 1,  y    );
        blobize(sourcePos + mSourceWidth,   x,      y + 1);
    }
}

inline void QImageUtilities::BlobInfo::startPixel(int32_t x, int32_t y) {
    mM00 = 1;
    mM10 = x;
    mM01 = y;
    mBoundingBoxTopLeftX = mBoundingBoxBottomRightX = x;
    mBoundingBoxTopLeftY = mBoundingBoxBottomRightY = y;
    mBoundingBox = QRect();
    mCentroid = QPointF();
}

inline void QImageUtilities::BlobInfo::addPixel(int32_t x, int32_t y) {
    mM00 += 1;
    mM10 += x;
    mM01 += y;
    if (x < mBoundingBoxTopLeftX) mBoundingBoxTopLeftX = x; else if (x > mBoundingBoxBottomRightX) mBoundingBoxBottomRightX = x;
    if (y < mBoundingBoxTopLeftY) mBoundingBoxTopLeftY = y; else if (y > mBoundingBoxBottomRightY) mBoundingBoxBottomRightY = y;
}

inline void QImageUtilities::BlobInfo::reset() {
    mX = mY = mM00 = mM01 = mM10 = mBoundingBoxTopLeftX = mBoundingBoxTopLeftY = mBoundingBoxBottomRightX = mBoundingBoxBottomRightY = 0;
    mCentroid = QPointF();
}

inline void QImageUtilities::BlobInfo::finalize() {
    mBoundingBox.setRect(mBoundingBoxTopLeftX, mBoundingBoxTopLeftY, mBoundingBoxBottomRightX - mBoundingBoxTopLeftX, mBoundingBoxBottomRightY - mBoundingBoxTopLeftY);
    mCentroid = QPointF(static_cast<double>(mM10) / static_cast<double>(mM00), static_cast<double>(mM01) / static_cast<double>(mM00));
}


