#include "QNIntervalScrollBar.h"


#include <QVBoxLayout>


QNIntervalScrollBar::QNIntervalScrollBar(size_t n, QWidget * parent)
    : QWidget(parent), mIntervalScrollBars(n)
{
    if (n == 0) throw std::invalid_argument("n must be greater than 0 in QNIntervalScrollBar::QNIntervalScrollBar");

    QVBoxLayout * intervalLayout{ new QVBoxLayout };
    intervalLayout->addStretch();
    for (auto & i : mIntervalScrollBars) {
        i = new QIntervalScrollBar;
        intervalLayout->addWidget(i);
        connect(i, &QIntervalScrollBar::rangeChanged, this, &QNIntervalScrollBar::rangeChanged);
        connect(i, &QIntervalScrollBar::intervalChanged, this, &QNIntervalScrollBar::intervalChanged);
    }
    intervalLayout->addStretch();

    setLayout(intervalLayout);
}

QIntervalScrollBar & QNIntervalScrollBar::interval(size_t i)
{
    if (i >= mIntervalScrollBars.size()) throw std::out_of_range("Out out bound in QNIntervalScrollBar::interval");
    return *mIntervalScrollBars[i];
}

void QNIntervalScrollBar::setTitle(QVector<QString> const & titles, int width)
{
    if (titles.size() != mIntervalScrollBars.size()) throw std::out_of_range("Size of title must be the same as the number of interval in QNIntervalScrollBar::setTitle");
    auto titleIt{ titles.begin() };
    for (auto & i : mIntervalScrollBars) {
        i->setTitle(*titleIt, width);
        ++titleIt;
    }
}

void QNIntervalScrollBar::setNoTitle()
{
    for (auto & i : mIntervalScrollBars) {
        i->setNoTitle();
    }
}

void QNIntervalScrollBar::setMinimum(int min)
{
    for (auto & i : mIntervalScrollBars) {
        i->setMinimum(min);
    }
}

void QNIntervalScrollBar::setMaximum(int max)
{
    for (auto & i : mIntervalScrollBars) {
        i->setMaximum(max);
    }
}

void QNIntervalScrollBar::setRange(int min, int max)
{
    for (auto & i : mIntervalScrollBars) {
        i->setRange(min, max);
    }
}

void QNIntervalScrollBar::setLower(int low)
{
    for (auto & i : mIntervalScrollBars) {
        i->setLower(low);
    }
}

void QNIntervalScrollBar::setUpper(int up)
{
    for (auto & i : mIntervalScrollBars) {
        i->setUpper(up);
    }
}

void QNIntervalScrollBar::setInterval(int low, int up)
{
    for (auto & i : mIntervalScrollBars) {
        i->setInterval(low, up);
    }
}

void QNIntervalScrollBar::setIntervalToRange()
{
    for (auto & i : mIntervalScrollBars) {
        i->setIntervalToRange();
    }
}

