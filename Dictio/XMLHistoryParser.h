#ifndef XMLHISTORYPARSER_H
#define XMLHISTORYPARSER_H

#include<QApplication>
#include<QDebug>
#include<QString>
#include<QIODevice>
#include<QXmlStreamReader>
#include<QXmlStreamWriter>
#include<QFile>
#include<QTextStream>
#include<QDate>
#include<QTime>
#include<QVariant>
#include<QMessageBox>

#include"XMLParser.h"
#include"History.h"
#include"HistoryContainer.h"

class XMLHistoryParser: public XMLParser {
private:
    QXmlStreamReader* rdr;
    QXmlStreamWriter* wrt;

    void open4reading() override;
    void open4writing() override;
    void readHistory();
    void errorHandler(QString errstr);
public:
    XMLHistoryParser();
    bool parseXML() override;
    bool writeXML() override;
    ~XMLHistoryParser() override;
};

#endif // XMLHISTORYPARSER_H
