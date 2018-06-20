#include "XMLHistoryParser.h"

void XMLHistoryParser::open4reading() {
    file->setFileName(qApp->applicationDirPath() + "/Risorse/History.xml");
    if(file->exists()) qDebug() << "Source for reading History does exist";
    else throw QString("Source for reading History does not exist");
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw QString("Error while reading History.xml\n") + file->errorString();
}

void XMLHistoryParser::open4writing() {
    file->setFileName(qApp->applicationDirPath() + "/Risorse/History.xml");
    if(file->exists()) qDebug() << "Source for writing History does exist";
    else {
        qDebug() << "Source for writing History does not exist, attempting to create";
        //CREARE FILE XML STANDARD VUOTO
        QFile empty(qApp->applicationDirPath() + "/Risorse/History.xml");
        if(empty.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&empty);
            stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
            stream << "<history>\n<\\history>";
        }
    }
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
        throw QString("Error while writing History.xml\n") + file->errorString();
}

void XMLHistoryParser::readHistory() {
    while(rdr->readNextStartElement()) {
        if(rdr->name() == "account") {
            History tmp;
            rdr->readNextStartElement();
            if(rdr->name() == "username") {
                tmp.setData(0, rdr->readElementText());
            }
            else throw QString("Error while reading History.xml:\nMissing username node at line ")
                    + QString::number(rdr->lineNumber());
            rdr->readNextStartElement();
            if(rdr->name() == "word") {
                tmp.setData(1, rdr->readElementText());
            }
            else throw QString("Error while reading History.xml:\nMissing word node at line ")
                    + QString::number(rdr->lineNumber());
            rdr->readNextStartElement();
            if(rdr->name() == "date") {
                QString date = rdr->readElementText();
                QString year = date.section('/', 2, 2);
                QString month = date.section('/', 1, 1);
                QString day = date.section('/', 0, 0);
                tmp.setData(2, QDate(2000 + year.toInt(), month.toInt(), day.toInt())); //Aggiornare quando arriverà il XXXI secolo
            }
            else throw QString("Error while reading History.xml:\nMissing date node at line ")
                    + QString::number(rdr->lineNumber());
            rdr->readNextStartElement();
            if(rdr->name() == "time") {
                QString time = rdr->readElementText();
                QString hours = time.section(':', 0, 0);
                QString minutes = time.section(':', 1, 1);
                tmp.setData(3, QTime(hours.toInt(), minutes.toInt()));
            }
            else throw QString("Error while reading History.xml:\nMissing time node at line ")
                    + QString::number(rdr->lineNumber());
            rdr->readNextStartElement();
            if(rdr->name() == "access_type") {
                QString type = rdr->readElementText();
                if(type == "Read") tmp.setData(4, QVariant::fromValue<History::AccessType>(History::Read));
                else if(type == "Write") tmp.setData(4, QVariant::fromValue<History::AccessType>(History::Write));
                else throw QString("Error while reading History.xml:\nInvalid access_type-tag content at line ")
                        + QString::number(rdr->lineNumber());
            }
            else throw QString("Error while reading History.xml:\nMissing access_type node at line ")
                    + QString::number(rdr->lineNumber());
            rdr->readNextStartElement();
            if(rdr->name() == "access") {
                QString type = rdr->readElementText();
                if(type == "Add") tmp.setData(5, QVariant::fromValue<History::Access>(History::Add));
                else if(type == "Modify") tmp.setData(5, QVariant::fromValue<History::Access>(History::Modify));
                else if(type == "Remove") tmp.setData(5, QVariant::fromValue<History::Access>(History::Remove));
                else if(type == "Open") tmp.setData(5, QVariant::fromValue<History::Access>(History::Open));
                else throw QString("Error while reading History.xml:\nInvalid access-tag content at line ")
                        + QString::number(rdr->lineNumber());
            }
            else throw QString("Error while reading History.xml:\nMissing access node at line ")
                    + QString::number(rdr->lineNumber());
            cont->insert(tmp);
            rdr->skipCurrentElement();
        }
        else rdr->skipCurrentElement();
    }
}

void XMLHistoryParser::errorHandler(QString errstr) {
    QMessageBox(QMessageBox::Warning, "Warning", errstr).exec();
}

XMLHistoryParser::XMLHistoryParser():
    XMLParser(new HistoryContainer),
    rdr(new QXmlStreamReader),
    wrt(new QXmlStreamWriter)
{}

bool XMLHistoryParser::parseXML() {
    try {
        open4reading();
        rdr->setDevice(file);

        if(rdr->readNextStartElement()) {
            if(rdr->name() == "history") readHistory();
            else throw QString("Error while reading History.xml:\nMissing history node at line")
                    + QString::number(rdr->lineNumber());
        }

        if(rdr->hasError()) {
            throw QString("Error while reading History.xml:\n") + rdr->errorString();
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

bool XMLHistoryParser::writeXML() {
    try {
        open4writing();
        wrt->setDevice(file);
        wrt->setAutoFormatting(true);
        wrt->writeStartDocument();
        wrt->writeStartElement("history");
        for(int i = 0; i < cont->size(); i++) {
            wrt->writeStartElement("account");
            wrt->writeTextElement("username", cont->getPtr(i)->getData(0).toString());
            wrt->writeTextElement("word", cont->getPtr(i)->getData(1).toString());
            wrt->writeTextElement("date", cont->getPtr(i)->getData(2).toDate().toString("dd/MM/yy"));
            wrt->writeTextElement("time", cont->getPtr(i)->getData(3).toTime().toString("H:m"));
            QString str;
            History::AccessType at = cont->getPtr(i)->getData(4).value<History::AccessType>();
            if(at == History::Read) str = "Read";
            else if(at == History::Write) str = "Write";
            wrt->writeTextElement("access_type", str);
            History::Access ac = cont->getPtr(i)->getData(5).value<History::Access>();
            if(ac == History::Add) str = "Add";
            else if(ac == History::Modify) str = "Modify";
            else if(ac == History::Remove) str = "Remove";
            else if(ac == History::Open) str = "Open";
            wrt->writeTextElement("access", str);
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

XMLHistoryParser::~XMLHistoryParser() {
    delete rdr;
    delete wrt;
}
