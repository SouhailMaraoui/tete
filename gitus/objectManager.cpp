std::string createObject(const std::string& sha)
{
    std::string newObjectPath=objectPathOfHash(sha);
    createFolder(".git/objects/"+sha.substr(0,2));
    createFile(newObjectPath);

    return newObjectPath;
}
std::string createObject(const std::string& sha,const std::string& content,const bool overwrite)
{
    return writeInFile(createObject(sha),content,overwrite);
}


/*
Return the third element onward in the file object, which consequently, returns the file contents.
*/
std::string getContentOfFileObject(std::string hash)
{
    std::ifstream fileObject(objectPathOfHash(hash));
    std::string line;

    std::string fileContent;
    int elmenetIndex=0;
    while(fileObject>>boost::io::quoted(line))
    {
        if(elmenetIndex<2) elmenetIndex++;
        else fileContent+=line;
    }

    return fileContent;
}