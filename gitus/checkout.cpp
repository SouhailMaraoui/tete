void cmd_checkout_help()
{
    println("- checkout\t Update the files in the working tree to match a commit.");
    println("     \t\t Usage: ./gitus checkout <commit_hash>\n");
}

void recursiveCheckout(std::string treeHash,std::string subFolder)
{
    if(subFolder!="") subFolder+="/";

    std::ifstream tree(objectPathOfHash(treeHash));
    std::string type,hash,name;
    while(tree>>type>>hash>>name){
        if(type=="blob"){
            createFile(subFolder+name);
            writeInFile(subFolder+name,getContentOfFileObject(hash),true);
        }
        else if(type=="tree"){
            createFolder(subFolder+name);
            recursiveCheckout(hash,subFolder+name);
        }
    }
}


/*
Once we checkout a commit that is different than the one in head we create a file .lock,
so that we lock the user from commiting, the check if the file existe is in cmd_commit().
*/

void cmd_checkout(std::string commitHash)
{
    std::string commitObjectPath=readFile(objectPathOfHash(commitHash));
    if(!commitObjectPath.empty())
    {
        if(commitHash==readFile(".git/HEAD"))
        {
            if (boost::filesystem::exists(".lock"))
                boost::filesystem::remove(".lock");
        }
        else
        {
            createFile(".lock");
            std::istringstream stream(readFile(objectPathOfHash(commitHash)));
            std::string type,hash;
            std::string treeHash;

            while(stream>>type>>hash){
                if(type=="tree") treeHash=hash;
            }

            recursiveCheckout(treeHash,"");
        }
        
    }
    else
    {
        println("Please type a valid commit hash. You can copy a hash from './gitus log' and paste it.");
    }
    
}