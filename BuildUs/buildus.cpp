/*
*   SD - CORRECTION
* 
*   cmake
*       fichiers manquant build.h/.cpp, util.cpp, clean.cpp et fileManagement.cpp -10
* 
*   nomenclature (-8)
*       ajout de constante -2
*       constance des accolades -2
*       nom de variable non significatif -2
*       lisibilite (code en sois et manque d'espace entre elements de code) -2
*   
*   non respect des consignes
*       assumer que les fichiers sont dans root -10
*
*   test
*       5/20
* 
*   ci
*       15/15
* 
*   56/100 
* 
*/
#include <iostream>
#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/uuid/detail/sha1.hpp>

#include "BuildYAML.cpp"

#include "fileManager.cpp"
#include "utils.cpp"

#include "build.cpp"
#include "clean.cpp"

void cmd_help()
{
    println("Here is an overview of implemented buildus methods :\n");

    cmd_build_help();
    cmd_clean_help();
}

int main(int argc, char * argv[])
{
    if(argc==2)
    {
        if(std::string(argv[1])=="--help") // SD - constante -2
        {
            cmd_help();
        }
        else if(std::string(argv[1])=="clean") // SD - constante
        {
            cmd_clean();
        }
    }
    else if(argc==3)
    {
        if(std::string(argv[2])=="--help") // SD - constante
        {
            std::string argv1 = argv[1];
            if(argv1=="build") 
            {
                cmd_build_help();
            }
            else if(argv1=="clean") // SD - constante
            {
                cmd_clean_help();
            }
        }
        else 
        {
            std::string argv1 = argv[1];
            std::string argv2 = argv[2];

            cmd_build(argv1, argv2);
        }
    }
    
    else
    {
        cmd_help();
    }

    return 0;
}