#include "Manager.h"

#include <iostream>

int main(int argc, char* argv[])
{
    hc::Manager manager;

    if(argc > 1){
        manager.setConfigPath( argv[1] );
        manager.configure();
        manager.start();
    }
    else
    {
        std::cerr << "You need to pass config file path as argument!"
                  << std::endl;
    }

        return 0;
}
