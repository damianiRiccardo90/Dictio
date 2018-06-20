#include"XMLAccountsParser.h"

void XMLAccountsParser::open4reading() {
    file->setFileName(qApp->applicationDirPath() + "/Risorse/Accounts.xml");
    if(file->exists()) qDebug() << "Source for reading Accounts does exist";
    else throw QString("Source for reading Accounts does not exist");
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw QString("Error while reading Accounts.xml\n") + file->errorString();
}

void XMLAccountsParser::open4writing() {
    file->setFileName(qApp->applicationDirPath() + "/Risorse/Accounts.xml");
    if(file->exists()) qDebug() << "Source for writing Accounts does exist";
    else {
        qDebug() << "Source for writing Accounts does not exist, attempting to create";
        //CREARE FILE XML STANDARD VUOTO
        QFile empty(qApp->applicationDirPath() + "/Risorse/Accounts.xml");
        if(empty.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&empty);
            stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
            stream << "<accounts>\n<\\accounts>";
        }
    }
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
        throw QString("Error while writing Accounts.xml\n") + file->errorString();
}

void XMLAccountsParser::readAccount() {
    while(rdr->readNextStartElement()) {
        if(rdr->name() == "account") {
            Account tmp;
            rdr->readNextStartElement();
            if(rdr->name() == "username") {
                tmp.setData(0, rdr->readElementText());
            }
            else throw QString("Error while reading Accounts.xml:\nMissing username node at line ")
                + QString::number(rdr->lineNumber());
            rdr->readNextStartElement();
            if(rdr->name() == "password") {
                tmp.setData(1, rdr->readElementText());
            }
            else throw QString("Error while reading Accounts.xml:\nMissing password node at line ")
                + QString::number(rdr->lineNumber());
            rdr->readNextStartElement();
            if(rdr->name() == "current_user") {
                tmp.setData(2, QVariant(rdr->readElementText()).toBool());
            }
            else throw QString("Error while reading Accounts.xml:\nMissing current_user node at line ")
                + QString::number(rdr->lineNumber());
            rdr->readNextStartElement();
            if(rdr->name() == "type") {
                QString type = rdr->readElementText();
                if(type == "Admin") tmp.setData(3, QVariant::fromValue<Account::Type>(Account::Admin));
                else if(type == "Operator") tmp.setData(3, QVariant::fromValue<Account::Type>(Account::Operator));
                else if(type == "Guest") tmp.setData(3, QVariant::fromValue<Account::Type>(Account::Guest));
                else throw QString("Error while reading Accounts.xml:\nInvalid type-tag content at line ")
                    + QString::number(rdr->lineNumber());
            }
            else throw QString("Error while reading Accounts.xml:\nMissing type node at line ")
                + QString::number(rdr->lineNumber());
            cont->insert(tmp);
            rdr->skipCurrentElement();
        }
        else rdr->skipCurrentElement();
    }
}

void XMLAccountsParser::errorHandler(QString errstr) {
    QMessageBox(QMessageBox::Warning, "Warning", errstr).exec();
}

XMLAccountsParser::XMLAccountsParser():
    XMLParser(new AccountsContainer),
    rdr(new QXmlStreamReader),
    wrt(new QXmlStreamWriter)
{}

bool XMLAccountsParser::parseXML() {
    try {
        open4reading();
        rdr->setDevice(file);

        if(rdr->readNextStartElement()) {
            if(rdr->name() == "accounts") readAccount();
            else throw QString("Error while reading Accounts.xml:\nMissing accounts node at line")
                + QString::number(rdr->lineNumber());
        }

        if(rdr->hasError()) {
            throw QString("Error while reading Accounts.xml:\n") + rdr->errorString();
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

bool XMLAccountsParser::writeXML() {
    try {
        open4writing();
        wrt->setDevice(file);
        wrt->setAutoFormatting(true);
        wrt->writeStartDocument();
        wrt->writeStartElement("accounts");
        for(int i = 0; i < cont->size(); i++) {
            wrt->writeStartElement("account");
            wrt->writeTextElement("username", cont->getPtr(i)->getData(0).toString());
            wrt->writeTextElement("password", cont->getPtr(i)->getData(1).toString());
            wrt->writeTextElement("current_user", "false");
            Account::Type tmp = cont->getPtr(i)->getData(3).value<Account::Type>();
            QString str;
            if(tmp == Account::Guest) str = "Guest";
            else if(tmp == Account::Operator) str = "Operator";
            else if(tmp == Account::Admin) str = "Admin";
            wrt->writeTextElement("type", str);
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

XMLAccountsParser::~XMLAccountsParser() {
    delete rdr;
    delete wrt;
}
