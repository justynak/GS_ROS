/// |-------------------------------------------------------------------------------------------|
/// |                                                                                           |
/// |               Class Cylinder - describes the cylinder of the Lunabot: it contains:        |
/// |           *instantaneous value of weight                                                  |
/// |           *the maximum weight of the material                                             |
/// |           *the single ?load? of the material                                              |
/// |           *flaps which are on/off to unload material                                      |
/// |           *electromagnet on/off to get rid off the remains of the moondust                |
/// |           *its own engine                                                                 |
/// --------------------------------------------------------------------------------------------|
/// |               The cylinder can:                                                           |
/// |           *be set to have a values described above                                        |
/// |           *get the material of the given weight                                           |
/// |           *get the material until full                                                    |
/// |           *unload the material                                                            |
/// |           *vibrate to get rid off the moondust with electromagnets on                     |
/// |-------------------------------------------------------------------------------------------|







#ifndef CYLINDER_H
#define CYLINDER_H

#include "Engine.hpp"

///maximum weight
#define WEIGHT 10

///maximum weight of the material for one full move of the cylinder

namespace groundstation{
class Cylinder
{


protected:
private:
    double md_weight;
    double md_maxweight;
    double md_totalweight;

    bool mb_flap;
    bool mb_electromagnet;
    Engine m_engine;


    public:
        Cylinder(double weight=0.0, double maxweight=WEIGHT, bool flap=false, bool electro=false) : md_weight(weight), md_maxweight(maxweight), mb_flap(flap), mb_electromagnet(electro) {};
        virtual ~Cylinder(){}

        double GetWeight() { return md_weight; }
        double SetWeight(double w){md_weight=w;}
        bool IsCylinderFull() {if (md_weight==md_maxweight) return true; else return false;};

        ///Returns true if the flaps are open
        bool IsOpened() { return mb_flap; }
        ///Sets the flaps to be : open-> true
        void Open(bool val=true) { mb_flap = val; }

        ///Turns on/off the electromagnet
        void SetElectromagnet(bool val=false){mb_electromagnet = val;}
        ///Returns true if electromagnet is on
        bool IsElectroMagnetOn(){return mb_electromagnet;}

        double GetMaxWeight() {return md_maxweight;}

        void Empty() {md_weight = 0;}
        ///Vibrates the cylinder to get rid off the moon sand
        void Vibrate(); //move cylinder cw and ccw for 0.5 s

        ///Starts digging until reaches the weight of the material - implicitly until full
        void GetMaterial(double weight=WEIGHT);
        double GetEngineSpeed(){return m_engine.GetAnVelocity();}

        void SetEngineSpeed(double w){m_engine.SetAnVelocity(w);}

        ///unloads the material
        void Unload(double md_weight=0);

        void SetMaxVoltage(double V){m_engine.SetMaxVoltage(V);}
        double GetMaxVoltage(){return m_engine.GetCurrent();}

        void SetMaxCurrent(double I){m_engine.SetMaxCurrent(I);}
        double GetMaxCurrent(){return m_engine.GetMaxCurrent();}

        void SetVoltage(double V){m_engine.SetVoltage(V);}
        double GetVoltage(){return m_engine.GetVoltage();}

        void SetCurrent(double I){m_engine.SetCurrent(I);}
        double GetCurrent(){return m_engine.GetCurrent();}

        void AddMass(double w){md_totalweight+=w;}
        double GetCurrentMass(){return md_totalweight;}

        void Stop(){m_engine.Stop();}

        //void SetAngularVelocity(double val=0, double time=0.5) { md_angVelocity = val;}
        //double GetAngularVelocity(){return md_angVelocity;}


        double SetEngineDirection(bool dir){m_engine.SetDirection(dir);}
        double GetEngineDirection(){return m_engine.GetDirection();}


};

}

#endif // CYLINDER_H
