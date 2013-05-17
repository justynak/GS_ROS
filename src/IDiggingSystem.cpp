#include "../include/groundstation/IDiggingSystem.hpp"

namespace groundstation{
using namespace Qt;
///assuming that a-for driving, angle=0, b-for dropping angle=45 , c-digging, angle=130
//enum POSITION {a=0, b=45, c=135};
IDiggingSystem::IDiggingSystem(QObject* parent){m_arm = Arm(); m_cylinder = Cylinder();}
IDiggingSystem::~IDiggingSystem() {}

void IDiggingSystem::Dig(){
    ///set the needed arm position
    m_arm.SetPosition(c);
    std::cout<<"Set arm position";
    ///start digging!

    m_cylinder.GetMaterial();

    std::cout<<"Got material";

    ///after move the arm to go
    m_arm.SetPosition(a);

    std::cout<<"\nI have successfully dug the desired amount of the material\n";

    }

void IDiggingSystem::Drop(){
    ///set the arm to the needed position
    m_arm.SetPosition(c);
    std::cout<<"set position";



    ///unload the matherial
    m_cylinder.Unload();

    std::cout<<"material unloaded";


    ///vibrate the cylinder
    m_cylinder.Vibrate();

    std::cout<<"vibrate";

    ///set arm to the previous position
    m_arm.SetPosition(a);


    std::cout<<"set position";
    std::cout<<"\nI have successfully unloaded the material to the lunabin\n";
}

}
