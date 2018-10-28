#include <SQLiteCpp/SQLiteCpp.h>
#include "DatabaseHandler.h"
#include <iostream>
#include <CanPacket.h>

int main() {
    DatabaseHandler databaseHandler{};

    wlp::Packet sP(10, 65.f, 20);
    databaseHandler.storePacket(sP);
}
