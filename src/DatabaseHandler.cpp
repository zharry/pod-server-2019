#include "DatabaseHandler.h"
#include <iostream>

DatabaseHandler::DatabaseHandler(const std::string &sensorDBFilename, const std::string &controlsDBFilename) {
    try {
        sensorDB = new SQLite::Database(sensorDBFilename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        controlsDB = new SQLite::Database(controlsDBFilename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    } catch (SQLite::Exception &e) {
        std::cout << "SQLite exception: " << e.getErrorStr() << std::endl;
    }
}

DatabaseHandler::DatabaseHandler(): DatabaseHandler(xstr(SENSOR_DB_FILE), xstr(CONTROLS_DB_FILE)) {}

DatabaseHandler::~DatabaseHandler() {
    delete sensorDB;
    delete controlsDB;
}

void DatabaseHandler::storePacket(wlp::Packet &packet) {
    // TODO parse the packet and store into specific db
}

