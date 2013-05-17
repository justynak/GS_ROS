/// |------------------------------------------------------------------------------------------------|
/// |                                                                                                |
/// |               Class IDiggingSystem - describes the driving system of the Lunabot: it contains: |
/// |           *Cylinder                                                                            |
/// |           *Arm                                                                                 |
/// -------------------------------------------------------------------------------------------------|
/// |               The DiggingSystem can                                                            |
/// |           *Dig the material                                                                    |
/// |           *Drop the material to the lunabin                                                    |
/// |                                                                                                |
/// |------------------------------------------------------------------------------------------------|


#ifndef IDIGGINGSYSTEM_H
#define IDIGGINGSYSTEM_H

#include "Cylinder.hpp"
#include "Arm.hpp"
#include <QObject>

namespace groundstation{

class IDiggingSystem: public QObject
{
    Q_OBJECT
    public:
        explicit IDiggingSystem(QObject* parent=0);
        virtual ~IDiggingSystem();
        virtual void Dig();
        virtual void Drop();



    protected:
        Cylinder m_cylinder;
        Arm m_arm;
        bool mb_electromagnet;

signals:

};

}

#endif // IDIGGINGSYSTEM_H
