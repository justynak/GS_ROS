#include "../include/groundstation/mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>
#include<QTimer>


int seconds = 0;
int mins = 10;

namespace groundstation{

using namespace Qt;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    //connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(close()));
    imgUp.load(":/images/dol.png");
    imgSide.load(":/images/bok.png");
    imgMap.load(":/images/lunarena2.png");
    imgSmall.load(":/images/small.png");

    signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(ui->button_Mining_SetCylinderTo0, 20);
    signalMapper->setMapping(ui->button_Unloading_SetCylinderTo0, 20);

     this->setFocus();

    joy = new Joystick();

   ////    IP CAM
    ////////  ZAMIAST 0 -> const std::string videoStreamAddress = "http://<username:password>@<ip_address>/video.cgi?.mjpg"; //czy w tym stylu
    const std::string videoStreamAddress = "http://admin:admin@192.168.1.201/ramdisk/preview.bmp";
    cam.open(0);
    //////////////////////////////////

    t=new QTimer();
    t->start(50);
    t_counter=new QTimer();
    t_counter->start(1000);
    t_joy = new QTimer();
    t_joy->start(200);

    connect(t, SIGNAL(timeout()), this, SLOT(updateCamImage()));
    connect(t_counter, SIGNAL(timeout()), this, SLOT(updateTime()));

    if(!(joy->init("/dev/input/js0"))){
        t = new QTimer(this);
        t->start();
        connect(t_joy, SIGNAL(timeout()), this, SLOT(updateJoystick()));
    }

    //disable checks
    ui->checkBox_ArchEngineLeft->setCheckable(false);
    ui->checkBox_ArchEngineRight->setCheckable(false);

    ui->checkBox_Mining_ArmPosition4->setCheckable(false);
    ui->checkBox_Mining_CloseCylinder->setCheckable(false);
    ui->checkBox_Mining_MiningDriving->setCheckable(false);
    ui->checkBox_Mining_SetArmPosition1->setCheckable(false);
    ui->checkBox_Mining_SetCylinderTo0->setCheckable(false);
    ui->checkBox_Mining_StartCylinder->setCheckable(false);
    ui->checkBox_Mining_TensometerMass->setCheckable(false);

    ui->checkBox_Unloading_CheckArmPosition->setCheckable(false);
    ui->checkBox_Unloading_CloseCylinder->setCheckable(false);
    ui->checkBox_Unloading_OpenCylinder->setCheckable(false);
    ui->checkBox_Unloading_RotateCylinder->setCheckable(false);
    ui->checkBox_Unloading_SetArmPosition1->setCheckable(false);
    ui->checkBox_Unloading_SetCylinderTo0->setCheckable(false);
    ui->checkBox_Unloading_ShakeCylinder->setCheckable(false);

    //disable all buttons except start
    ui->button_Arch->setEnabled(false);
    ui->button_Calibration->setEnabled(false);
    ui->button_Electromagnets->setEnabled(false);
    ui->button_EngineSteer->setEnabled(false);
    ui->button_Mining_TensometerMass->setEnabled(false);
    ui->button_StopAll->setEnabled(false);
    ui->button_StopArm->setEnabled(false);
    ui->button_StopCylinder->setEnabled(false);
    ui->button_StopDriving->setEnabled(false);
    ui->button_Teleoperation->setEnabled(false);

    ui->button_Mining_ArmPosition4->setEnabled(false);
    ui->button_Mining_CheckCylinderState->setEnabled(false);
    ui->button_Mining_Initiate->setEnabled(false);
    ui->button_Mining_MiningDriving->setEnabled(false);
    ui->button_Mining_SetCylinderTo0->setEnabled(false);
    ui->button_Mining_StartCylinder->setEnabled(false);
    ui->button_Mining_ArmPositionTo1->setEnabled(false);


    ui->button_Unloading_CheckArmPosition->setEnabled(false);
    ui->button_Unloading_CloseCylinder->setEnabled(false);
    ui->button_Unloading_Initiate->setEnabled(false);
    ui->button_Unloading_OpenCylinder->setEnabled(false);
    ui->button_Unloading_RotateCylinder->setEnabled(false);
    ui->button_Unloading_SetArmPosition1->setEnabled(false);
    ui->button_Unloading_SetCylinderTo0->setEnabled(false);
    ui->button_Unloading_ShakeCylinder->setEnabled(false);
    ui->button_UpdateValues->setEnabled(false);


}

