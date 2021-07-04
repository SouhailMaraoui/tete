void cmd_build_help()
{
    println("- build\t\t Build a c++ program from a config file.");
    println("     \t\t Usage: ./buildus [configFile] [pathToBuild]\n");
}

int setupEnvirement(std::string buildPath, std::string intermediateFolder,std::string compileHistoryPath)
{
    createFolder(buildPath);
    createFolder(intermediateFolder);
    createFile(compileHistoryPath);
    return 0;
}

int cmd_build(std::string buildFilePath, std::string buildPath)
{
    std::string sourceBuildFolder = boost::filesystem::path(buildFilePath).parent_path().string()+"/";
    buildPath=sourceBuildFolder+buildPath;
    std::string intermediateFolder="intermediate/";
    std::string compileHistoryPath=intermediateFolder+"compileHistory";
    setupEnvirement(buildPath,intermediateFolder,compileHistoryPath);


    try
    {
        BuildYAML buildYAML=buildYAMLObject(buildFilePath);
        buildYAML.display();
        std::string intermediateFiles = "";
        std::string compileHistoryContent=readFile(compileHistoryPath);

        println("===========> Compiling");
        auto compileFiles=buildYAML.getCompile();
        for(auto compileFile = compileFiles.begin(); compileFile != compileFiles.end(); ++compileFile)
        {
            std::string content=readFile(sourceBuildFolder+compileFile->second);
            std::string fileHash=getSHA1(content);
            if(!isCompiled(compileHistoryPath,compileFile->second,fileHash))
            {
                std::string compileCMD="g++ -c "+sourceBuildFolder+compileFile->second + " -o " + intermediateFolder+compileFile->first;
                println(compileCMD);
                std::system(compileCMD.c_str());
                insertToHistory(compileHistoryPath,sourceBuildFolder+compileFile->second,fileHash);
            }
            else{
                println("No need to recompile the file " + sourceBuildFolder+compileFile->second);
            }   
            intermediateFiles+=intermediateFolder+compileFile->first+" ";
        }

        auto includesVector=buildYAML.getDeps_include_var();
        std::string dependencyInclude="";
        if(includesVector.length()>0) dependencyInclude+=" -I"+sourceBuildFolder+includesVector;

        auto librariesPathVector=buildYAML.getDeps_library_var();
        std::string dependencyLibraryPath="";
        if(librariesPathVector.length()>0) dependencyLibraryPath+=" -static -L"+sourceBuildFolder+librariesPathVector;

        auto librariesVector=buildYAML.getDeps_library_lib();
        std::string dependencyLibrary="";
        for(auto library=librariesVector.begin(); library!=librariesVector.end(); ++library)
        {
            dependencyLibrary+=" -l"+*library;
        }
        
        println("===========> Building");
        std::string buildCMD="g++ " +intermediateFiles+ " -o " + buildPath+buildYAML.getProject() + dependencyInclude + dependencyLibraryPath + dependencyLibrary;
        println(buildCMD);
        std::system(buildCMD.c_str());

        println("===========> Copying Files");
        auto filesVector=buildYAML.getFiles();
        for(auto file=filesVector.begin(); file!=filesVector.end(); ++file)
        {
            boost::filesystem::path src(sourceBuildFolder+*file);
            boost::filesystem::path destPath(buildPath);

            boost::filesystem::path dir = boost::filesystem::path(*file).parent_path();
            std::string newFolder=(boost::filesystem::path(buildPath).append(dir.string())).string();
            createFolder(newFolder);
            try
            {
                boost::filesystem::copy_file(src,destPath.append(*file));
            }
            catch(...) 
            {
                throw "Could not copy the file "+*file;
            }
            //boost::filesystem::path(buildPath).append(boost::filesystem::path(*file).filename())
        }
        
    }
    catch (std::string e)
    {
        println(e);
    }
    return 0;  
}