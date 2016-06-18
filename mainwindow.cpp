#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//TODO add button to recreate color
	//TODO add button to select/unselect all items
	starttime = QDateTime::currentDateTime().toTime_t();
	ui->plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));

	ui->plot->setInteraction(QCP::iSelectPlottables,true);
	ui->plot->setInteraction(QCP::iMultiSelect,true);
	ui->plot->setInteraction(QCP::iRangeDrag,true);
	ui->plot->setInteraction(QCP::iRangeZoom,true);
	ui->plot->xAxis->axisRect()->setRangeDrag(Qt::Horizontal);
	ui->plot->yAxis->axisRect()->setRangeDrag(Qt::Horizontal);
	ui->plot->xAxis->axisRect()->setRangeZoom(Qt::Horizontal);
	ui->plot->yAxis->axisRect()->setRangeZoom(Qt::Horizontal);
	
	// bottom axis shows time
	ui->plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
	ui->plot->xAxis->setDateTimeFormat("HH:mm:ss");//dd.MM\n
	// set a more compact font size for bottom and left axis tick labels:
	ui->plot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
	ui->plot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
	// set a fixed tick-step to one tick per month:
	ui->plot->xAxis->setAutoTickStep(true);
	//ui->plot->xAxis->setAutoTicks(true);
	//ui->plot->xAxis->setAutoTickLabels(false);
	ui->plot->xAxis->setTickStep(60); // one month in seconds
	ui->plot->xAxis->setSubTickCount(3);
	// apply manual tick and tick label for left axis:
	ui->plot->yAxis->setAutoTicks(true);
	//ui->plot->yAxis->setTickStep(10);
	//ui->plot->yAxis->setSubTickCount(3);
	ui->plot->yAxis->setAutoTickLabels(true);
	//ui->plot->yAxis->setTickVector(QVector<double>() << 0 << 2);
	//ui->plot->yAxis->setTickVectorLabels(QVector<QString>() << "Not so\nhigh" << "Very\nhigh");
	// set axis labels:
	ui->plot->xAxis->setLabel("Time");
	ui->plot->yAxis->setLabel("Number");
	// make top and right axes visible but without ticks and labels:
	ui->plot->xAxis2->setVisible(true);
	ui->plot->yAxis2->setVisible(true);
	ui->plot->xAxis2->setTicks(false);
	ui->plot->yAxis2->setTicks(false);
	ui->plot->xAxis2->setTickLabels(false);
	ui->plot->yAxis2->setTickLabels(false);
	// set axis ranges to show all data:
	ui->plot->xAxis->setRange(starttime, starttime+600);
	//ui->plot->xAxis->setRange(0, 600);
	//ui->plot->xAxis->setRangeLower(starttime);
	ui->plot->yAxis->setRange(0, 60);
	// show legend:
	ui->plot->legend->setVisible(true);
	//test code
	//getGraph("player")->addData(starttime,1);
	//getGraph("player")->addData(starttime+1,2);
	//getGraph("player")->addData(starttime+3,3);
	//getGraph("player")->addData(starttime+4,4);
	//getGraph("player")->addData(starttime+5,5);
	//ui->plot->replot();
}

QCPGraph* MainWindow::getGraph(QString const& graphName/*,int &graphIndex*/){
	QCPGraph* graph;
	for (int var = 0; var < ui->plot->graphCount(); ++var) {
		graph = ui->plot->graph(var);
		if (graph->name().contains(graphName)){
			//graphIndex = var;
			return graph;
		}
	}
	//graph not found so create a new one
	ui->plot->addGraph();
	//graphIndex = ui->plot->graphCount();
	QPen pen;
	pen.setColor(QColor(rand() % 255 ,rand() % 255,rand() % 255));//QColor(0, 0, 255, 200)
	pen.setWidth(1);
	pen.setStyle(Qt::SolidLine);
	QColor invert = pen.color();
	invert.setAlpha(255);
	qDebug() << pen.color();
	ui->plot->graph()->setLineStyle(QCPGraph::lsLine);//lsLine
	ui->plot->graph()->setPen(pen);
	ui->plot->graph()->setName(graphName);
	//ui->plot->graph()->setBrush(QBrush(invert));
	QCPScatterStyle myScatter;
	myScatter.setShape(QCPScatterStyle::ssCross);
	myScatter.setPen(pen);
	myScatter.setBrush(Qt::white);
	myScatter.setSize(5);
	pen.setStyle(Qt::SolidLine);
	ui->plot->graph()->setSelectedPen(pen);
	ui->plot->graph()->setSelectedBrush(QBrush(QColor(255,0,0,150)));
	//ui->plot->graph()->setScatterStyle(myScatter);
	ui->plot->graph()->setVisible(true);
	ui->plot->graph()->setSelectable(true);
	qDebug() << "addGraph" << graphName;

	//QListWidgetItem* item = new QListWidgetItem(name);
	//item->setBackgroundColor(pen.color());
	//invert = pen.color().toHsv();
	//invert.fromHsv(360-invert.hue(),invert.saturation(),invert.alpha());
	//item->setTextColor(
	//			QColor::fromHsv(360-invert.hue(),invert.saturation(),invert.alpha()));
	//item->setCheckState(Qt::Unchecked);
	//item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
	//ui->listWidget->addItem(item);
	return ui->plot->graph();

	// Add graph with checkbox to listview and color listview entry corresponding to graph color
}

void MainWindow::gotData(ARMA_SERVER_INFO data)
{
	auto timestamp = QString::number(QDateTime::currentDateTime().toTime_t()).toDouble();

	//qDebug() << "dataIn" << timestamp;

	QCPGraph* graphPlayerCount = getGraph("player");
	QCPGraph* graphAILocal = getGraph("ailocal");
	QCPGraph* graphAIRemote = getGraph("airemote");
	QCPGraph* graphSFPS = getGraph("sfps");
	QCPGraph* graphScps = getGraph("scps");
	//QCPGraph* graphPlayerCount = getGraph("pcount",index);
	graphPlayerCount->addData(timestamp,data.PLAYER_COUNT);
	graphPlayerCount->setName("player ("+QString::number(data.PLAYER_COUNT)+")");
	graphAILocal->addData(timestamp,data.AI_LOC_COUNT);
	graphAILocal->setName("ailocal ("+QString::number(data.AI_LOC_COUNT)+")");
	graphAIRemote->addData(timestamp,data.AI_REM_COUNT);
	graphAIRemote->setName("airemote ("+QString::number(data.AI_REM_COUNT)+")");
	graphSFPS->addData(timestamp,data.SERVER_FPS/1000);
	graphSFPS->setName("sfps ("+QString::number(data.SERVER_FPS/1000)+")");
	graphScps->addData(timestamp,data.FSM_CE_FREQ/1000);
	graphScps->setName("scps ("+QString::number(data.FSM_CE_FREQ/1000)+")");
	ui->label_Mission->setText(QStringLiteral("Mission:") + data.MISSION);

	ui->plot->replot();

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_button_connect_clicked()
{
	connect(&asmc,&asmConnector::gotData,this,&MainWindow::gotData);
	asmc.init(ui->edit_SocketAddress->text());
}
