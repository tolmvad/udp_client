#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets>
#include <QtNetwork>

class QPushButton;
class QTextBrowser;
class QTextEdit;
class QLineEditor;
class QLabel;
class QUdpSocket;
class QHostAddress;

class MainWindow : public QMainWindow {
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	private:
		QTextBrowser	*textBrw;
		QTextEdit		*textEdt;
		QPushButton		*btnSend;
		QPushButton		*btnConnect;
		QLineEdit		*lnClient;
		QLineEdit		*lnSend;
		QLabel			*lbClient;
		QLabel			*lbSendto;
		void			clickSend();
		void			clickConnecting();
		void			initGui();
		QUdpSocket		*udpSocket;
		quint16			portListn;
		quint16			portSend;
		void			readDatagrams();
};

#endif
