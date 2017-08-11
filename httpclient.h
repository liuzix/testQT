#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <memory>
#include <vector>
#include <QString>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/NameValueCollection.h>
#include <Poco/Net/HTTPCookie.h>
#include <Poco/URI.h>

using namespace std;
using namespace Poco;
using namespace Poco::Net;

class HttpClient
{
private:
    unique_ptr<HTTPClientSession> sessionPtr;
    NameValueCollection cookies;

    void createSession(URI uri);
    void processCookies(HTTPResponse& resp);
public:
    HttpClient();
    QString get(QString url);

};

class HttpCookieManager {
private:
    vector<HTTPCookie> cookieArray;
public:
    void setCookies(vector<HTTPCookie>& cookies);
    NameValueCollection getCookies(URI uri);
};

#endif // HTTPCLIENT_H
