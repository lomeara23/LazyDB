#include "Database.h"

int main(int argc, char const *argv[])
{
    Database *db = new Database();

    db->runDB();

    return 0;
}
