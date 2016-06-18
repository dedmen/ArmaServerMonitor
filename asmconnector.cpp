#include "asmconnector.h"

asmConnector::asmConnector(QObject *parent) : QObject(parent)
{

}

asmConnector::~asmConnector()
{

}

void asmConnector::init()
{
	connect(&sock,&QTcpSocket::readyRead,this,&asmConnector::readyRead);
	sock.connectToHost("arma.dedmen.de",24000);
	connect(&timer,&QTimer::timeout,this,&asmConnector::requestData);
	timer.setInterval(1000);
	timer.start();
	//qDebug() << "init" << sock.state();
}

void asmConnector::disconnect()
{
	sock.disconnectFromHost();
}

void asmConnector::readyRead()
{
	QByteArray data = sock.readAll();
	if (data.length() < 130)
		return;

	ARMA_SERVER_INFO *dt = (struct ARMA_SERVER_INFO*) data.data();
	emit gotData(*dt);//I hope this copies


}

void asmConnector::requestData()
{
	//qDebug() << "request" << sock.state();
	sock.write("\0\0\0\0",4);
}

