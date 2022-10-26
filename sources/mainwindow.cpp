#include "../includes/mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	initGui();
	frequency = DEFAULT_FREQUENCY;
	udpSocket = new QUdpSocket(this);
}

MainWindow::~MainWindow() {
	delete textBrw;
	delete msgField;
	delete btnSend;
	delete btnConnect;
	delete lnClient;
	delete lnSend;
	delete lbClient;
	delete lbSendto;
	delete lbSettings;
	delete lnPackagesize;
	delete lnFrequency;
	delete udpSocket;
}

void MainWindow::initGui() {
	setWindowTitle("Client");
	setGeometry(0, 0, 800, 600);
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
	btnConnect->setGeometry(710, 55, 80, 20);
	connect(btnConnect, &QPushButton::clicked, this, &MainWindow::clickConnecting);

	// Label "Send to"
	lbSendto = new QLabel("Send to", this);
	lbSendto->setAlignment(Qt::AlignCenter);
	lbSendto->setGeometry(700, 200, 100, 20);

	// LineEdit to receiver port
	lnSend = new QLineEdit(this);
	lnSend->setAlignment(Qt::AlignCenter);
	lnSend->setPlaceholderText("Receiver port");
	lnSend->setGeometry(710, 220, 80, 20);

	// Label "Settings"
	lbSettings = new QLabel("Settings", this);
	lbSettings->setAlignment(Qt::AlignCenter);
	lbSettings->setGeometry(700, 445, 100, 20);

	// LineEdit to packagesize
	lnPackagesize = new QLineEdit(this);
	lnPackagesize->setAlignment(Qt::AlignCenter);
	lnPackagesize->setPlaceholderText("package size");
	lnPackagesize->setGeometry(710, 465, 80, 20);

	// LineEdit to frequency
	lnFrequency = new QLineEdit(this);
	lnFrequency->setAlignment(Qt::AlignCenter);
	lnFrequency->setPlaceholderText("frequency");
	lnFrequency->setGeometry(710, 490, 80, 20);

	// Button "Send"
	btnSend = new QPushButton(tr("Send"), this);
	btnSend->setGeometry(710, 540, 80, 50);
	connect(btnSend, &QPushButton::clicked, this, &MainWindow::clickSend);

	// TextBrowser to show
	textBrw = new QTextBrowser(this);
	textBrw->setGeometry(10, 10, 690, 500);

	// TextEditor to write message
	msgField = new QTextEdit(this);
	msgField->setGeometry(10, 540, 690, 50);
}

void MainWindow::clickConnecting() {
	if (checkClientPort())
		if (bindPort()) {
			lnClient->setReadOnly(true);
			btnConnect->setText("Successful");
			btnConnect->setDisabled(true);
			connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readDatagrams);
			statusBar()->showMessage("Client running on port: " + lnClient->text(), 10000);
		}
}

int MainWindow::checkClientPort() {
	portListn = lnClient->text().toUShort();
	if (portListn > 1023 && portListn <= std::numeric_limits<quint16>::max())
		return 1;
	statusBar()->showMessage("Error: expected Client port from range 1024-65535");
	return 0;
}

int MainWindow::bindPort() {
	if (udpSocket->bind(QHostAddress::LocalHost, portListn))
		return 1;
	statusBar()->showMessage(QString("Error: port %1 is allready busy, try another port").arg(portListn));
	return 0;
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

void MainWindow::clickSend() {
	if (checkConnect())
		if (checkSendPort())
			sendMsg();
}

int MainWindow::checkConnect() {
	if (lnClient->isReadOnly())
		return 1;
	statusBar()->showMessage("Error: Client not connected");
	return 0;
}

int MainWindow::checkSendPort() {
	portSend = lnSend->text().toUShort();
	if (portSend > 1023 && portSend <= std::numeric_limits<quint16>::max())
		return 1;
	statusBar()->showMessage("Error: expected Recipient port from range 1024-65535");
	return 0;
}

void MainWindow::sendMsg() {
	if (emptyMsg()) {
		checkPackageSize(lnPackagesize->text());
		packManager(msgField->toPlainText());
		msgField->clear();
		statusBar()->showMessage("Message send", 5000);
	}
}

int MainWindow::emptyMsg() {
	if (msgField->toPlainText().isEmpty()) {
		statusBar()->showMessage("Message field is empty", 5000);
		return 0;
	}
	return 1;
}

int MainWindow::checkPackageSize(const QString &size) {
	if (size.isEmpty()) {
		packageSize = DEFAULT_PACKAGE_SIZE;
		return 1;
	}

	int tmpSize = size.toInt();
	if (tmpSize > 0) {
		packageSize = tmpSize;
		return 1;
	}

	statusBar()->showMessage("Error: expected package size value > 0 or empty field");
	return 0;
}

void MainWindow::packManager(const QString &msg) {
	QByteArray byteMsg = msg.toUtf8();
	int msgSize = msg.toUtf8().size();
	int packageNeed = (msgSize % packageSize != 0) ? (msgSize / packageSize + 1) : (msgSize / packageSize);
	textBrw->append(QString("to %1: ").arg(portSend) + msg);
	/*
	*** Debug mode
	*/
	qDebug() << "MSG:" << msgSize << "| PKSZ:" << packageSize << "| TOTAL:" << packageNeed;
	for (int i = 0; i < packageNeed; i++) {
		udpSocket->writeDatagram(byteMsg.mid(i * packageSize, packageSize), QHostAddress::LocalHost, portSend);
	}
	//udpSocket->writeDatagram(byteMsg, QHostAddress::LocalHost, portSend);
}
