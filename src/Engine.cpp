/// |---------------------------------------------------------------------------------------------------------------|
/// |                               Here are the functions of the engine:                                           |
///                                             |
/// |                   -Do the opposite: voltage generates angular velocity                                        |
/// |                   -Move to an angular position, depending on the direction: clockwise or counter-clockwise    |
/// |---------------------------------------------------------------------------------------------------------------|

#include "../include/groundstation/Engine.hpp"

namespace groundstation{
void Engine::SetPosition(double a, double w){
        if (w==0){
            std::cout<<"Wrong angular velocity!!!\n";
            std::cin>>w;
        }

        double t=0;
        double da = a-this->GetPosition();

        if (this->GetDirection()){t = (da>0 ? da/w : (360-da)/w); }
        else { t=( da>0 ? (360-da)/w : da/w ); }


        this->md_position=a;
}


Engine::~Engine() {}

}
