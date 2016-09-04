#include "httpserver.h"

#include <QDateTime>

HttpServer::HttpServer(QObject *parent) :
    QObject(parent),
    m_server(new QTcpServer(this))
{
    m_server->listen(QHostAddress::Any, 8080);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void HttpServer::newConnection()
{
    if (m_server->hasPendingConnections()) {
        QTcpSocket *socket = m_server->nextPendingConnection();
        QString response, responseHeader, responseBody;
        QString timestamp = QDateTime::currentDateTime().toString("ddd, dd MMM yyyy hh:mm:ss") + " GMT";
        QTextStream responseStream(&response, QIODevice::WriteOnly);
        QTextStream responseHeaderStream(&responseHeader, QIODevice::WriteOnly);
        QTextStream responseBodyStream(&responseBody, QIODevice::WriteOnly);
        responseBodyStream << "<html>" << "\n"
                           << "<head>" << "\n"
                           << "<title>Welcome to Qt HTTP Server!</title>" << "\n"
                           << "</head>" << "\n"
                           << "<body>" << "\n"
                           << "<h1>It works!</h1>" << "\n"
                           << "</body>" << "\n"
                           << "</html>";
        responseHeaderStream << "HTTP/1.1 200 OK" << "\r\n"
                             << "Date: " << timestamp << "\r\n"
                             << "Connection: close" << "\r\n"
                             << "Server: My Qt HTTP Server" << "\r\n"
                             << "Accept-Ranges: bytes" << "\r\n"
                             << "Content-Type: text/html" << "\r\n"
                             << "Content-Length: " << responseBody.length() << "\r\n"
                             << "Last-Modified: " << timestamp << "\r\n";
        responseStream << responseHeader << "\r\n" << responseBody;
        socket->write(response.toUtf8());
        socket->close();
    }
}
