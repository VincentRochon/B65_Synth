#pragma once


#include <QWidget>
#include <QVector>
#include <algorithm>
#include "QIntervalScrollBar.h"



class QNIntervalScrollBar : public QWidget
{
    Q_OBJECT

public:
    QNIntervalScrollBar(size_t n = 1, QWidget * parent = nullptr);

    QIntervalScrollBar & interval(size_t i);

    //void setTitle(QVector<QString> const & titles, int width, Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter, QFrame::Shadow shadow = QFrame::Shadow::Plain, QFrame::Shape shape = QFrame::Shape::NoFrame);
    void setTitle(QVector<QString> const & titles, int width);
    void setNoTitle();

public slots:
    void setMinimum(int min);
    void setMaximum(int max);
    void setRange(int min, int max);
    void setLower(int low);
    void setUpper(int up);
    void setInterval(int low, int up);
    void setIntervalToRange();

signals:
    void rangeChanged();
    void intervalChanged();

private:
    QVector<QIntervalScrollBar*> mIntervalScrollBars;

};

