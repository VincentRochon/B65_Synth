#pragma once


#include <QWidget>


class QScrollBar;
class QSpinBox;
class QPushButton;
//#include <QLabel>


class QIntervalScrollBar : public QWidget
{
    Q_OBJECT

public:
    QIntervalScrollBar(QWidget * parent = nullptr);
    ~QIntervalScrollBar();

    int minimum() const;
    int maximum() const;

    int lower() const;
    int upper() const;

    void setTitle(QString const & title, int width, Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter);
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
    void rangeChanged(int min, int max);
    void intervalChanged(int low, int up);

private:
    QScrollBar * mLowerScrollBar;
    QScrollBar * mUpperScrollBar;
    QSpinBox * mLowerSpinBox;
    QSpinBox * mUpperSpinBox;
    QPushButton * mTitle;

    void setInterval(int low, int up, bool limitLow, bool validate);

private slots:
    void updateFromLowerScrollBar(int low);
    void updateFromUpperScrollBar(int up);
    void updateFromLowerSpinBox(int low);
    void updateFromUpperSpinBox(int up);
};

