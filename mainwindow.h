#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "asmconnector.h"
#include "qcustomplot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		asmConnector asmc;
		quint64 starttime;
		QCPGraph* getGraph(QString const& graphName/*,int &graphIndex*/);
		void gotData(ARMA_SERVER_INFO data);
	private slots:
		void on_button_connect_clicked();

	private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
