#include <iostream>
#include "DatabaseHandler.h"

DatabaseHandler* DatabaseHandler::m_pInstance = nullptr;

DatabaseHandler::DatabaseHandler(const std::string &sensorDBFilename, const std::string &controlsDBFilename) {
    try {
        m_pSensorDB = new SQLite::Database(sensorDBFilename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        m_pControlsDB = new SQLite::Database(controlsDBFilename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    } catch (SQLite::Exception &e) {
        std::cout << "SQLite exception: " << e.getErrorStr() << std::endl;
    }
}

DatabaseHandler::DatabaseHandler(): DatabaseHandler(xstr(SENSOR_DB_FILE), xstr(CONTROLS_DB_FILE)) {}

DatabaseHandler::~DatabaseHandler() {
    delete m_pSensorDB;
    delete m_pControlsDB;
}

void DatabaseHandler::storePacket(wlp::Packet &packet) {
    // TODO parse the packet and store into specific db
}

DatabaseHandler *DatabaseHandler::geInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new DatabaseHandler();
    }

    return m_pInstance;
}