void MainWindow::initialize(){
    connect(ui->button_UpdateValues, SIGNAL(clicked()), this, SLOT(BasicChangeValues()));
    connect(ui->button_EngineSteer, SIGNAL(clicked()), this, SLOT(BasicEngineSteer()));
    //void BasicCylinderSetToZero(double w);           //4
    //?
    //void BasicElectromagnetSet(bool on);                //6
    connect(ui->button_Electromagnets, SIGNAL(clicked()), this, SLOT(BasicElectromagnetSet()));
    connect(ui->button_Arch, SIGNAL(clicked()), this, SLOT(BasicTurnArc()));
    connect(ui->button_StartAll, SIGNAL(clicked()), this, SLOT(StartAll()));
    connect(ui->button_Mining_Initiate, SIGNAL(clicked()), this, SLOT(MiningInitiate()));
    connect(ui->button_Mining_CheckCylinderState, SIGNAL(clicked()), this, SLOT(MiningCylinderState()));
    connect(ui->button_Mining_ArmPosition4, SIGNAL(clicked()), this, SLOT(MiningArmPosition4()));
    connect(ui->button_Mining_StartCylinder, SIGNAL(clicked()), this, SLOT(MiningCylinderStart()));
    connect(ui->button_Calibration, SIGNAL(clicked()), this, SLOT(MiningCalibration()));
    connect(ui->button_Mining_SetCylinderTo0, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(MiningCylinderToGround(int)));
    connect(ui->button_Mining_MiningDriving, SIGNAL(clicked()), this, SLOT(MiningDriving()));
    connect(ui->button_Mining_TensometerMass, SIGNAL(clicked()), this, SLOT(MiningTensometerMass()));
    connect(ui->button_Mining_ArmPositionTo1, SIGNAL(clicked()), this, SLOT(MiningArmPosition1()));
    connect(ui->button_Unloading_Initiate, SIGNAL(clicked()), this, SLOT(UnloadInitiate()));
    connect(ui->button_Unloading_SetArmPosition1, SIGNAL(clicked()), this, SLOT(UnloadArmPosition1()));
    connect(ui->button_Unloading_SetCylinderTo0, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(UnloadCylinderToZero(int)));
    connect(ui->button_Unloading_OpenCylinder, SIGNAL(clicked()), this, SLOT(UnloadCylinderOpen()));
    connect(ui->button_Unloading_ShakeCylinder, SIGNAL(clicked()), this, SLOT(UnloadCylinderShake()));
    connect(ui->button_Unloading_RotateCylinder, SIGNAL(clicked()), this, SLOT(UnloadCylinderRotate()));
    connect(ui->button_Unloading_CloseCylinder, SIGNAL(clicked()), SLOT(UnloadCylinderClose()));
    connect(ui->button_Unloading_CheckArmPosition, SIGNAL(clicked()), this, SLOT(UnloadArmPositionCheck()));
    connect(ui->button_StopAll, SIGNAL(clicked()), this, SLOT(SecurityAllEnginesStop()));
    connect(ui->button_StopDriving, SIGNAL(clicked()), this, SLOT(SecurityDrivingEnginesStop()));
    connect(ui->button_StopArm, SIGNAL(clicked()), this, SLOT(SecurityArmEngineStop()));
    connect(ui->button_StopCylinder, SIGNAL(clicked()), this, SLOT(SecurityCylinderEngineStop()));
    connect(ui->button_Teleoperation, SIGNAL(clicked()), this, SLOT(SecurityAutonomy()));

    /*
    ui->lineEdit_ArchEngineLeft->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_ArchEngineRight->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_EngineSteerArm->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_EngineSteerCylinder->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_EngineSteerLeft->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_SteerEngineRight->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_Unloading_CylinderAngle->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_Unloading_CylinderSpeed->setFocusPolicy(Qt::NoFocus);
    */

    this->setFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete t;

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W){
        //ui->labelMap->setText(tr("aaa"));
        robot->BasicDriveForward(0.2, 0.2);

    }
    if(event->key()==Qt::Key_D){
        robot->BasicTurn(-5, 0.2);
    }
    if(event->key()==Qt::Key_A){
        robot->BasicTurn(5, 0.2);

    }

    if(event->key()==Qt::Key_S){
        robot->BasicDriveForward(-0.2, 0.2);
    }

    if(event->key()==Qt::Key_1){
        robot->BasicArmPositionChange(a);
    }

    if(event->key()==Qt::Key_2){
        robot->BasicArmPositionChange(b);
    }

    if(event->key()==Qt::Key_3){
        robot->BasicArmPositionChange(c);
    }

    if(event->key()==Qt::Key_4){
        robot->BasicArmPositionChange(d);
    }

    if(event->key()==Qt::Key_Escape){
        robot->SecurityAllEnginesStop();
    }
}

