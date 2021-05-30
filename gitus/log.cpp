void cmd_log_help()
{
    println("- log\t\t Show commits logs.");
    println("     \t\t Usage: ./gitus log\n");
}

/*
Print the comment of the current hash and return the parent commit hash 
*/
std::string getParentCommit(std::string commitHash)
{
    std::string content=readFile(objectPathOfHash(commitHash));

    std::istringstream stream(content);
    std::string type,hash;
    std::string ret;

    while(stream>>type>>boost::io::quoted(hash))
    {
        if(type=="tree") continue;
        else if(type=="parent") ret=hash;
        else if(type=="time") continue;
        else if (type=="message") println("\t"+hash+"\n");
    }
    return ret;
}

void cmd_log()
{
    std::string currentCommitHash=readFile(".git/HEAD");
    println("> "+currentCommitHash);
    std::string hash=getParentCommit(currentCommitHash);
    while(hash!=""){
        println("> "+hash);
        hash=getParentCommit(hash);
    }
}