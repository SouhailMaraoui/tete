#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/uuid/detail/sha1.hpp>

#include "../BuildYAML.cpp"

#include "../fileManager.cpp"
#include "../utils.cpp"

#include "../build.cpp"
#include "../clean.cpp"


/*
*	SD - 5/20 faible
* 
*	et si pas de nom de projet ou lib ou files ou includes? tests d'erreurs
* 
*/

std::string configFileName="config.buildus";

std::string test0Path="TestBuild/ex0/";
std::string test0Build="ex0/";

std::string test1Path="TestBuild/ex1/";
std::string test1Build="ex1/";

std::string test2Path="TestBuild/ex2/";
std::string test2Build="ex2/";

std::string test3Path="TestBuild/myTest/";
std::string test3Build="myTest/";

/*
I used the 3 first exercises from Lab4 and an additional test with Files to copy since they cover most build cases :
	- EX0 : Compile a single cpp file;
	- EX1 : Compile two cpp files;
	- EX2 : Compile one cpp file but with a Library path(-Ll) and a Library (-l);
	- myTest: Compile one file and copy 2 files (one is in a subfolder);
*/

TEST_CASE("YAML_PARSER")
{
	BuildYAML testObj;
	REQUIRE_NOTHROW(testObj=buildYAMLObject(test0Path+configFileName));
	REQUIRE(testObj.getProject()=="hello-world-0");
	REQUIRE(testObj.getFiles().size()==0);
}

TEST_CASE("EX0") 
{
	println("==========================EX0==========================");
	REQUIRE_NOTHROW(cmd_build(test0Path+configFileName,test0Build));
	std::string cmd="./"+test0Build+"hello-world-0 > output";
	std::system(cmd.c_str());

	//Check the output of the excutable
	REQUIRE(readFile("output")=="Hello World 42");
	
	//Check if we have created the build environment ('intermediate' folder and 'compileHistory' file)
	REQUIRE(boost::filesystem::exists("intermediate"));
	REQUIRE(boost::filesystem::exists("intermediate/compileHistory"));

	//Make sure that we don't have to recompile the file main.cpp
	REQUIRE(compileFileFunc(test0Path+"main.cpp","helloworld","intermediate/compileHistory")==1);

	//Clean 
	REQUIRE_NOTHROW(cmd_clean());
}

TEST_CASE("EX1") 
{
	println("==========================EX1==========================");
	REQUIRE_NOTHROW(cmd_build(test1Path+configFileName,test1Build));
	std::string cmd="./"+test1Build+"hello-world-1 > output";
	std::system(cmd.c_str());
	REQUIRE(readFile("output")=="Hello World 42");
	REQUIRE_NOTHROW(cmd_clean());
}

TEST_CASE("EX2") 
{
	println("==========================EX2==========================");
	REQUIRE_NOTHROW(cmd_build(test2Path+configFileName,test2Build));
	std::string cmd="./"+test2Build+"hello-world-2 > output";
	std::system(cmd.c_str());
	REQUIRE(readFile("output")=="Hello World \nHello World 42\nHello World 2 21");
	REQUIRE_NOTHROW(cmd_clean());
}

TEST_CASE("myTest") 
{
	println("=========================myTest=========================");
	REQUIRE_NOTHROW(cmd_build(test3Path+configFileName,test3Build));
	std::string cmd="./"+test3Build+"helloworld > output";
	std::system(cmd.c_str());
	REQUIRE(readFile("output")=="Hello World!");
	REQUIRE_NOTHROW(cmd_clean());

	//Check if the files were copied
	REQUIRE(boost::filesystem::exists(test3Build+"file1"));
	REQUIRE(boost::filesystem::exists(test3Build+"folder/file2"));
}