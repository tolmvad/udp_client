#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets>

class QPushButton;
class QTextBrowser;
class QTextEdit;
class QLineEditor;
class QLabel;

class MainWindow : public QMainWindow {
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	private:
		int				portSend;
		int				portListn;
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
};

#endif
