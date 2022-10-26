#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <limits>

#define DEFAULT_PACKAGE_SIZE	100
#define DEFAULT_FREQUENCY		0

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
		QTextEdit		*msgField;
		QPushButton		*btnSend;
		QPushButton		*btnConnect;
		QLineEdit		*lnClient;
		QLineEdit		*lnSend;
		QLineEdit		*lnPackagesize;
		QLineEdit		*lnFrequency;
		QLabel			*lbClient;
		QLabel			*lbSendto;
		QLabel			*lbSettings;
		void			clickSend();
		void			clickConnecting();
		void			initGui();
		QUdpSocket		*udpSocket;
		quint16			portListn;
		quint16			portSend;
		int				checkClientPort();
		int				bindPort();
		void			readDatagrams();
		int				checkConnect();
		int				checkSendPort();
		void			sendMsg();
		int				emptyMsg();
		void			packManager(const QString &msg);
		int				packageSize;
		int				checkPackageSize(const QString &size);
		int				frequency;
};

#endif
