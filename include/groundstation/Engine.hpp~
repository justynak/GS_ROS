/// |-------------------------------------------------------------------------------------------|
/// |                                                                                           |
/// |               Class Engine - describes the typical DC engine: it contains:                |
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


#ifndef ENGINE_H
#define ENGINE_H
#include <unistd.h>
#include <climits>
#include <iostream>
#include <cmath>
#include <QObject>


class Engine
{

    public:

        ///ctor: voltage, angular velocity, position and direction: 0 for cw
        Engine(double V=1, double W=100, double v=0, double w=0, int pos=0, bool cw=0) : md_voltage(v), md_anvelocity(w), md_position(0), mb_direction(true) {};
        virtual ~Engine();

        double GetVoltage() { return md_voltage; }
        void SetVoltage(double val=0) { md_voltage = val; } //set voltage

        double GetAnVelocity() { return md_anvelocity; }
        ///Set the angular velocity of the engine
        void SetAnVelocity(double val=0, double time=0.2) { md_anvelocity = val; }


        int GetPosition() { return md_position; }
        void SetPosition(double a=0, double w=1000); //


        bool GetDirection() { return mb_direction; }
        ///Set the direction: 0 for CW, 1 for CCW
        void SetDirection(bool val=true) { mb_direction = val; }

        double GetMaxVoltage(){return md_maxvoltage;}
        void SetMaxVoltage(double V){md_maxvoltage=V;}

        double GetMaxAnVelocity(){return md_maxanvelocity;}
        void SetMaxAnVelocity(double W){md_maxanvelocity=W;}

        double GetMaxCurrent(){return md_maxcurrent;}
        void SetMaxCurrent(double Imax){md_maxcurrent=Imax;}

        double GetCurrent(){return md_current;}
        double SetCurrent(double I){md_current=I;}

        void Stop(){
            md_anvelocity=0;
        }

    private:
        double md_voltage;
        double md_maxvoltage;

        double md_anvelocity;
        double md_maxanvelocity;

        double md_maxcurrent;
        double md_current;


        ///between 0 and 359
        double md_position;
        bool mb_direction;
};

#endif // ENGINE_H
