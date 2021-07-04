void cmd_build_help()
{
    println("- build\t\t Build a c++ program from a config file.");
    println("     \t\t Usage: ./buildus [configFile] [pathToBuild]\n");
}

int setupEnvirement(std::string buildPath, std::string intermediateFolder)
{
    createFolder(buildPath);
    createFolder(intermediateFolder);
    return 0;
}

int cmd_build(std::string buildFilePath, std::string buildPath)
{
       std::string intermediateFolder="intermediate/";
    setupEnvirement(buildPath,intermediateFolder);


    BuildYAML buildYAML=buildYAMLObject(buildFilePath);
    std::string intermediateFiles = "";

    buildYAML.display();

    println("===========> Compiling");
    auto compileFiles=buildYAML.getCompile();
    for(auto compileFile = compileFiles.begin(); compileFile != compileFiles.end(); ++compileFile)
    {
        std::string compileCMD="g++ -c "+compileFile->second + " -o " + intermediateFolder+compileFile->first;
        println(compileCMD);
        std::system(compileCMD.c_str());
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
    return 0;  
}