void MainWindow::paintEvent(QPaintEvent *){
    QPixmap side(imgSide);
    QPainter painter(&side);
    paintArrowSpeed(QPoint(120,240), robot->GetLinearVelocity(), 20, painter);
    painter.end();
    QPixmap map(imgMap);
    painter.begin(&map);
    //painter.drawPixmap(QPoint(120,240), imgSmall);
    //void paintLocation(double* point, double v, double sze, double a, QPixmap& pic, QPainter& painter){
    paintLocation(robot->GetPosition(), robot->GetLinearVelocity(), 7,robot->GetPosition()[2], imgSmall, painter);
    ui->labelMap->setPixmap(map);
    painter.end();

}


    //if(joy->getButton(0)) robot->Dig();
    //ui->browser->append(tr("Digging"));
    //if(joy->getButton(3)) robot->Drop();
    //ui->browser->append(tr("Dropping"));

void MainWindow::updateCamImage(){
    cv::Mat mat;
    cam>>mat;
    if(mat.empty()) return;
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    //cv::flip(mat,mat,1);

    QImage img((uchar*)mat.data, mat.cols, mat.rows, QImage::Format_RGB888);
    ui->labelWebCam->setPixmap(QPixmap::fromImage(img));

}


void MainWindow::updateTime(){
    if(mins==10){
        ui->lcdNumber_RemainingTime->display(tr("%1:0%2").arg(mins).arg(seconds));
        seconds=59;
        --mins;
    }

    else if(mins>=0){

        if(seconds==0){
            ui->lcdNumber_RemainingTime->display(tr("0%1:0%2").arg(mins).arg(seconds));
            seconds=59;
            --mins;
        }
        else if(seconds < 10){
            ui->lcdNumber_RemainingTime->display(tr("0%1:0%2").arg(mins).arg(seconds));
            --seconds;
            }
        else{
            ui->lcdNumber_RemainingTime->display(tr("0%1:%2").arg(mins).arg(seconds));
            --seconds;

        }
    }
    else
        t_counter->stop();
}

void MainWindow::BasicChangeValues(){
    robot->BasicChangeValues();
}

void MainWindow::BasicEngineSteer(){
    if(ui->radioEngineRight->isChecked()){
         robot->BasicEngineSteer(4, ui->lineEdit_SteerEngineRight->text().toDouble());
        }
    if(ui->radioEngineLeft->isChecked()){
        robot->BasicEngineSteer(3, ui->lineEdit_EngineSteerLeft->text().toDouble());
    }
    if(ui->radioEngineArm->isChecked()){
            robot->BasicEngineSteer(2, ui->lineEdit_EngineSteerArm->text().toDouble());
        }
    if(ui->radioEngineCylinder->isChecked()){
        robot->BasicEngineSteer(1, ui->lineEdit_EngineSteerCylinder->text().toDouble());
    }
}
//2
void MainWindow::BasicEngineDrivingSteer(){
}   //3

void MainWindow::BasicCylinderSetToZero(double w){}

