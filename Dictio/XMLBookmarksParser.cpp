#include "XMLBookmarksParser.h"

void XMLBookmarksParser::open4reading() {
    file->setFileName(qApp->applicationDirPath() + "/Risorse/Bookmarks.xml");
    if(file->exists()) qDebug() << "Source for reading Bookmarks does exist";
    else throw QString("Source for reading Bookmarks does not exist");
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw QString("Error while reading Bookmarks.xml\n") + file->errorString();
}

void XMLBookmarksParser::open4writing() {
    file->setFileName(qApp->applicationDirPath() + "/Risorse/Bookmarks.xml");
    if(file->exists()) qDebug() << "Source for writing Bookmarks does exist";
    else {
        qDebug() << "Source for writing Bookmarks does not exist, attempting to create";
        //Crea file xml standard vuoto
        QFile empty(qApp->applicationDirPath() + "/Risorse/Bookmarks.xml");
        if(empty.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&empty);
            stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
            stream << "<bookmarks>\n<\\bookmarks>";
        }
    }
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
        throw QString("Error while writing Bookmarks.xml\n") + file->errorString();
}

void XMLBookmarksParser::readBookmarks() {
    while(rdr->readNextStartElement()) {
        if(rdr->name() == "account") {
            Bookmarks tmp;
            rdr->readNextStartElement();
            if(rdr->name() == "username") {
                tmp.setData(0, rdr->readElementText());
            }
            else throw QString("Error while reading Bookmarks.xml:\nMissing username node at line ")
                    + QString::number(rdr->lineNumber());
            QStringList words;
            while(rdr->readNextStartElement()) {
                if(rdr->name() == "bookmark") {
                    words.append(rdr->readElementText());
                }
                else throw QString("Error while reading Bookmarks.xml:\nMissing bookmark node at line ")
                        + QString::number(rdr->lineNumber());
            }
            tmp.setData(1, QVariant(words));
            cont->insert(tmp);
        }
        else rdr->skipCurrentElement();
    }
}

void XMLBookmarksParser::errorHandler(QString errstr) {
    QMessageBox(QMessageBox::Warning, "Warning", errstr).exec();
}

XMLBookmarksParser::XMLBookmarksParser():
    XMLParser(new BookmarksContainer),
    rdr(new QXmlStreamReader),
    wrt(new QXmlStreamWriter)
{}

bool XMLBookmarksParser::parseXML() {
    try {
        open4reading();
        rdr->setDevice(file);

        if(rdr->readNextStartElement()) {
            if(rdr->name() == "bookmarks") readBookmarks();
            else throw QString("Error while reading Bookmarks.xml:\nMissing bookmarks node at line")
                    + QString::number(rdr->lineNumber());
        }

        if(rdr->hasError()) {
            throw QString("Error while reading Bookmarks.xml:\n") + rdr->errorString();
        }

        rdr->clear();
        closeFile();
        return true;
    }
    catch(QString errstr) {
        errorHandler(errstr);
        rdr->clear();
        closeFile();
        return false;
    }
}

bool XMLBookmarksParser::writeXML() {
    try {
        open4writing();
        wrt->setDevice(file);
        wrt->setAutoFormatting(true);
        wrt->writeStartDocument();
        wrt->writeStartElement("bookmarks");
        for(int i = 0; i < cont->size(); i++) {
            wrt->writeStartElement("account");
            wrt->writeTextElement("username", cont->getPtr(i)->getData(0).toString());
            QStringList words = cont->getPtr(i)->getData(1).toStringList();
            for(int j = 0; j < words.size(); j++) {
                wrt->writeTextElement("bookmark", words[j]);
            }
            wrt->writeEndElement();
        }
        wrt->writeEndElement();
        wrt->writeEndDocument();
        closeFile();
        return true;
    }
    catch(QString errstr) {
        errorHandler(errstr);
        closeFile();
        return false;
    }
}

XMLBookmarksParser::~XMLBookmarksParser() {
    delete rdr;
    delete wrt;
}
