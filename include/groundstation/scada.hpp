 #ifndef SCADA_H
#define SCADA_H

#include "qnode.hpp"
#include "ui_scada.h"
#include "drawArrow.hpp"
#include "Robot.hpp"
#include<QTimer>
#include <QMainWindow>
#include <QPixmap>
#include <QPaintEvent>
#include<QImage>




namespace groundstation{



class SCADA : public QWidget
{
    Q_OBJECT
    
public:
    SCADA(int argc, char** argv, QWidget *parent = 0);
    ~SCADA();
    void paintEvent(QPaintEvent *);
    Robot* robot;
    void initialize();

    
private:
    Ui::SCADA *ui;
    QPixmap qpixUp;
    QPixmap qpixSide;
    //cv::VideoCapture cam;
    QImage image;
    QTimer* tcam;
    QTimer* tup;
    QNode qnode;

public slots:
    ////BASIC SEQ.
     void BasicChangeValues();                         //1
     void BasicEngineSteer(int i, double w);          //2
     void BasicEngineDrivingSteer(int i, double w);   //3    ARG?
     void BasicCylinderSetToZero(double w);           //4
     void BasicArmPositionChange(POSITION pos);       //5
     void BasicElectromagnetSet(bool on);                //6
     void BasicDriveForward(double v, double t);      //7
     void BasicTurn(double a, double t);              //8
     void BasicTurnArc(bool dir1, bool dir3, double w1, double w2);//9    ARG?

     ///START SEQ.
     void StartAll();                                 //20

     ////MINING SEQ
     void MiningInitiate();                           //30
     void MiningCylinderState(bool opened);           //31     ARG?
     void MiningArmPosition4();                       //32
     void MiningCylinderStart();                      //33
     void MiningCalibration() ;                       //34
     void MiningCylinderToGround(double w);           //35
     void MiningDriving();                            //37
     void MiningTensometerMass();                     //38
     void MiningArmPosition1();                       //39

     ///UNLOAD SEQ
     void UnloadInitiate();                           //40
     void UnloadArmPosition1();                       //41
     void UnloadCylinderToZero(double w);             //42
     void UnloadCylinderOpen();                       //43
     void UnloadCylinderState(bool opened);           //44
     void UnloadCylinderShake();                      //45
     void UnloadCylinderRotate(double angle, double w);//46
     void UnloadCylinderClose();                      //47
     void UnloadArmPositionCheck();                   //48

     ///SECURITY SEQ
     void SecurityAllEnginesStop();                   //101
     void SecurityDrivingEnginesStop();               //102
     void SecurityArmEngineStop();                    //103
     void SecurityCylinderEngineStop();               //104
     void SecurityAutonomy();                         //105


    void updateImageCam();



};


}
#endif // SCADA_H
