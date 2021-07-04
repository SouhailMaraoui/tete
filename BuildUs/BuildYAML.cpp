#include <iostream>
#include <vector>
#include <map>

class BuildYAML 
{
    private :
        std::string project;
        
        //As in the TP2 recommendations, we will only have one include var in the config file.
        std::string deps_include_var;
        //As in the TP2 recommendations, we will only have one library var in the config file.
        std::string deps_library_var;

        std::vector<std::string> deps_library_lib;
        std::map<std::string, std::string> compile;
        std::vector<std::string> files;

    public:
        std::string getProject()
        {
            return project;
        }

        void setProject(std::string project)
        {
            this->project = project;
        }

        std::string getDeps_include_var()
        {
            return this->deps_include_var;
        }

        void setDeps_include_var(std::string deps_include_var)
        {
            this->deps_include_var=deps_include_var;
        }

        std::string getDeps_library_var()
        {
            return this->deps_library_var;
        }

        void setDeps_library_var(std::string deps_library_var)
        {
            this->deps_library_var=deps_library_var;
        }
        std::vector<std::string> getDeps_library_lib()
        {
            return this->deps_library_lib;
        }

        void pushDeps_library_lib(std::string deps_library_lib)
        {
            this->deps_library_lib.push_back( deps_library_lib);
        }

        std::map<std::string, std::string> getCompile()
        {
            return this->compile;
        }
        void pushCompile(std::string file1, std::string file2)
        {
            this->compile.insert(std::pair<std::string,std::string>(file1,file2));
        }

        std::vector<std::string> getFiles()
        {
            return this->files;
        }
        void pushFiles(std::string file)
        {
            this->files.push_back(file);
        }
};