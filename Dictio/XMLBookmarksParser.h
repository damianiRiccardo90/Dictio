#ifndef XMLBOOKMARKSPARSER_H
#define XMLBOOKMARKSPARSER_H

#include<QApplication>
#include<QString>
#include<QIODevice>
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<QVariant>
#include<QMessageBox>
#include<QXmlStreamReader>
#include<QXmlStreamWriter>
#include<QStringList>

#include"XMLParser.h"
#include"Bookmarks.h"
#include"BookmarksContainer.h"

class XMLBookmarksParser: public XMLParser {
private:
    QXmlStreamReader* rdr;
    QXmlStreamWriter* wrt;

    void open4reading() override;
    void open4writing() override;
    void readBookmarks();
    void errorHandler(QString errstr);
public:
    XMLBookmarksParser();
    bool parseXML() override;
    bool writeXML() override;
    ~XMLBookmarksParser() override;
};

#endif // XMLBOOKMARKSPARSER_H
