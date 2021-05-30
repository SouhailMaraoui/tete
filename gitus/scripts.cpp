void println(const std::string& text)
{
    std::cout<<text<<std::endl;
}

bool isInIndex(const std::string& sha,const std::string& name )
{
    bool ret=false;
    std::ifstream index(".git/index");
    std::string path,hash;
    while(index>>hash>>boost::io::quoted(path))
    {
        if(hash==sha && name==path)
            ret=true;
    }
    
    return ret;
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

std::string objectPathOfHash(const std::string& hash)
{
    return ".git/objects/"+hash.substr(0,2)+"/"+hash.substr(2,hash.length());
}

std::string getCurrentDateTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(buffer);
    return str;
}