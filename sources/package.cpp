#include "../includes/package.hpp"

/*
*** JSON Packege struct
***
*** Total packages		total (int)
*** Current package		cur (int)
*** Timestamp			timestamp (qstring)
*** Message				text (qbytearray)
***
*/

Package::Package() {}

Package::Package(int t, int cur, const QString &s, const QByteArray &msg) : total(t), current(cur), timestamp(s), text(msg) {
	qDebug() << "TIME:" << timestamp << "| TOTAL:" << total << "| CUR: " << current << "| MSG: " << text;
}

Package::~Package() {}

int Package::getTotal() {
	return this->total;
}

int Package::getCurrent() {
	return this->current;
}

QString Package::getTimestamp() {
	return this->timestamp;
}

QByteArray Package::getText() {
	return this->text;
}

const QByteArray Package::zip() {
	QJsonObject jObj;

	jObj.insert(J_STAMP, QJsonValue::fromVariant(timestamp));
	jObj.insert(J_TOTAL, QJsonValue::fromVariant(total));
	jObj.insert(J_CUR, QJsonValue::fromVariant(current));
	jObj.insert(J_TEXT, QJsonValue::fromVariant(text));
	return QJsonDocument(jObj).toJson();
}

int Package::unzip(const QByteArray &data) {
	QJsonObject jObj = QJsonDocument::fromJson(data).object();
	timestamp = jObj.value(J_STAMP).toString();
	total = jObj.value(J_TOTAL).toInt();
	current = jObj.value(J_CUR).toInt();
	text = jObj.value(J_TEXT).toString().toUtf8();

	return 0;
}
