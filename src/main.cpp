/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "../include/groundstation/mainwindow.hpp"
#include "../include/groundstation/scada.hpp"
#include "../include/groundstation/Robot.hpp"
#include  "../include/groundstation/qnode.hpp"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    groundstation::Robot* Robot = new groundstation::Robot(0,0,0);

    groundstation::MainWindow w;
    w.robot = Robot;
    w.initialize();

    groundstation::SCADA s(argc, argv);
    s.robot=Robot;

    s.initialize();
    w.show();
    s.show();    //app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    //int result = app.exec();

    groundstation::QNode node(argc, argv);
    node.init();
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("robot", 1000, &groundstation::QNode::GSCallback, &node);
    //node.init();
    //node.run();

    return app.exec();
}
