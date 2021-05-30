void cmd_commit_help()
{
    println("- commit\t Record changes to the repository.");
    println("     \t\t Usage: ./gitus commit <message> <author>\n");
}

/*
A recursive method that iterate over all folder and subfolder of the root repo, 
and if it finds a file that exist in the index, return ("blob"+ hash of file).
After we finish iterating over all files, we assend back each time checking
=>  if the return was "" (meaning no file was found that exist in the index) we ignore the folder,
=>  if the return was ("blob"+ hash of file), we add ("tree"+ hash of the parent folder of that file)
    and create an object, and we return ("tree"+ hash of that folder).
*/
std::string recursiveObjectCreate(std::string currentPath)
{
    boost::filesystem::path path(currentPath);

    if(boost::filesystem::is_regular_file(currentPath))
    {
        std::string sha1=getSHA1(readFile(currentPath));
        if(isInIndex(sha1))
        {
            println("-----"+currentPath);
            return "blob "+sha1+" "+path.filename().string()+"\n";
        }
    }

    else if (boost::filesystem::is_directory(currentPath)){
        std::string outputFile="";

        for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(currentPath), {}))
        {
            outputFile+= recursiveObjectCreate(entry.path().string());
        }

        if(outputFile.length()>0)
        {
            std::string treeSHA1=getSHA1(outputFile);
            std::string treePath = createObject(treeSHA1,outputFile,true);

            return "tree "+treeSHA1+" "+path.filename().string()+"\n";
        }
        return "";
    }
    return "";
}

/*
Create a commit object and point HEAD to it
*/
void createCommitObject(const std::string& commitObjectContent,const std::string& message,const std::string& author){
    std::string sha1=getSHA1(commitObjectContent);
    std::string content=commitObjectContent;

    std::string head=readFile(".git/HEAD");

    //Check if this is the first commit, if not add parent.
    if(head.length()>0)
        content+="parent "+head;
    
    content+="\ntime \""+getCurrentDateTime()+"\"\n";
    content+="\nmessage \""+message+"\" \nauthor \""+author+"\"\n";
    createObject(sha1,content,true); 

    writeInFile(".git/HEAD",sha1,true);
}

void cmd_commit(const std::string& message,const std::string& author)
{
    if (boost::filesystem::exists(".lock"))
    {
        println("You can't commit as you are curretly checking out a different commit than the one in HEAD.");
    }
    else
    {
        auto path = boost::filesystem::current_path();
        std::string root=recursiveObjectCreate(path.string());

        //root return ("tree" + hash + root_folder_name),
        //the following code just construct a the content of commit object without the folder name.
        std::istringstream stream(root);
        std::string type,hash,folder;
        std::string commitObjectContent;
        while(stream>>type>>hash>>folder){
            commitObjectContent=type+" "+hash+"\n"; 
        }

        createCommitObject(commitObjectContent,message,author);
        writeInFile(".git/index","",true);
    }  
}