#include "httpclient.h"

#include <iostream>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <QDebug>


void HttpClient::createSession(URI uri)
{
    if (sessionPtr) {
        if (sessionPtr->getHost() == uri.getHost())
            return;
    }

    HTTPClientSession* newSession;
    if (uri.getScheme() == "https") {
        newSession = new HTTPSClientSession(uri.getHost());
    } else {
        newSession = new HTTPClientSession(uri.getHost());
    }
    sessionPtr = unique_ptr<HTTPClientSession>(newSession);
    sessionPtr->setKeepAlive(true);
}

void HttpClient::processCookies(HTTPResponse &resp)
{
    vector<HTTPCookie> setCookies;
    resp.getCookies(setCookies);
    for (auto &cookie: setCookies) {
        cookies.add(cookie.getName(), cookie.getValue());
    }
}

HttpClient::HttpClient()
{

}

QString HttpClient::get(QString url)
{
    using namespace Poco;
    URI uri(url.toStdString());
    createSession(uri);

    auto path = uri.getPathAndQuery();
    if (path.empty()) path = "/";

    HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    req.setCookies(cookies);
    sessionPtr->sendRequest(req);

    HTTPResponse res;
    std::istream &is = sessionPtr->receiveResponse(res);
    qDebug() << url << "\n" << res.getStatus();
    processCookies(res);
    QByteArray buffer;
    char rawBuffer[1024];
    while (!is.eof()) {
        int bytesIn = is.read(rawBuffer, sizeof(rawBuffer)).gcount();
        buffer.append(rawBuffer, bytesIn);
    }

    return QString(buffer);
}

/*
 * Here starts HttpCookieManager
 * */

void HttpCookieManager::setCookies(vector<HTTPCookie> &cookies)
{
    cookieArray.insert(cookieArray.end(), cookies.begin(), cookies.end());

}
