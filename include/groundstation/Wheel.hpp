/// |------------------------------------------------------------------------------------------------|
/// |                                                                                                |
/// |               Class Wheel - describes the driving wheel powered by the engine. It has:         |
/// |           *Radius                                                                              |
/// |           *Current angular velocity                                                            |
/// |           *its own engine                                                                      |
/// -------------------------------------------------------------------------------------------------|
/// |               The Wheel can:                                                                   |
/// |           *return the currrent values (described above)                                        |
/// |           *be set to turn with the given angular velocity                                      |
/// |           *Avoid obstacles on the way to and from lunabins and mining spot                     |
/// |------------------------------------------------------------------------------------------------|



#ifndef WHEEL_H
#define WHEEL_H

#include <QWidget>
#include "Engine.hpp"


///Wheel's radius
#define R 0.3
namespace groundstation{
class Wheel
{
    public:
        Wheel(double w=0, double r=0.3) : md_angVelocity(w), md_radius(r), m_engine(Engine()) {} ;
        virtual ~Wheel(){}
        double GetVelocity() {return md_angVelocity;}
        double GetRadius() {return md_radius;}


        void SetAngularVelocity(double val=0) { md_angVelocity = val;}
        double GetAngularVelocity(){return md_angVelocity;}

        double SetEngineSpeed(double w){m_engine.SetAnVelocity(w);}
        double SetEngineVoltage(double U){m_engine.SetVoltage(U);}
        double SetEngineMaxVoltage(double Umax){m_engine.SetMaxVoltage(Umax);}
        double SetEngineCurrent(double I){m_engine.SetCurrent(I);}
        double SetEngineMaxCurrent(double Imax){m_engine.SetMaxCurrent(Imax);}
        double SetEngineDirection(bool dir){m_engine.SetDirection(dir);}

        double GetEngineVoltage(){return m_engine.GetVoltage();}
        double GetEngineCurrent(){return m_engine.GetCurrent();}
        double GetEngineSpeed(){return m_engine.GetAnVelocity();}

        void Stop(){m_engine.Stop();}


    protected:
    private:
        double md_angVelocity;
        double md_radius;
        Engine m_engine;
};

}

#endif // WHEEL_H
