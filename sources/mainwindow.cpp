#include "../includes/mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	initGui();
}

MainWindow::~MainWindow() {
	delete textBrw;
	delete textEdt;
	delete btnSend;
	delete btnConnect;
	delete lnClient;
	delete lnSend;
	delete lbClient;
	delete lbSendto;
}

void MainWindow::clickSend() {
	textBrw->append("Some text here");
	statusBar()->showMessage("\"Send\" clicked", 2000);
	textEdt->clear();
}

void MainWindow::clickConnecting() {
	statusBar()->showMessage("\"Connecting\" clicked", 2000);
}

void MainWindow::initGui() {
	setWindowTitle("Client");
	setGeometry(0,0,800,600);
	statusBar();

	// Label "Client"
	lbClient = new QLabel("Client", this);
	lbClient->setAlignment(Qt::AlignCenter);
	lbClient->setGeometry(700, 10, 100, 20);

	// LineEdit to client port
	lnClient = new QLineEdit(this);
	lnClient->setGeometry(710, 30, 80, 20);

	// Button "Connecting"
	btnConnect = new QPushButton(tr("Connecting"), this);
	btnConnect->setGeometry(710, 60, 80, 20);
	connect(btnConnect, &QPushButton::clicked, this, &MainWindow::clickConnecting);

	// Label "Send to"
	lbSendto = new QLabel("Send to", this);
	lbSendto->setAlignment(Qt::AlignCenter);
	lbSendto->setGeometry(700, 100, 100, 20);

	// LineEdit to send message
	lnSend = new QLineEdit(this);
	lnSend->setGeometry(710, 130, 80, 20);

	// Button "Send"
	btnSend = new QPushButton(tr("Send"), this);
	btnSend->setGeometry(710, 540, 80, 50);
	connect(btnSend, &QPushButton::clicked, this, &MainWindow::clickSend);

	// TextBrowser to show
	textBrw = new QTextBrowser(this);
	textBrw->setGeometry(10, 10, 690, 500);

	// TextEditor to write message
	textEdt = new QTextEdit(this);
	textEdt->setGeometry(10, 540, 690, 50);
}
