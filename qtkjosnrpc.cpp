#include "QDebug"
#include "qtkjosnrpc.h"

qtkJosnRpc::qtkJosnRpc(quint32 id, QObject *parent) : QObject(parent)
{
    this->m_jsonRoot["jsonrpc"] = "2.0";
    this->m_jsonRoot.insert(QString("id"),QJsonValue((int)id));
}

void qtkJosnRpc::setMethodKey(QString method)
{
    this->m_jsonRoot["method"] = method;
}

void qtkJosnRpc::setMethodParams(QString json)
{
    QJsonDocument params;
    QJsonParseError error;
    params = QJsonDocument::fromJson(json.toUtf8(), &error);

    if(error.error)
    {
        qDebug() << QString("[qtkJosnRpc] setMethodParams() error: %1,  offset: %2")
                    .arg(error.errorString())
                    .arg(error.offset);
        return;
    }

    if(params.isArray())
    {
        this->m_jsonRoot["params"] = params.array();
    }
    else if(params.isObject())
    {
        this->m_jsonRoot["params"] = params.object();
    }
    else if(params.isEmpty())
    {
        qDebug() << QString("[qtkJosnRpc] setMethodParams() error: Empty params?")
                    .arg(error.errorString())
                    .arg(error.offset);
    }
    else if(params.isNull())
    {
        qDebug() << QString("[qtkJosnRpc] setMethodParams() error: Null params?")
                    .arg(error.errorString())
                    .arg(error.offset);
    }
}

void qtkJosnRpc::setResultParams(QString json)
{
    QJsonDocument params;
    QJsonParseError error;
    params = QJsonDocument::fromJson(json.toUtf8(), &error);

    if(error.error)
    {
        qDebug() << QString("[qtkJosnRpc] setResultParams() error: %1,  offset: %2")
                    .arg(error.errorString())
                    .arg(error.offset);
        return;
    }

    if(params.isArray())
    {
        this->m_jsonRoot["result"] = params.array();
    }
    else if(params.isObject())
    {
        this->m_jsonRoot["result"] = params.object();
    }
    else if(params.isEmpty())
    {
        qDebug() << QString("[qtkJosnRpc] setResultParams() error: Empty params?")
                    .arg(error.errorString())
                    .arg(error.offset);
    }
    else if(params.isNull())
    {
        qDebug() << QString("[qtkJosnRpc] setResultParams() error: Null params?")
                    .arg(error.errorString())
                    .arg(error.offset);
    }
}

void qtkJosnRpc::setError(quint32 code)
{
    this->setError(code, this->getStandardErrorString(code));
}

void qtkJosnRpc::setError(quint32 code, QString message)
{
    QJsonObject error;
    error.insert(QString("code"),QJsonValue((int)code));
    error["message"] = message;
    this->m_jsonRoot["error"] = error;
}

QString qtkJosnRpc::getStandardErrorString(quint32 error)
{
    switch(error)
    {
        case jsrParseError: return QString("Parse error"); break;
        case jsrInvalidRequest: return QString("Invalid Request"); break;
        case jsrMethodNotFound: return QString("Method not found"); break;
        case jsrInvalidParams: return QString("Invalid params"); break;
        case jsrInternalError: return QString("Internal error"); break;
    default:
        break;
    }

    return QString("Unknown error string");
}

QByteArray qtkJosnRpc::getJsonString()
{
    QJsonDocument string;
    string.setObject(this->m_jsonRoot);
    return string.toJson();
}







