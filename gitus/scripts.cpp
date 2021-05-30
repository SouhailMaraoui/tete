
void println(const std::string& text)
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
    {
		stream << std::hex << hash[i]; 
	}
    return stream.str();
}

bool isInIndex(const std::string& sha)
{
    bool ret=false;
    std::ifstream index(".git/index");
    std::string path,hash;
    while(index>>path>>hash)
    {
        if(hash==sha)
            ret=true;
    }
    return ret;
}