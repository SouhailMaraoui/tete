int createFolder(const std::string& foldername)
{
    auto path = boost::filesystem::current_path();
    const auto folderpath = path.append(foldername);
    if (!boost::filesystem::exists(folderpath))
	{
        boost::filesystem::create_directory(folderpath);
        return 0;
    }
    return -1;
}

int  removeFolder(const std::string& foldername)
{
    auto path = boost::filesystem::current_path();
    const auto folderpath = path.append(foldername);
    if (boost::filesystem::exists(folderpath))
	{
        boost::filesystem::remove_all(folderpath);
        return 0;
    }
    return -1;
}

int createFile(const std::string& filename)
{
    auto path = boost::filesystem::current_path();
    const auto filepath = path.append(filename);
    if (!boost::filesystem::exists(filepath))
	{
        std::ofstream file(filename);
        file.close();
        return 0;
    }
    return -1;
    
}

std::string readFile(const std::string& filename)
{
    std::ifstream file(filename);
    if(file.is_open())
    {
        std::stringstream content;
        content <<file.rdbuf();
        std::string ret=content.str();

        //Remove the last 'new line' from the file content if it exists 
        if (ret[ret.length()-1] == '\n') 
            ret=ret.substr(0,ret.length()-1);
        
        return ret;
    }
    else
    {
        println("Could not read from file "+filename);
        return nullptr;
    }
}

std::string writeInFile(const std::string& filename, const std::string& content,bool overwrite)
{
    std::fstream file;
    if(overwrite)
        file.open(filename,std::ios::out);
    else
        file.open(filename,std::ios::app);

    if(file)
        file<<content<<std::endl;
    else
        println("Could not write into file "+filename);
    file.close();
    return filename;
}

std::string getFileSize(const std::string& filename)
{
    std::string size="0";
    if(boost::filesystem::exists(filename))
        size=std::to_string(boost::filesystem::file_size(filename));
    return size;
}