void cmd_checkout_help()
{
    println("- checkout\t Update the files in the working tree to match a commit.");
    println("     \t\t Usage: ./gitus checkout <commit_hash>\n");
}

std::vector<std::string> getListOfCommitsHashes(){
    std::vector<std::string> commitsHashesArray;
    std::string currentCommitHash=readFile(".git/HEAD");
    std::string prevHash;
    std::string currentHash=currentCommitHash;
    while(currentHash!=prevHash){
        commitsHashesArray.push_back(currentHash);
        prevHash=currentHash;
        std::string content=readFile(objectPathOfHash(currentHash));

        std::istringstream stream(content);
        std::string type,hash;
        while(stream>>type>>hash)
        {
            if(type=="parent") currentHash=hash;
        }
    }
    return commitsHashesArray;
}

void recursiveCheckoutForFiles(std::string treeHash,std::string subFolder,bool first)
{
    if(subFolder!="") subFolder+="/";

    std::ifstream tree(objectPathOfHash(treeHash));
    std::string type,hash,name;
    while(tree>>type>>hash>>name){
        if(type=="blob"){
            println("Changed file "+subFolder+name);
            createFile(subFolder+name);
            writeInFile(subFolder+name,getContentOfFileObject(hash),true);
        }
        else if(type=="tree"){
            if(first) name="";
            createFolder(subFolder+name);
            recursiveCheckoutForFiles(hash,subFolder+name,false);
        }
    }
}


/*
Once we checkout a commit that is different than the one in head we create a file .lock,
so that we lock the user from commiting, the check if the file existe is in cmd_commit().
*/
void cmd_checkout(std::string commitHash)
{

    std::vector<std::string> commitsHashesArray = getListOfCommitsHashes();

    bool found =false;
    int hashIndex=0;
    for(;hashIndex<commitsHashesArray.size();hashIndex++)
    {
        if(commitsHashesArray[hashIndex]==commitHash)
        {
            found=true;
            break;
        }
    }
    if(found)
    {
        if(!boost::filesystem::exists(".lock"))
        {
            createFile(".lock");
            writeInFile(".lock",commitHash,true);
            
            int recursionIndex=1;
            while(recursionIndex<=hashIndex)
            {
                println("===> Checking out "+commitsHashesArray[recursionIndex]);
                recursiveCheckoutForFiles(commitsHashesArray[recursionIndex],"",true);
                    recursionIndex++;
            }
        }
        else if(hashIndex>0)
        {
            std::string prevCheckoutHash=readFile(".lock");
            int prevCheckoutIndex=0;
            for(;prevCheckoutIndex<commitsHashesArray.size();prevCheckoutIndex++)
            {
                if(commitsHashesArray[prevCheckoutIndex]==prevCheckoutHash)
                    break;
            }

            if(prevCheckoutIndex<hashIndex)
            {
                int recursionIndex=prevCheckoutIndex+1;
                while(recursionIndex<=hashIndex)
                {
                    println("===> Checking out "+commitsHashesArray[recursionIndex]);
                    recursiveCheckoutForFiles(commitsHashesArray[recursionIndex],"",true);
                    recursionIndex++;
                }
            }
            else if (hashIndex<prevCheckoutIndex)
            {
                int recursionIndex=prevCheckoutIndex-1;
                while(recursionIndex>=hashIndex)
                {
                    println("===> Checking out "+commitsHashesArray[recursionIndex]);
                    recursiveCheckoutForFiles(commitsHashesArray[recursionIndex],"",true);
                    recursionIndex--;
                }
            }
            else 
            {
                println("You are currently checking out that commit.");
            }
            if(hashIndex==0)
            {
                boost::filesystem::remove(".lock");
            }
        }
        else
        {
            println("You are already in HEAD.");
        }
    }
    else
    {
        println("Please type a valid commit hash. You can copy a hash from './gitus log' and paste it.");
    }
    


    // std::string commitObjectPath=readFile(objectPathOfHash(commitHash));
    // if(!commitObjectPath.empty())
    // {
    //     if(commitHash==readFile(".git/HEAD"))
    //     {
    //         if (boost::filesystem::exists(".lock"))
    //             boost::filesystem::remove(".lock");
    //     }
    //     else
    //     {
    //         createFile(".lock");
    //         std::istringstream stream(readFile(objectPathOfHash(commitHash)));
    //         std::string type,hash;
    //         std::string treeHash;

    //         while(stream>>type>>hash){
    //             if(type=="tree") treeHash=hash;
    //         }

    //         recursiveCheckoutForFiles(treeHash,"");
    //     }   
    // }
    // else
    // {
    //     println("Please type a valid commit hash. You can copy a hash from './gitus log' and paste it.");
    // }
}