//4
void MainWindow::BasicArmPositionChange(POSITION pos){
    robot->BasicArmPositionChange(pos);
}       //5
void MainWindow::BasicElectromagnetSet(){
    if(ui->button_Electromagnets->text() == tr("ON")){
        robot->BasicElectromagnetSet(true);
        ui->button_Electromagnets->setText(tr("OFF"));
    }
    else{
        robot->BasicElectromagnetSet(false);
        ui->button_Electromagnets->setText(tr("ON")); //just to make sure
    }
}
//6
void MainWindow::BasicDriveForward(double v, double t){
    robot->BasicDriveForward(v,t);
}      //7
void MainWindow::BasicTurn(double a, double t){
    robot->BasicTurn(a,t);
}
//8
void MainWindow::BasicTurnArc(){
    bool dir1 = ui->checkBox_ArchEngineRight->isChecked();
    bool dir2= ui->checkBox_ArchEngineRight->isChecked();
    double w1 = ui->lineEdit_ArchEngineRight->text().toDouble();
    double w2=ui->lineEdit_ArchEngineLeft->text().toDouble();
    robot->BasicTurnArc(dir1, dir2, w1, w2);
}
//9    ARG?

///START SEQ.
void MainWindow::StartAll(){
    robot->StartAll();
    ui->button_StartAll->setDisabled(true);

    //enable all
    ui->button_Arch->setEnabled(true);
    ui->button_Calibration->setEnabled(true);
    ui->button_EngineSteer->setEnabled(true);
    ui->button_Mining_Initiate->setEnabled(true);
    ui->button_StopAll->setEnabled(true);
    ui->button_StopArm->setEnabled(true);
    ui->button_StopCylinder->setEnabled(true);
    ui->button_StopDriving->setEnabled(true);
    ui->button_Teleoperation->setEnabled(true);
    ui->button_Unloading_Initiate->setEnabled(true);
    ui->button_UpdateValues->setEnabled(true);
    ui->button_Electromagnets->setEnabled(true);

    ui->checkBox_ArchEngineLeft->setCheckable(true);
    ui->checkBox_ArchEngineRight->setCheckable(true);



}                                 //20

////MINING SEQ
void MainWindow::MiningInitiate(){
    robot->MiningInitiate();
    //enable mining
    ui->checkBox_Mining_ArmPosition4->setCheckable(true);
    ui->checkBox_Mining_CloseCylinder->setCheckable(true);
    ui->checkBox_Mining_MiningDriving->setCheckable(true);
    ui->checkBox_Mining_SetArmPosition1->setCheckable(true);
    ui->checkBox_Mining_SetCylinderTo0->setCheckable(true);
    ui->checkBox_Mining_StartCylinder->setCheckable(true);
    ui->checkBox_Mining_TensometerMass->setCheckable(true);
    ui->button_Mining_ArmPosition4->setEnabled(true);
    ui->button_Mining_CheckCylinderState->setEnabled(true);
    ui->button_Mining_ArmPositionTo1->setEnabled(true);
    ui->button_Mining_MiningDriving->setEnabled(true);
    ui->button_Mining_SetCylinderTo0->setEnabled(true);
    ui->button_Mining_StartCylinder->setEnabled(true);
    ui->button_Mining_Initiate->setDisabled(true);
    ui->button_Mining_TensometerMass->setEnabled(true);

    //disable unloading
    ui->checkBox_Unloading_CheckArmPosition->setCheckable(false);
    ui->checkBox_Unloading_CloseCylinder->setCheckable(false);
    ui->checkBox_Unloading_OpenCylinder->setCheckable(false);
    ui->checkBox_Unloading_RotateCylinder->setCheckable(false);
    ui->checkBox_Unloading_SetArmPosition1->setCheckable(false);
    ui->checkBox_Unloading_SetCylinderTo0->setCheckable(false);
    ui->checkBox_Unloading_ShakeCylinder->setCheckable(false);
    ui->button_Unloading_CheckArmPosition->setEnabled(false);
    ui->button_Unloading_CloseCylinder->setEnabled(false);
    ui->button_Unloading_Initiate->setEnabled(false);
    ui->button_Unloading_OpenCylinder->setEnabled(false);
    ui->button_Unloading_RotateCylinder->setEnabled(false);
    ui->button_Unloading_SetArmPosition1->setEnabled(false);
    ui->button_Unloading_SetCylinderTo0->setEnabled(false);
    ui->button_Unloading_ShakeCylinder->setEnabled(false);


}                           //30
void MainWindow::MiningCylinderState(){
    robot->MiningCylinderState(true);
    ui->checkBox_Mining_CloseCylinder->setChecked(true);

}           //31     ARG?
void MainWindow::MiningArmPosition4(){
    robot->MiningArmPosition4();
    ui->checkBox_Mining_ArmPosition4->setChecked(true);
}
//32
void MainWindow::MiningCylinderStart(){
    robot->MiningCylinderStart();
    ui->checkBox_Mining_StartCylinder->setChecked(true);
}
//33
void MainWindow::MiningCalibration() {
    robot->MiningCalibration();
}

