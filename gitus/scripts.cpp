
void println(std::string text)
{
    std::cout<<text<<std::endl;
}

int createFolder(const std::string& folderName)
{
    auto path = boost::filesystem::current_path();
    const auto folder = path.append(folderName);
    if (!boost::filesystem::exists(folder))
	{
        boost::filesystem::create_directory(folder);
        return 0;
    }
    return -1;
}

void removeFolder(const std::string& folderPath)
{
    auto path = boost::filesystem::current_path();
    boost::filesystem::remove_all(path.append(folderPath));
}

void createFile(const std::string& fileName)
{
    std::ofstream file(fileName);
    file.close();
}