void cmd_init_help()
{
    println("- init\t\t Create an empty gitus repository or reinitialize an existing one.");
    println("     \t\t Usage: ./gitus init\n");
}

void cmd_init()
{
    if(createFolder(".git")==0)
    {
        createFolder(".git/objects");
        createFile(".git/index");
        createFile(".git/HEAD");
        println("Gitus repository created.");
    }
    else
    {
        println("This directory is already a git repository, would you like to reinitialize it ? (y/n)");
        std::string response;
        std::cin>> response;
        if(response=="y")
        {
            removeFolder(".git");
            cmd_init();
        }
    }
        
}