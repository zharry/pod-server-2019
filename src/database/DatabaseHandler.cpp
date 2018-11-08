#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include "DatabaseHandler.hh"

DatabaseHandler* DatabaseHandler::m_pInstance = nullptr;

DatabaseHandler::DatabaseHandler(const std::string &sensorDBFilename, const std::string &controlsDBFilename) {
    try {
        this->m_pSensorDB = new SQLite::Database(sensorDBFilename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        this->m_pControlsDB = new SQLite::Database(controlsDBFilename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

        // Create Tables for this run
        this->tableName = std::to_string(std::time(0));
        std::string statement = "\
            CREATE TABLE [" + this->tableName + "] (\
                id INT(32) PRIMARY KEY UNIQUE, \
                data NUMERIC\
            );";
        SQLite::Statement createSensorTable(*(this->m_pSensorDB), statement);
        createSensorTable.exec();
        SQLite::Statement createControlsTable(*(this->m_pControlsDB), statement);
        createControlsTable.exec();
    
    } catch (SQLite::Exception &e) {
        std::cout << "SQLite exception: " << e.getErrorStr() << std::endl;
    }
}

DatabaseHandler::DatabaseHandler(): DatabaseHandler(xstr(SENSOR_DB_FILE), xstr(CONTROLS_DB_FILE)) {}

DatabaseHandler::~DatabaseHandler() {
    delete m_pSensorDB;
    delete m_pControlsDB;
}

bool doubleEquals(double a, double b) {
    return ((int64_t)(round(a * 1000000))) == ((int64_t)(round(b * 1000000)));
}

void DatabaseHandler::storePacket(wlp::Packet &packet) {
    const uint32_t id = packet.id();
    const uint32_t type = packet.type(); // Where 0 - Controls, 1 - Sensors
    const uint32_t data = packet.data();
    const float dataf = packet.dataf();

    // Print out packet information, just to see each packet's data (debug)
    bool isFloat = !doubleEquals(packet.dataf(), 0);
    printf("Incoming Packet:\n%-10s %-10s %-10s\n", "ID", "Type", "Data");
    if (isFloat)
        printf("%-10d %-10d %-10f\n\n", id, type, dataf);
    else
        printf("%-10d %-10d %-10d\n\n", id, type, data);

    try {
        // Insert the row
        std::string insertStatement = "\
            INSERT INTO [" + this->tableName + "] (id, data)\
            VALUES(?, ?);";
        SQLite::Statement insert(type ? *(this->m_pSensorDB) : *(this->m_pControlsDB), insertStatement);
        insert.bind(1, id);
        if (isFloat)
            insert.bind(2, dataf);
        else
            insert.bind(2, data);
        insert.exec();
    }
    catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

DatabaseHandler *DatabaseHandler::geInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new DatabaseHandler();
    }

    return m_pInstance;
}
