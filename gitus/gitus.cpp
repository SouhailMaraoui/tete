#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/uuid/detail/sha1.hpp>

#include "scripts.cpp"
#include "fileManager.cpp"
#include "objectManager.cpp"

#include "init.cpp"
#include "add.cpp"
#include "log.cpp"
#include "commit.cpp"
#include "checkout.cpp"

void cmd_help()
{
    println("Here is an overview of implemented gitus methods :\n");

    cmd_init_help();
    cmd_log_help();
    cmd_add_help();
    cmd_commit_help();
    cmd_checkout_help();
}




int main(int argc, char * argv[])
{

        if(argc>2 && std::string(argv[2])=="--help")
        {
            std::string argv1 = argv[1];
            if(argv1=="init") cmd_init_help();
            else if(argv1=="log") cmd_log_help();
            else if(argv1=="add") cmd_add_help();
            else if(argv1=="commit") cmd_commit_help();
            else if(argv1=="checkout") cmd_checkout_help();
        }
        else if(argc>1)
        {
            std::string argv1 = argv[1];
            if(argv1=="init") cmd_init();
            
            else if(argv1=="add")
            {
                if(argc>2)
                    cmd_add(std::string(argv[2]));
                else 
                    println("You need to select one file to add.");
            }
            
            else if(argv1=="commit")
            {
                if(argc>3)
                    cmd_commit(std::string(argv[2]),std::string(argv[3]));
                else 
                    println("You need to enter a message and the author, see 'gitus commit --help'.");
            } 
            
            else if(argv1=="log")
            {
                
            }
            
            else if(argv1=="checkout")
            {}
            
            else if(argv1=="--help" || argv1=="-h")
                cmd_help();
            
            else
                println(argv1+" is an invalid command, type './gitus --help' or './gitus -h' for help.");
        }
        else
            cmd_help();

    return 0;
}



