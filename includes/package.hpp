#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <QtCore>

#define J_TOTAL	"total"
#define J_CUR	"current"
#define J_STAMP	"timestamp"
#define J_TEXT	"text"

class QJsonDocument;
class QJsonValue;
class QJsonObject;
// class QJsonArray;

class Package {
	public:
		Package();
		Package(int t, int cur, const QString &tm, const QByteArray &msg);
		~Package();
		const QByteArray	zip();
		int					unzip(const QByteArray &data);
		int					getTotal();
		int					getCurrent();
		QString				getTimestamp();
		QByteArray			getText();

	private:
		int					total;
		int					current;
		QString				timestamp;
		QByteArray			text;
};

struct Message {
	quint16		sender;
	int			packs;
	QString		timestamp;
	QByteArray	text;
};

#endif
