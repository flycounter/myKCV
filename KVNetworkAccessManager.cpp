#include "KVNetworkAccessManager.h"

#include <QDebug>

#include "KVNetworkReply.h"

KVNetworkAccessManager::KVNetworkAccessManager(QObject *parent) :
	QNetworkAccessManager(parent)
{
	
}

QNetworkReply *KVNetworkAccessManager::createRequest(Operation op, const QNetworkRequest &req, QIODevice *outgoingData)
{
	QNetworkRequest request = req;
	request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.107 Safari/537.36");

	if(request.url().host() != "localhost")
	{
		if(op == QNetworkAccessManager::PostOperation)
		{
			qDebug() << "POST" << request.url().path();
			QNetworkReply *r = QNetworkAccessManager::createRequest(op, request, outgoingData);
			KVNetworkReply *reply = new KVNetworkReply(r->parent(), r, this);
			return reply;
		}
		else if(op == QNetworkAccessManager::GetOperation)
		{
			qDebug() << "GET" << request.url().path();
		}
	}

	QNetworkReply *reply = QNetworkAccessManager::createRequest(op, request, outgoingData);
	return reply;
}
