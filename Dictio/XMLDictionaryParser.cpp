#include"XMLDictionaryParser.h"

void XMLDictionaryParser::open4reading() {
    file->setFileName(qApp->applicationDirPath() + "/Risorse/Dictionary.xml");
    if(file->exists()) qDebug() << "Source for reading Dictionary does exist";
    else throw QString("Source for reading Dictionary does not exist");
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw QString("Error while reading Dictionary.xml\n") + file->errorString();
}

void XMLDictionaryParser::open4writing() {
    file->setFileName(qApp->applicationDirPath() + "/Risorse/Dictionary.xml");
    if(file->exists()) qDebug() << "Source for writing Dictionary does exist";
    else {
        qDebug() << "Source for writing Dictionary does not exist, attempting to create";
        //Crea file xml standard vuoto
        QFile empty(qApp->applicationDirPath() + "/Risorse/Dictionary.xml");
        if(empty.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream stream(&empty);
            stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
            stream << "<dictio>\n<\\dictio>";
        }
    }
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        throw QString("Error while writing Dictionary.xml\n") + file->errorString();
}

void XMLDictionaryParser::readTerm() {
    while(rdr->readNextStartElement()) {
        if(rdr->name() == "term") {
            Term tmp1;
            rdr->readNextStartElement();
            if(rdr->name() == "word") {
                tmp1.setData(0, QVariant(rdr->readElementText()));
            }
            else throw QString("Error while reading Dictionary.xml:\nMissing word node at line ")
                + QString::number(rdr->lineNumber());
            while(rdr->readNextStartElement()) {
                LexicalCategory tmp2;
                if(rdr->name() == "lexical_category") {
                    rdr->readNextStartElement();
                    if(rdr->name() == "category") {
                        tmp2.setData(0, QVariant(rdr->readElementText()));
                    }
                    else throw QString("Error while reading Dictionary.xml:\nMissing category node at line ")
                        + QString::number(rdr->lineNumber());
                    while(rdr->readNextStartElement()) {
                        if(rdr->name() == "semantic") {
                            tmp2.add(rdr->readElementText());
                        }
                        else rdr->skipCurrentElement();
                    }
                }
                else throw QString("Error while reading Dictionary.xml:\nMissing lexical_category node at line ")
                    + QString::number(rdr->lineNumber());
                tmp1.add(tmp2);
            }
            cont->insert(tmp1);
        }
        else rdr->skipCurrentElement();
    }
}

void XMLDictionaryParser::errorHandler(QString errstr) {
    QMessageBox(QMessageBox::Warning, "Warning", errstr).exec();
}

XMLDictionaryParser::XMLDictionaryParser():
    XMLParser(new DictionaryContainer),
    rdr(new QXmlStreamReader),
    wrt(new QXmlStreamWriter)
{}

bool XMLDictionaryParser::parseXML() {
    try {
        open4reading();
        rdr->setDevice(file);

        if(rdr->readNextStartElement()) {
            if(rdr->name() == "dictio") readTerm();
            else throw QString("Error while reading Dictionary.xml:\nMissing dictio node at line")
                + QString::number(rdr->lineNumber());
        }

        if(rdr->hasError()) {
            throw QString("Error while reading Dictionary.xml:\n") + rdr->errorString();
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

bool XMLDictionaryParser::writeXML() {
    try {
        open4writing();
        wrt->setDevice(file);
        wrt->setAutoFormatting(true);
        wrt->writeStartDocument();
        wrt->writeStartElement("dictio");
        QMap<QString, Term>* map = static_cast<QMap<QString, Term>*>(cont->getPtr());
        for(QMap<QString, Term>::const_iterator it = map->cbegin(); it != map->cend(); it++) {
            wrt->writeStartElement("term");
            wrt->writeTextElement("word", (*it).getData(0).toString());
            QVariantList vl = (*it).getData(1).toList();
            for(int i = 0; i < vl.size(); i++) {
                LexicalCategory lc = vl[i].value<LexicalCategory>();
                wrt->writeStartElement("lexical_category");
                wrt->writeTextElement("category", lc.getData(0).toString());
                QStringList semantics = lc.getData(1).toStringList();
                for(int j = 0; j < semantics.size(); j++) {
                    wrt->writeTextElement("semantic", semantics[j]);
                }
                wrt->writeEndElement();
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

XMLDictionaryParser::~XMLDictionaryParser() {
    delete rdr;
    delete wrt;
}
