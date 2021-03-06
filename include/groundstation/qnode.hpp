/**
 * @file /include/groundstation/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef groundstation_QNODE_HPP_
#define groundstation_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/String.h>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace groundstation {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);
	void GSCallback(const std_msgs::String::ConstPtr& msg);

signals:
	void loggingUpdated();
        void rosShutdown();

private:
	int init_argc;
	char** init_argv;
	ros::Subscriber robot_subscriber;
        QStringListModel logging_model;


};

}  // namespace groundstation

#endif /* groundstation_QNODE_HPP_ */