//34
void MainWindow::MiningCylinderToGround(int w){
    robot->MiningCylinderToGround(w);
    ui->checkBox_Mining_SetCylinderTo0->setChecked(true);
}

     //36
void MainWindow::MiningDriving(){
    robot->MiningDriving();
    ui->checkBox_Mining_MiningDriving->setChecked(true);
}                            //37
void MainWindow::MiningTensometerMass(){
    robot->MiningTensometerMass();
    ui->checkBox_Mining_TensometerMass->setChecked(true);
}                     //38
void MainWindow::MiningArmPosition1(){
    robot->MiningArmPosition1();
    ui->checkBox_Mining_SetArmPosition1->setChecked(true);
    ui->button_Unloading_Initiate->setEnabled(true);
}                       //39

///UNLOAD SEQ
void MainWindow::UnloadInitiate(){
    //disable mining
    //uncheck boxes
    ui->checkBox_Mining_ArmPosition4->setCheckable(false);
    ui->checkBox_Mining_CloseCylinder->setCheckable(false);
    ui->checkBox_Mining_MiningDriving->setCheckable(false);
    ui->checkBox_Mining_SetArmPosition1->setCheckable(false);
    ui->checkBox_Mining_SetCylinderTo0->setCheckable(false);
    ui->checkBox_Mining_StartCylinder->setCheckable(false);
    ui->checkBox_Mining_TensometerMass->setCheckable(false);

    //disable buttons&checkes
    ui->button_Mining_CheckCylinderState->setEnabled(false);
    ui->button_Mining_Initiate->setEnabled(false);
    ui->button_Mining_MiningDriving->setEnabled(false);
    ui->button_Mining_SetCylinderTo0->setEnabled(false);
    ui->button_Mining_StartCylinder->setEnabled(false);
    ui->button_Mining_ArmPositionTo1->setEnabled(false);
    ui->button_Mining_ArmPosition4->setEnabled(false);
    ui->button_Mining_TensometerMass->setEnabled(false);

    //enable unloading
    ui->button_Unloading_CheckArmPosition->setEnabled(true);
    ui->button_Unloading_CloseCylinder->setEnabled(true);
    ui->button_Unloading_Initiate->setEnabled(true);
    ui->button_Unloading_OpenCylinder->setEnabled(true);
    ui->button_Unloading_RotateCylinder->setEnabled(true);
    ui->button_Unloading_SetArmPosition1->setEnabled(true);
    ui->button_Unloading_SetCylinderTo0->setEnabled(true);
    ui->button_Unloading_ShakeCylinder->setEnabled(true);

    ui->checkBox_Unloading_CheckArmPosition->setCheckable(true);
    ui->checkBox_Unloading_CloseCylinder->setCheckable(true);
    ui->checkBox_Unloading_OpenCylinder->setCheckable(true);
    ui->checkBox_Unloading_RotateCylinder->setCheckable(true);
    ui->checkBox_Unloading_SetArmPosition1->setCheckable(true);
    ui->checkBox_Unloading_SetCylinderTo0->setCheckable(true);
    ui->checkBox_Unloading_ShakeCylinder->setCheckable(true);

    //disable button
    ui->button_Mining_Initiate->setDisabled(true);
    ui->button_Unloading_Initiate->setDisabled(true);

}                           //40
void MainWindow::UnloadArmPosition1(){
    robot->UnloadArmPosition1();
    ui->checkBox_Unloading_SetArmPosition1->setChecked(true);
}                       //41
void MainWindow::UnloadCylinderToZero(int w){
    robot->UnloadCylinderToZero(w);
    ui->checkBox_Unloading_SetCylinderTo0->setChecked(true);
}             //42
void MainWindow::UnloadCylinderOpen(){
    robot->UnloadCylinderOpen();
    ui->checkBox_Unloading_OpenCylinder->setChecked(true);
    UnloadCylinderState(true);
}                       //43
void MainWindow::UnloadCylinderState(bool opened){
    robot->UnloadCylinderState(true);
}           //44
void MainWindow::UnloadCylinderShake(){
    robot->UnloadCylinderShake();
    ui->checkBox_Unloading_ShakeCylinder->setChecked(true);
}                      //45
void MainWindow::UnloadCylinderRotate(){
    double angle = ui->lineEdit_Unloading_CylinderAngle->text().toDouble();
    double w = ui->lineEdit_Unloading_CylinderSpeed->text().toDouble();
    robot->UnloadCylinderRotate(angle, w);
    ui->checkBox_Unloading_RotateCylinder->setChecked(true);
}//46
void MainWindow::UnloadCylinderClose(){
    robot->UnloadCylinderClose();
    ui->checkBox_Unloading_CloseCylinder->setChecked(true);
}                      //47
void MainWindow::UnloadArmPositionCheck(){
    robot->UnloadArmPositionCheck();
    ui->checkBox_Unloading_CheckArmPosition->setChecked(true);

    //disable unloading
    ui->button_Unloading_CheckArmPosition->setEnabled(false);
    ui->button_Unloading_CloseCylinder->setEnabled(false);
    ui->button_Unloading_Initiate->setEnabled(false);
    ui->button_Unloading_OpenCylinder->setEnabled(false);
    ui->button_Unloading_RotateCylinder->setEnabled(false);
    ui->button_Unloading_SetArmPosition1->setEnabled(false);
    ui->button_Unloading_SetCylinderTo0->setEnabled(false);
    ui->button_Unloading_ShakeCylinder->setEnabled(false);

    ui->checkBox_Unloading_CheckArmPosition->setCheckable(false);
    ui->checkBox_Unloading_CloseCylinder->setCheckable(false);
    ui->checkBox_Unloading_OpenCylinder->setCheckable(false);
    ui->checkBox_Unloading_RotateCylinder->setCheckable(false);
    ui->checkBox_Unloading_SetArmPosition1->setCheckable(false);
    ui->checkBox_Unloading_SetCylinderTo0->setCheckable(false);
    ui->checkBox_Unloading_ShakeCylinder->setCheckable(false);

    //disable button
    ui->button_Mining_Initiate->setDisabled(false);

}                   //48    ARG?

