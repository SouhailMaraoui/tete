void cmd_add_help()
{
    println("- add\t\t Add a file to the staging area.");
    println("     \t\t Usage: ./gitus add <file>\n");
}


void cmd_add(const std::string& filePath)
{
    std::string fileContent=readFile(filePath);
    std::string sha=getSHA1(fileContent);

    if(isInIndex(sha))
    {
        println("The file is in the staging area already and was not modified.");
    }
    else
    {
        std::string objectContent="\""+filePath+"\" "+getFileSize(filePath)+"\n\""+fileContent+"\"";
        createObject(sha,objectContent,true);
        writeInFile(".git/index",sha+" \""+filePath+"\" ",false);
    }
}