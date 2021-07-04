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
    std::string intermediateFolder="intermediate/";
    std::string compileHistoryPath=intermediateFolder+"compileHistory";
    setupEnvirement(buildPath,intermediateFolder,compileHistoryPath);


    BuildYAML buildYAML=buildYAMLObject(buildFilePath);
    std::string compileHistoryContent=readFile(compileHistoryPath);
    std::string intermediateFiles = "";

    buildYAML.display();

    println("===========> Compiling");
    auto compileFiles=buildYAML.getCompile();
    for(auto compileFile = compileFiles.begin(); compileFile != compileFiles.end(); ++compileFile)
    {
        std::string content=readFile(compileFile->second);
        std::string fileHash=getSHA1(content);
        if(!isCompiled(compileHistoryPath,compileFile->second,fileHash))
        {
            std::string compileCMD="g++ -c "+compileFile->second + " -o " + intermediateFolder+compileFile->first;
            println(compileCMD);
            std::system(compileCMD.c_str());
            insertToHistory(compileHistoryPath,compileFile->second,fileHash);
        }
        else{
            println("No need to recompile the file " + compileFile->second);
        }   
        intermediateFiles+=intermediateFolder+compileFile->first+" ";
    }

    auto includesVector=buildYAML.getDeps_include_var();
    std::string dependencyInclude="";
    for(auto include=includesVector.begin(); include!=includesVector.end(); ++include){
        dependencyInclude+=" -I"+*include;
    }

    auto librariesPathVector=buildYAML.getDeps_library_var();
    std::string dependencyLibraryPath="";
    for(auto libraryPath=librariesPathVector.begin(); libraryPath!=librariesPathVector.end(); ++libraryPath){
        dependencyLibraryPath+=" -L"+*libraryPath;
    }

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
        println(*file);
        boost::filesystem::copy_file(*file,buildPath+*file);
    }
    println("To... "+buildPath);

    return 0;  
}