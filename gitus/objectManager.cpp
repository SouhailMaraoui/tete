std::string createObject(const std::string& sha)
{
    std::string newObject=sha.substr(0,2)+"/"+sha.substr(2,sha.length());
    createFolder(".git/objects/"+sha.substr(0,2));
    createFile(".git/objects/"+newObject);

    return ".git/objects/"+newObject;
}
std::string createObject(const std::string& sha,const std::string& content,const bool overwrite){
    return writeInFile(createObject(sha),content,overwrite);
}