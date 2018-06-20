#ifndef XMLACCOUNTSPARSER_H
#define XMLACCOUNTSPARSER_H

#include<QApplication>
#include<QString>
#include<QIODevice>
#include<QFile>
#include<QTextStream>
#include<QVariant>
#include<QXmlStreamReader>
#include<QXmlStreamWriter>
#include<QDebug>
#include<QMessageBox>

#include"XMLParser.h"
#include"Account.h"
#include"AccountsContainer.h"

class XMLAccountsParser: public XMLParser {
private:
    QXmlStreamReader* rdr;
    QXmlStreamWriter* wrt;

    void open4reading() override;
    void open4writing() override;
    void readAccount();
    void errorHandler(QString errstr);
public:
    XMLAccountsParser();
    bool parseXML() override;
    bool writeXML() override;
    ~XMLAccountsParser() override;
};

#endif // XMLACCOUNTSPARSER_H
