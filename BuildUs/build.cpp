void cmd_build_help()
{
    println("- build\t\t Build a c++ program from a config file to a path.");
    println("     \t\t Usage: ./buildus [configFile] [pathToBuild]\n");
}

/*
A function that setup the build environment :
    - Create the build path;
    - Create the intermediate folder where ./buildus was executed;
    - create 'compileHistory' file which contains the name and hash of all previously compiled files.
*/
void setupEnvirement(const std::string buildPath,const std::string intermediateFolder,const std::string compileHistoryPath)
{
    createFolder(buildPath);
    createFolder(intermediateFolder);
    createFile(compileHistoryPath);
}

/*
A function that check in the compile history to see if the file has already been compiled (Using it's {path+name} and {SHA1(fileContent)} for validation),
And then compile it if it has not been compiled previously or was changed.
*/
int compileFileFunc(const std::string sourceFile,const std::string intermediateFile, const std::string compileHistoryPath)
{
    std::string content=readFile(sourceFile);
    std::string fileHash=getSHA1(content);
    if(!isCompiled(compileHistoryPath,sourceFile,fileHash))
    {
        std::string compileCMD="g++ -c "+sourceFile+ " -o " + intermediateFile;
        std::system(compileCMD.c_str());
        println(compileCMD);
        insertToHistory(compileHistoryPath,sourceFile,fileHash);
        return 0;
    }
    else{
        println("No need to recompile the file " + sourceFile);
        return 1;
    }   
}


void cmd_build(std::string buildFilePath, std::string buildPath)
{
    // Add a '/' to the build path if the user didn't add one.. so "folder/build" => "folder/build/"
    if(buildPath.back()!='/')
    {
        buildPath+="/";
    }

    std::string sourceBuildFolder = boost::filesystem::path(buildFilePath).parent_path().string()+"/";
    std::string intermediateFolder="intermediate/";
    std::string compileHistoryPath=intermediateFolder+"compileHistory";
    setupEnvirement(buildPath,intermediateFolder,compileHistoryPath);

    try
    {
        BuildYAML buildYAML=buildYAMLObject(buildFilePath);

        std::string compileHistoryContent=readFile(compileHistoryPath);
        std::string intermediateFiles = "";

        println("\n===========> Compiling");
        auto compileFiles=buildYAML.getCompile();
        for(auto compileFile = compileFiles.begin(); compileFile != compileFiles.end(); ++compileFile)
        {
            compileFileFunc(sourceBuildFolder+compileFile->second,intermediateFolder+compileFile->first,compileHistoryPath);  
            intermediateFiles+=intermediateFolder+compileFile->first+" ";
        }
        println("===========> Done\n");


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
        std::system(buildCMD.c_str());
        println(buildCMD);
        println("===========> Done\n");


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
                println("Copied the file '"+*file+"'");
            }
            catch(...) 
            {
                println("Could not copy the file '"+*file+"'");
            }
        }
        println("===========> Done\n");
    }
    catch (std::string e)
    {
        println(e);
    }
}