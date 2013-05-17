#include "../include/groundstation/IDrivingSystem.hpp"
#include <cmath>

namespace groundstation{

IDrivingSystem::IDrivingSystem(){}
IDrivingSystem::~IDrivingSystem(){}

void IDrivingSystem::Drive(double v, double t){} //
void IDrivingSystem::Turn(double angle, double t){} //
void IDrivingSystem::GoForward(double s){}
void IDrivingSystem::SetPosition(double da, double ds){} //
void IDrivingSystem::SetPosition(double* p){} //

}
