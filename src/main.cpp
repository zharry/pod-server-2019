#include <SQLiteCpp/SQLiteCpp.h>
#include "DatabaseHandler.h"
#include <iostream>
#include <CanPacket.h>

int main() {
    DatabaseHandler *databaseHandler = DatabaseHandler::geInstance();

    wlp::Packet sP1(1, 1.6545f, 1);
    databaseHandler->storePacket(sP1);

    wlp::Packet sP2(2, (uint32_t) 64, 0);
    databaseHandler->storePacket(sP2);

    wlp::Packet sP3(3, 128);
    databaseHandler->storePacket(sP3);

    wlp::Packet sP4(4);
    databaseHandler->storePacket(sP4);

}
