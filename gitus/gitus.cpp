#include <iostream>
#include "scripts.cpp"

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
            if(argv1=="init")
            {

            }
            
            else if(argv1=="add")
            {}
            
            else if(argv1=="commit")
            {}
            
            else if(argv1=="log")
            {}
            
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



