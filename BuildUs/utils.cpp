void println(const std::string& text) // SD - why though?
{
    std::cout<<text<<std::endl;
}


std::string getSHA1(const std::string& valueToHash)
{
    boost::uuids::detail::sha1 sha;

	sha.process_bytes(valueToHash.c_str(), valueToHash.length());

	unsigned int hash[5];
	sha.get_digest(hash);

	std::stringstream stream;

	std::string result;
	for (int i = 0; i < 5; ++i) 
		stream << std::hex << hash[i]; 

    return stream.str();
}

bool isCompiled(std::string compileHistoryPath, std::string filePath, std::string fileHash)
{
    std::string compileHistoryContent=readFile(compileHistoryPath);
    std::istringstream stream(compileHistoryContent);
    std::string file,hash;
    while(stream>>file>>hash)
    {
        if(filePath==file && fileHash==hash)
        {
            return true;
        }
    }
    return false;
}

std::string insertToHistory(std::string compileHistoryPath, std::string filePath, std::string newHash)
{
    std::string output="";
    std::string compileHistoryContent=readFile(compileHistoryPath);
    std::istringstream stream(compileHistoryContent);
    std::string file,hash;
    while(stream>>file>>hash)
    {
        if(filePath!=file)
        {
            output+=file+" " + hash + "\n";
        }
    }
    output+=filePath+" " + newHash + "\n";
    return writeInFile(compileHistoryPath,output,true);
}