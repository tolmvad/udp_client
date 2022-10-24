#include "../includes/mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	initGui();
	udpSocket = new QUdpSocket(this);
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
	delete udpSocket;
}

void MainWindow::clickSend() {
	if (lnClient->isReadOnly()) {
		portSend = lnSend->text().toUShort();
		if (portSend > 1023 && portSend < 65535) {
			udpSocket->writeDatagram(textEdt->toPlainText().toUtf8(), QHostAddress::LocalHost, portSend);
			textBrw->append(QString("to %1: ").arg(portSend) + textEdt->toPlainText());
			textEdt->clear();
			statusBar()->showMessage("Message send", 5000);
		} else {
			statusBar()->showMessage("Error: expected port from range 1024-65534", 10000);
		}
	} else {
		statusBar()->showMessage("Error: client not connected", 10000);
	}
}

void MainWindow::clickConnecting() {
	portListn = lnClient->text().toUShort();
	if (portListn > 1023 && portListn < 65535) {
		lnClient->setReadOnly(true);
		btnConnect->setText("Successful");
		btnConnect->setDisabled(true);
		statusBar()->showMessage("Client running on port: " + lnClient->text(), 5000);
		udpSocket->bind(QHostAddress::LocalHost, portListn);
		connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readDatagrams);
	} else {
		statusBar()->showMessage("Error: expected port from range 1024-65534", 10000);
	}
}

void MainWindow::readDatagrams() {
	QHostAddress	sender;
	quint16			senderPort;

	while (udpSocket->hasPendingDatagrams()) {
		QByteArray	datagram;

		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
		textBrw->append(QString("from %1: ").arg(senderPort) + QString(datagram));
	}
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
	lnClient->setAlignment(Qt::AlignCenter);
	lnClient->setPlaceholderText("Client port");
	lnClient->setGeometry(710, 30, 80, 20);

	// Button "Connecting"
	btnConnect = new QPushButton(tr("Connecting"), this);
	btnConnect->setGeometry(710, 60, 80, 20);
	connect(btnConnect, &QPushButton::clicked, this, &MainWindow::clickConnecting);

	// Label "Send to"
	lbSendto = new QLabel("Send to", this);
	lbSendto->setAlignment(Qt::AlignCenter);
	lbSendto->setGeometry(700, 100, 100, 20);

	// LineEdit to receiver port
	lnSend = new QLineEdit(this);
	lnSend->setAlignment(Qt::AlignCenter);
	lnSend->setPlaceholderText("Receiver port");
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
