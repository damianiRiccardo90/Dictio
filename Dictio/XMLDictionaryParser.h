#ifndef XMLDICTIONARYPARSER_H
#define XMLDICTIONARYPARSER_H

#include<QString>
#include<QIODevice>
#include<QApplication>
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QXmlStreamReader>
#include<QXmlStreamWriter>
#include<QMap>

#include"XMLParser.h"
#include"Term.h"
#include"LexicalCategory.h"
#include"DictionaryContainer.h"

class XMLDictionaryParser: public XMLParser {
private:
    QXmlStreamReader* rdr;
    QXmlStreamWriter* wrt;

    void open4reading() override;
    void open4writing() override;
    void readTerm();
    void errorHandler(QString errstr);
public:
    XMLDictionaryParser();
    bool parseXML() override;
    bool writeXML() override;
    ~XMLDictionaryParser() override;
};

#endif // XMLDICTIONARYPARSER_H
