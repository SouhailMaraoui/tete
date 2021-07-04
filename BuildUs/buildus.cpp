
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
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
    if(argc>1)
    {
        if(std::string(argv[1])=="--help")
        {
            cmd_help();
        }
        else if(std::string(argv[1])=="clean")
        {
            cmd_clean();
        }
    }
    if(argc>2)
    {
        if(std::string(argv[2])=="--help")
        {
            std::string argv1 = argv[1];
            if(argv1=="build") 
            {
                cmd_build_help();
            }
            else if(argv1=="clean")
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