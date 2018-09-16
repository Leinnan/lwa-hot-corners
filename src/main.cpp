#include "Manager.h"

int main(int argc, char* argv[])
{
    hc::Manager manager;

    manager.configure();
    manager.start();

    return 0;
}
