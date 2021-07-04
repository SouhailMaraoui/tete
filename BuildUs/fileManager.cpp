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
    
    try
    {
        std::ifstream file(filename);
        file.is_open();
        std::stringstream content;
        content <<file.rdbuf();
        std::string ret=content.str();

        //Remove the last 'new line' from the file content if it exists 
        if (ret[ret.length()-1] == '\n') 
            ret=ret.substr(0,ret.length()-1);
        
        return ret;
    }
    catch(std::ios_base::failure& e)
    {
        std::cout << "Could not read from file " << filename <<std::endl;
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
        std::cout << "Could not write into file "<< filename <<std::endl;
    file.close();
    return filename;
}

/*
A function that take the yaml config file and build an Object of type BuildYAML.
*/
BuildYAML buildYAMLObject(std::string filename)
{
    BuildYAML buildYAML;

    std::string content=readFile(filename); 
    std::istringstream stream(content);
    

    std::string line,parent,subparent;

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
        std::string a, b,c,d;
        iss>>a>>b>>c>>d;

        
        /*
        In case there was a space between an element and the colon ":", remove that space and translate to the left.
        So for example "project : app2" will turn into "project: app2"
        Or " - f1 : file1.cpp" will turn into "- f1: file1.cpp"
        */
        if(b==":")
        {
            a+=b;
            b=c;
        }
        else if(c==":")
        {
            b+=c;
            c=d;
        }

        if(a=="libs:"){
            subparent="libs";
            continue;
        }

        if(parent=="project"){
            buildYAML.setProject(b);
        }
        else if(parent=="deps_include"){
            if(a=="var:") {
                buildYAML.setDeps_include_var(b);
            }
        }
        else if(parent=="deps_library"){
            if(a=="var:") {
                buildYAML.setDeps_library_var(b);
            }
            if(subparent=="libs") 
                buildYAML.pushDeps_library_lib(b);
        }
        else if(parent=="compile"){
            buildYAML.pushCompile(b.substr(0,b.size()-1),c);
        }
        else if(parent=="files"){
            buildYAML.pushFiles(b);
        }
    }
    return buildYAML;
}