///SECURITY SEQ
void MainWindow::SecurityAllEnginesStop(){
    robot->SecurityAllEnginesStop();
}                   //101
void MainWindow::SecurityDrivingEnginesStop(){
    robot->SecurityDrivingEnginesStop();
}               //102
void MainWindow::SecurityArmEngineStop(){
    robot->SecurityArmEngineStop();
}                    //103
void MainWindow::SecurityCylinderEngineStop(){
    robot->SecurityCylinderEngineStop();
}               //104
void MainWindow::SecurityAutonomy(){
    robot->SecurityAutonomy();
}                         //105

void MainWindow::MiningLaunchAll(){
    robot->MiningLaunchAll();
}

void MainWindow::UnloadLaunchAll(){
    robot->UnloadLaunchAll();
}

void MainWindow::updateJoystick(){
    //0 - forward, 1-turn
    robot->BasicDriveForward((joy->getAxis(1))*0.2/-32767, 0.2);
    robot->BasicDriveForward((joy->getAxis(3))*0.2/-32767, 0.2);
    robot->BasicDriveForward((joy->getAxis(5))*0.2/-32767, 0.2);

    robot->BasicTurn((double)(joy->getAxis(0))*15/-32767, 0.2);
    robot->BasicTurn((double)(joy->getAxis(2))*15/-32767, 0.2);
    robot->BasicTurn((double)(joy->getAxis(4))*15/-32767, 0.2);

}

}
