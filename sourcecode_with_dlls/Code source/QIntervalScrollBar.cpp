#include "QIntervalScrollBar.h"


#include <QScrollBar>
#include <QSpinBox>
#include <QPushButton>
#include <QLayout>



QIntervalScrollBar::QIntervalScrollBar(QWidget * parent)
    :   QWidget(parent),
        mLowerScrollBar{ new QScrollBar },
        mUpperScrollBar{ new QScrollBar },
        mLowerSpinBox{ new QSpinBox },
        mUpperSpinBox{ new QSpinBox },
        mTitle{ new QPushButton }
{
    mTitle->setVisible(false);
    mTitle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    mLowerScrollBar->setOrientation(Qt::Horizontal);
    mUpperScrollBar->setOrientation(Qt::Horizontal);
    mLowerScrollBar->setMinimumWidth(100);
    mUpperScrollBar->setMinimumWidth(100);

    mLowerScrollBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mUpperScrollBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mLowerSpinBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    mUpperSpinBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    QHBoxLayout * minLayout{ new QHBoxLayout };
    minLayout->addWidget(mLowerScrollBar);
    minLayout->addWidget(mLowerSpinBox);
    
    QHBoxLayout * maxLayout{ new QHBoxLayout };
    maxLayout->addWidget(mUpperScrollBar);
    maxLayout->addWidget(mUpperSpinBox);

    QVBoxLayout * intervalLayout{ new QVBoxLayout };
    intervalLayout->addLayout(minLayout);
    intervalLayout->addLayout(maxLayout);

    QHBoxLayout * titleLayout{ new QHBoxLayout };
    titleLayout->addWidget(mTitle);
    titleLayout->addLayout(intervalLayout);

    QVBoxLayout * mainLayout{ new QVBoxLayout };
    mainLayout->addLayout(titleLayout);
    //mainLayout->addStretch();

    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    setRange(0, 100);
    setInterval(0, 100, true, false);

    connect(mLowerScrollBar, &QScrollBar::valueChanged, this, &QIntervalScrollBar::updateFromLowerScrollBar);
    connect(mUpperScrollBar, &QScrollBar::valueChanged, this, &QIntervalScrollBar::updateFromUpperScrollBar);
    connect(mLowerSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &QIntervalScrollBar::updateFromLowerSpinBox);
    connect(mUpperSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &QIntervalScrollBar::updateFromUpperSpinBox);
    connect(mTitle, &QPushButton::clicked, this, &QIntervalScrollBar::setIntervalToRange);
}

QIntervalScrollBar::~QIntervalScrollBar()
{
}

int QIntervalScrollBar::minimum() const
{
    return mLowerScrollBar->minimum();
}

int QIntervalScrollBar::maximum() const
{
    return mUpperScrollBar->maximum();
}

int QIntervalScrollBar::lower() const
{
    return mLowerScrollBar->value();
}

int QIntervalScrollBar::upper() const
{
    return mUpperScrollBar->value();
}

void QIntervalScrollBar::setTitle(QString const & title, int width, Qt::Alignment alignment)
{
    mTitle->setText(title);
    mTitle->setFixedWidth(width);
    mTitle->setVisible(true);
}

void QIntervalScrollBar::setNoTitle()
{
    mTitle->setVisible(false);
}

void QIntervalScrollBar::setMinimum(int min)
{
    setRange(min, std::max(min, maximum()));
}

void QIntervalScrollBar::setMaximum(int max)
{
    setRange(std::min(minimum(), max), max);
}

void QIntervalScrollBar::setRange(int min, int max)
{
    if (min > max) throw std::invalid_argument("min > max in QIntervalScrollBar::setRange.");
    if (min == minimum() && max == maximum()) return;

    QSignalBlocker const blocker0(mLowerScrollBar);
    QSignalBlocker const blocker1(mUpperScrollBar);
    QSignalBlocker const blocker2(mLowerSpinBox);
    QSignalBlocker const blocker3(mUpperSpinBox);

    mLowerScrollBar->setRange(min, max);
    mUpperScrollBar->setRange(min, max);
    mLowerSpinBox->setRange(min, max);
    mUpperSpinBox->setRange(min, max);

    mLowerScrollBar->update();
    mUpperScrollBar->update();
    mLowerSpinBox->update();
    mUpperSpinBox->update();

    emit rangeChanged(min, max);

    setInterval(lower(), upper(), true, true);
}

void QIntervalScrollBar::setLower(int low)
{
    setInterval(low, upper(), true, true);
}

void QIntervalScrollBar::setUpper(int up)
{
    setInterval(lower(), up, false, true);
}

void QIntervalScrollBar::setInterval(int low, int up)
{
    setInterval(low, up, true, true);
}

void QIntervalScrollBar::setIntervalToRange()
{
    setInterval(minimum(), maximum());
}

void QIntervalScrollBar::setInterval(int low, int up, bool limitLow, bool validate)
{
    //if (low > up) throw std::invalid_argument("low > up in QIntervalScrollBar::setInterval.");
    if (validate && low == lower() && up == upper() && low >= minimum() && up <= maximum()) return;

    QSignalBlocker const blocker0(mLowerScrollBar);
    QSignalBlocker const blocker1(mUpperScrollBar);
    QSignalBlocker const blocker2(mLowerSpinBox);
    QSignalBlocker const blocker3(mUpperSpinBox);

    if (limitLow) {
        low = std::clamp(low, minimum(), maximum());
        up = std::clamp(up, low, maximum());
    } else {
        up = std::clamp(up, minimum(), maximum());
        low = std::clamp(low, minimum(), up);
    }

    mLowerScrollBar->setValue(low);
    mUpperScrollBar->setValue(up);
    mLowerSpinBox->setValue(low);
    mUpperSpinBox->setValue(up);

    mLowerScrollBar->update();
    mUpperScrollBar->update();
    mLowerSpinBox->update();
    mUpperSpinBox->update();

    emit intervalChanged(low, up);
}

void QIntervalScrollBar::updateFromLowerScrollBar(int low)
{
    setInterval(low, upper(), true, false);
}

void QIntervalScrollBar::updateFromUpperScrollBar(int up)
{
    setInterval(lower(), up, false , false);
}

void QIntervalScrollBar::updateFromLowerSpinBox(int low)
{
    setInterval(low, upper(), true, false);
}

void QIntervalScrollBar::updateFromUpperSpinBox(int up)
{
    setInterval(lower(), up, false, false);
}

