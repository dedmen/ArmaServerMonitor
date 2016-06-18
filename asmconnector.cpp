#include "asmconnector.h"

asmConnector::asmConnector(QObject *parent) : QObject(parent)
{

}

asmConnector::~asmConnector()
{

}

void asmConnector::init(QString const& socketAddress)
{
	connect(&sock,&QTcpSocket::readyRead,this,&asmConnector::readyRead);
	auto addressParts = socketAddress.split(':');
	if (addressParts.size() != 2)
		return;
	sock.connectToHost(addressParts.first(), addressParts[1].toInt());
	connect(&timer,&QTimer::timeout,this,&asmConnector::requestData);
	timer.setInterval(1000);
	timer.start();
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

	ARMA_SERVER_INFO *dt = reinterpret_cast<ARMA_SERVER_INFO*>(data.data());
	emit gotData(*dt);//I hope this copies
}

void asmConnector::requestData()
{
	//qDebug() << "request" << sock.state();
	sock.write("\0\0\0\0",4);
}

