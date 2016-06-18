#ifndef ASMCONNECTOR_H
#define ASMCONNECTOR_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>
#define SMALSTRINGSIZE 32
struct ARMA_SERVER_INFO
{
		uint16_t	PID;
		uint16_t	OBJ_COUNT_0;
		uint16_t	OBJ_COUNT_1;
		uint16_t	OBJ_COUNT_2;
		uint16_t	PLAYER_COUNT;
		uint16_t	AI_LOC_COUNT;
		uint16_t	AI_REM_COUNT;
		uint16_t	SERVER_FPS;
		uint16_t	SERVER_FPSMIN;//49383 = 49,383 FPS
		uint16_t	FSM_CE_FREQ;
		uint32_t	MEM;
		uint32_t	NET_RECV;
		uint32_t	NET_SEND;
		uint32_t	DISC_READ;
		uint32_t	TICK_COUNT;
		char		MISSION[SMALSTRINGSIZE];
		char		PROFILE[SMALSTRINGSIZE];
};

class asmConnector : public QObject
{
		Q_OBJECT
	public:
		explicit asmConnector(QObject *parent = 0);
		~asmConnector();
		void init();
		void disconnect();
		QTcpSocket sock;
		QTimer timer;
	signals:
		void gotData(ARMA_SERVER_INFO);
	public slots:
		void readyRead();
		void requestData();
};

#endif // ASMCONNECTOR_H
