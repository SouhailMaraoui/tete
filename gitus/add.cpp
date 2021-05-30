void cmd_add_help()
{
    println("- add\t\t Add a file to the staging area.");
    println("     \t\t Usage: ./gitus add <file>\n");
}


int  cmd_add(const std::string& filePath)
{
    if(!boost::filesystem::exists(".git"))
    {
        println("This is not a gitus repository.");
        return -1;
    }
    std::string fileContent=readFile(filePath);
    if(!fileContent.empty())
    {
        std::string sha=getSHA1(fileContent);

        if(isInIndex(sha,filePath))
        {
            println("The file is in the staging area already and was not modified.");
        }
        else
        {
            std::string objectContent="\""+filePath+"\" "+getFileSize(filePath)+"\n\""+fileContent+"\"";
            createObject(sha,objectContent,true);
            writeInFile(".git/index",sha+" \""+filePath+"\" ",false);
        }
        return 0;
    }
    else
    {
        println("File is empty or does not exist.");
        return -1;
    }
    
}