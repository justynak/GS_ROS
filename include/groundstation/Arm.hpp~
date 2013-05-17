/// |-------------------------------------------------------------------------------------------|
/// |                                                                                           |
/// |               Class Arm - describes the typical DC engine: it contains:                |
/// |           *instantaneous values of voltage and angular velocity                           |
/// |           *the maximum voltage and angular velocity                                       |
/// |           *the angular position                                                           |
/// |           *direction to move clockwise or counter-clockwise                               |
/// --------------------------------------------------------------------------------------------|
/// |               The engine can:                                                             |
/// |           *be set to have a given voltage, velocity, position and direction               |
/// |           *transform given voltage to angular velocity and the opposite                   |
/// |           *turn to an angle depending on the current direction                            |
/// |-------------------------------------------------------------------------------------------|





#ifndef ARM_H
#define ARM_H

#include "Engine.hpp"

enum POSITION  {a=1,b=2,c=3, d=4};
namespace groundstation{
class Arm
{
    public:
        Arm(POSITION pos = a) : m_position(pos), m_engine(Engine()) {} ;
        virtual ~Arm(){}

        POSITION GetPosition() { return m_position; }
        void SetPosition(POSITION val=a);

        void SetEngineMaxCurrent(double Imax){m_engine.SetMaxCurrent(Imax);}
        double GetEngineMaxCurrent(){return m_engine.GetMaxCurrent();}

        void SetEngineMaxVoltage(double Umax){m_engine.SetMaxVoltage(Umax);}
        double GetMaxVoltage(){return m_engine.GetMaxVoltage();}

        void SetEngineCurrent(double I){ m_engine.SetCurrent(I);}
        double GetEngineCurrent(){return m_engine.GetCurrent();}

        void SetEngineVoltage(double U){ m_engine.SetVoltage(U);}
       double GetEngineVoltage(){return m_engine.GetVoltage();}

        void Stop(){m_engine.Stop();}

        void SetEngineSpeed(double w){m_engine.SetAnVelocity(w);}
        double GetEngineSpeed(){m_engine.GetAnVelocity();}

        void SetEngineDirection(bool dir){m_engine.SetDirection(dir);}
        bool GetEngineDirection(){return m_engine.GetDirection();}

    protected:
    private:
        POSITION m_position;
        Engine m_engine;
};


}
#endif // ARM_H
