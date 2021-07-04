int createFolder(const std::string& foldername)
{
    auto path = boost::filesystem::current_path();
    const auto folderpath = path.append(foldername);
    if (!boost::filesystem::exists(folderpath))
	{
        boost::filesystem::create_directories(folderpath);
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
        throw "Could not read from file \""+filename+"\".";
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
        throw "Could not write into file " + filename;
    
    file.close();
    return filename;
}

/*
A function that take the yaml config file and build an Object of type BuildYAML.
*/
BuildYAML buildYAMLObject(std::string filename)
{
    try
    {
        BuildYAML buildYAML;

        std::string content=readFile(filename);
        std::string line,parent,subparent;
        std::istringstream stream(content);

        while(std::getline(stream,line))
        {
            if(line.rfind("project",0)==0){
                parent="project";
            }
            else if(line.rfind("deps_include",0)==0){
                parent="deps_include";
                continue;
            }
            else if(line.rfind("deps_library",0)==0){
                parent="deps_library";
                continue;
            }
            else if(line.rfind("compile",0)==0){
                parent="compile";
                continue;
            }
            else if(line.rfind("files",0)==0){
                parent="files";
                continue;
            }

            std::istringstream iss(line);
            std::string elm1, elm2,elm3,elm4;
            iss>>elm1>>elm2>>elm3>>elm4;

            
            /*
            In case there was a space between an element and the colon ":", remove that space and translate to the left.
            So for example "project : app2" will turn into "project: app2"
            Or " - f1 : file1.cpp" will turn into "- f1: file1.cpp"
            */
            if(elm2==":")
            {
                elm1+=elm2;
                elm2=elm3;
            }
            else if(elm3==":")
            {
                elm2+=elm3;
                elm3=elm4;
            }

            if(elm1=="libs:"){
                subparent="libs";
                continue;
            }

            if(parent=="project"){
                buildYAML.setProject(elm2);
            }
            else if(parent=="deps_include"){
                if(elm1=="var:") {
                    buildYAML.setDeps_include_var(elm2);
                }
            }
            else if(parent=="deps_library"){
                if(elm1=="var:") {
                    buildYAML.setDeps_library_var(elm2);
                }
                if(subparent=="libs") 
                    buildYAML.pushDeps_library_lib(elm2);
            }
            else if(parent=="compile"){
                buildYAML.pushCompile(elm2.substr(0,elm2.size()-1),elm3);
            }
            else if(parent=="files"){
                buildYAML.pushFiles(elm2);
            }
        }
        return buildYAML;
    }
    catch(std::string error)
    {
        throw error;
    }
}
