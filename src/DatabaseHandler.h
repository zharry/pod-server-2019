#ifndef PODSERVER_DATABASE_H
#define PODSERVER_DATABASE_H

#include <string>

#include <SQLiteCpp/SQLiteCpp.h>
#include <CanPacket.h>

#define xstr(s) str(s)
#define str(s) #s

#if !defined(SENSOR_DB_FILE)
#error "Sensor Database file not defined"
#elif !defined(CONTROLS_DB_FILE)
#error "Controls Database file not defined"
#endif

class DatabaseHandler {
    SQLite::Database *m_pSensorDB;
    SQLite::Database *m_pControlsDB;
    std::string tableName;
    static DatabaseHandler *m_pInstance;

    DatabaseHandler(const std::string &sensorDBFilename, const std::string &controlsDBFilename);

    DatabaseHandler();

    ~DatabaseHandler();

public:
    /// Provides DatabaseHandler instance (singleton)
    static DatabaseHandler* geInstance();

    /// Stores CAN packet received into appropriate database
    /// @param packet CAN packet
    void storePacket(wlp::Packet &packet);
};

#endif //PODSERVER_DATABASE_H
