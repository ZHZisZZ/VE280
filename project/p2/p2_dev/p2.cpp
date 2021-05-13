/*
 * This is VE280 Project 2, SU2020.
 * Written by Zhanhui Zhou, Ziqiao Ma(TA) and Zhuoer Zhu(TA).
 * Latest Update: 6/1/2020.
 * All rights reserved.
 */
#include <iostream>
#include "server_type.h"
#include "simulation.h"

int main(int argc, char* argv[])
{
    try
    {
        ValidArgument(argc - 1);
        InputFile inputFile = {string(argv[1]), string(argv[2])};
        Server server(inputFile);
        server.ParseNameFile();
        server.ParseLogFile();  
    }
    catch(const Exception_t& e)
    {
        cout << e.error_info;
    }
}