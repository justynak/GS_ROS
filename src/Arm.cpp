#include "../include/groundstation/Arm.hpp"

namespace groundstation{
///assuming that a-for driving, angle=0, b-for dropping angle=45 , c-digging, angle=130
//enum POSITION {a=0, b=45, c=135};

void Arm::SetPosition(POSITION val){
    if (Arm::GetPosition() == val)
        std::cout<<"Nothing to do!\n";
    else{
        if (Arm::GetPosition()==a){
            Arm::m_engine.SetDirection(0);
            Arm::m_engine.SetPosition(val==b ? 45 : 130 ); //

            }
        else if (Arm::GetPosition()==b){
            if (val==a){
                Arm::m_engine.SetDirection(1);
                Arm::m_engine.SetPosition(0);
            }
            else{
                Arm::m_engine.SetDirection(0);
                Arm::m_engine.SetPosition(130);
            }
        }

        else{
            Arm::m_engine.SetDirection(1);
            Arm::m_engine.SetPosition(val==b ? 45 : 0 );
        }
        std::cout<<"\nI have moved my arm to a position"<<val;
    }
    m_position=val;
}

}
