#ifndef QTKJOSNRPC_H
#define QTKJOSNRPC_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>

class qtkJosnRpc : public QObject
{
    Q_OBJECT
    enum errorCodes
    {
        jsrParseError = -32700,
        jsrInvalidRequest = -32600,
        jsrMethodNotFound = -32601,
        jsrInvalidParams = -32602,
        jsrInternalError = -32603
     };

public:
    explicit qtkJosnRpc(quint32 id, QObject *parent = 0);
    void setMethodKey(QString method);
    void setMethodParams(QString json);
    void setResultParams(QString json);
    void setError(quint32 code);
    void setError(quint32 code, QString message);
    QByteArray getJsonString();


private:
    QString getStandardErrorString(quint32 error);
    QJsonObject m_jsonRoot;


signals:

public slots:
};

#endif // QTKJOSNRPC_H
