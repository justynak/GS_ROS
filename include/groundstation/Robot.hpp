/// |------------------------------------------------------------------------------------------------|
/// |                                                                                                |
/// |               Class Robot - describes the whole Lunabot, It contains:                          |
/// |           *Position [x, y, alpha]                                                              |
/// |           *Descend the methods from IDiggingSystem and IDriving system                         |                                                        |
/// -------------------------------------------------------------------------------------------------|
/// |               The DiggingSystem can                                                            |
/// |           *Do what both system are written for                                                 |
/// |           *Go to lunabin and to the mining spot                                                |
/// |           *Avoid obstacles on the way to and from lunabins and mining spot                     |
/// |           *Give its posiiton                                                                   |
/// |           *Go to a position                                                                    |
/// |------------------------------------------------------------------------------------------------|

#ifndef ROBOT_H
#define ROBOT_H

#include "IDiggingSystem.hpp"
#include "IDrivingSystem.hpp"
#include "battery.hpp"
#include <cstdlib>
#include <QPixmap>
#include <QObject>
#include <QTcpSocket>


enum STATE {BASIC, MINING, UNLOADING, AUTONOMY};

namespace groundstation{

class Robot : public IDiggingSystem, public IDrivingSystem
{

    Q_OBJECT
    public:
        ///Constructor: Robot ready to go in a position of (x,y,a)
        explicit Robot(double x=0, double y=0, double a=0, QObject *parent=0);

        void SetPosition(double da, double ds); //
        void SetPosition(double* p);
        double GetWheelVelocity(int i){return m_wheel[i].GetAngularVelocity();}
        POSITION GetArmPosition(){return(m_arm.GetPosition()) ;}
        double GetCylinderWeight(){return(m_cylinder.GetWeight()) ;}
        double GetEngineCurrent(int i){
            if(i==1) return m_cylinder.GetCurrent();
            if(i==2) return m_arm.GetEngineCurrent();
            if(i==3) return m_wheel[0].GetEngineCurrent();
            if(i==4) return m_wheel[1].GetEngineCurrent();
        }

        double GetEngineSpeed(int i){
            switch(i){
            case 1: return m_cylinder.GetEngineSpeed(); break;
            case 2: return m_arm.GetEngineSpeed(); break;
            case 3: return m_wheel[0].GetEngineSpeed(); break;
            case 4: return m_wheel[1].GetEngineSpeed(); break;
            }
        }
        double GetCylinderSpeed(){return m_cylinder.GetEngineSpeed();}
        double GetElectromagnet(){return m_cylinder.IsElectroMagnetOn();}
        double GetTensometer(){return tensometer[1];}
        void SetTensometer(double t){tensometer[1]=t;}
        double GetMass(){return m_cylinder.GetWeight();}
        bool IsTeleoperated(){if(state!=AUTONOMY) return false; else return true;}
        void SetMaxCurrentVoltage(double U, double I);
        virtual ~Robot(){}
        char* ReceiveFrame(int id);
        void SendFrame(int id, int arg1, int arg2, int arg3);

        STATE GetState(){return state;}
        void SetState(STATE st){state=st;}

        char* bl;

private:
        QTcpSocket* socket;
        double tensometer[2];
        STATE state;

signals:
       ////BASIC SEQ.
        void _BasicChangeValues();                       //1
        void _BasicEngineSteer(int i, double w);         //2 /////
        void _BasicEngineDrivingSteer(int i, double w);  //3
        void _BasicCylinderSetToZero(double w);          //4
        void _BasicArmPositionChange(POSITION pos);      //5
        void _BasicElectromagnetSet(bool on);            //6
        void _BasicDriveForward(double v, double t);     //7
        void _BasicTurn(double a, double t);             //8
        void _BasicTurnArc(bool dir1, bool dir3, double w1, double w2); //9    ARG?

        ///START SEQ.
        void _StartAll();                                //20

        ////MINING SEQ
        void _MiningInitiate();                          //30
        void _MiningCylinderState(bool opened);          //31        ARG?
        void _MiningArmPosition4();                      //32
        void _MiningCylinderStart();                     //33
        void _MiningCalibration() ;                      //34
        void _MiningCylinderToGround(double w);          //35
        void _MiningDriving();                           //37
        void _MiningTensometerMass();                    //38
        void _MiningArmPosition1();                      //39
        void _Mining_All_Launched();

        ///UNLOAD SEQ
        void _UnloadInitiate();                          //40
        void _UnloadArmPosition1();                      //41
        void _UnloadCylinderToZero(double w);            //42
        void _UnloadCylinderOpen();                      //43
        void _UnloadCylinderState(bool opened);             //44
        void _UnloadCylinderShake();                     //45 HARLEM SHAKE LEL
        void _UnloadCylinderRotate(double angle, double w);//46
        void _UnloadCylinderClose();                     //47
        void _UnloadArmPositionCheck();      //48    //position
        void _UnloadAllLaunched();

        ///SECURITY SEQ
        void _SecurityAllEnginesStop();                  //101
        void _SecurityDrivingEnginesStop();              //102
        void _SecurityArmEngineStop();                   //103
        void _SecurityCylinderEngineStop();              //104
        void _SecurityAutonomy();                        //105


public slots:
        ////BASIC SEQ.
         void BasicChangeValues();                        //1
         void BasicEngineSteer(int i, double w);          //2
         void BasicEngineDrivingSteer(int i, double w);   //3
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
         void MiningLaunchAll();

         ///UNLOAD SEQ
         void UnloadInitiate();                           //40
         void UnloadArmPosition1();                       //41
         void UnloadCylinderToZero(double w);             //42
         void UnloadCylinderOpen();                       //43
         void UnloadCylinderState(bool opened);           //44
         void UnloadCylinderShake();                      //45
         void UnloadCylinderRotate(double angle, double w);//46
         void UnloadCylinderClose();                      //47
         void UnloadArmPositionCheck();                   //48    ARG?
         void UnloadLaunchAll();

         ///SECURITY SEQ
         void SecurityAllEnginesStop();                   //101
         void SecurityDrivingEnginesStop();               //102
         void SecurityArmEngineStop();                    //103
         void SecurityCylinderEngineStop();               //104
         void SecurityAutonomy();                         //105

         void connected();
         void not_connected();
         ///
};

}

#endif // ROBOT_H
