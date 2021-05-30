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