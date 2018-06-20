#include"Manager.h"

Manager::Manager(XMLParser *p): parser(p) {}

Container *Manager::getContainer() const {return parser->getContainer();}

bool Manager::parseXML() {return parser->parseXML();}

bool Manager::writeXML() {return parser->writeXML();}

Manager::~Manager() {delete parser;}
