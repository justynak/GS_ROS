#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>

class Battery : public QObject
{
    Q_OBJECT

private:
    double voltage;
    double current;

public:
    explicit Battery(QObject *parent = 0);
    double GetVoltage(){return voltage;}
    double GetCurrent(){return current;}

    void SetCurrent(double I){current=I;}
    void SetVoltage(double U){voltage=U;}


    
signals:
    void CurrentChanged();
    void VoltageChanged();

public slots:
    
};

#endif // BATTERY_H
