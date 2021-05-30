#define CATCH_CONFIG_MAIN

// RTFM catch2:
// https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top

#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/uuid/detail/sha1.hpp>

#include "../scripts.cpp"
#include "../fileManager.cpp"
#include "../objectManager.cpp"

#include "../init.cpp"
#include "../add.cpp"
#include "../log.cpp"
#include "../commit.cpp"
#include "../checkout.cpp"

/*
The test cases are assumed to be run sequentially, hence why "gitus commit" 
commit the test files from the test case "gitus add".
*/


//This is file 1 in root folder
std::string testFile1="1.test_file";
std::string testFile1ContentV1="THIS IS TEST FILE 1";
std::string testFile1ContentV2="THIS IS VERSION 2 OF FILE 1";
std::string file1V1SHA=getSHA1(testFile1ContentV1);
std::string file1V2SHA=getSHA1(testFile1ContentV2);

/*
This is file 2 in nested folder f1/f2/, reason being to check if both
recursive commit and checkout are working even with files in subfolders.
*/
std::string testFile2="f1/f2/2.test_file";
std::string testFile2ContentV1="THIS IS TEST FILE 2";
std::string testFile2ContentV2="THIS IS VERSION 2 OF FILE 2";
std::string file2V1SHA=getSHA1(testFile2ContentV1);
std::string file2V2SHA=getSHA1(testFile2ContentV2);

TEST_CASE("gitus init") 
{
	REQUIRE((createFolder(".git") == 0 || createFolder(".git")== -1));
	CHECK(removeFolder(".git")==0);
	if(createFolder(".git")==0)
	{
		REQUIRE(createFolder(".git/objects") == 0);
		REQUIRE(createFile(".git/index")==0);
		REQUIRE(createFile(".git/HEAD")==0);
	}
	if(createFolder(".git")==-1)
	{
		REQUIRE(createFolder(".git/objects") == -1);
		REQUIRE(createFile(".git/index")==-1);
		REQUIRE(createFile(".git/HEAD")==-1);
	}
}

TEST_CASE("gitus add") 
{
	createFolder("f1");
	createFolder("f1/f2");

	REQUIRE((createFile(testFile1)==0 || createFile(testFile1)==-1));
	REQUIRE((createFile(testFile2)==0 || createFile(testFile2)==-1));

	REQUIRE(writeInFile(testFile1,testFile1ContentV1,true)==testFile1);
	REQUIRE(writeInFile(testFile2,testFile2ContentV1,true)==testFile2);

	REQUIRE(cmd_add(testFile1)==0);
	REQUIRE(cmd_add(testFile2)==0);
	REQUIRE(cmd_add("I_DONT_EXIST.FILE")==-1);

	//Check if the files were added to index
	REQUIRE(isInIndex(file1V1SHA,testFile1)==true);
	REQUIRE(isInIndex(file2V1SHA,testFile2)==true);

	//Check if the object of file was created and contains the original text content. 
	REQUIRE(getContentOfFileObject(file1V1SHA)==testFile1ContentV1);
	REQUIRE(getContentOfFileObject(file2V1SHA)==testFile2ContentV1);
}

TEST_CASE("gitus commit") 
{
	REQUIRE(cmd_commit("COMMIT_1","mars3319")==0);println("");

	//Check if the files were remove from index
	REQUIRE(isInIndex(file1V1SHA,testFile1)==false);
	REQUIRE(isInIndex(file2V1SHA,testFile2)==false);

	//Check if commit object was created
	REQUIRE_NOTHROW(readFile(objectPathOfHash(readFile(".git/HEAD"))));
}

TEST_CASE("gitus checkout") 
{
	std::string oldCommitHash=readFile(".git/HEAD");

	//We change the content of the file1 to V2 and commit
	writeInFile(testFile1,testFile1ContentV2,true);
	cmd_add(testFile1);
	cmd_commit("COMMIT_2","mars3319");println("");

	//We change the content of the file2 to V2 and commit
	writeInFile(testFile2,testFile2ContentV2,true);
	cmd_add(testFile2);
	cmd_commit("COMMIT_3","mars3319");println("");

	std::string newCommitHash=readFile(".git/HEAD");

	//Make sure that the content of the file 1 and 2 now is in V2
	REQUIRE(readFile(testFile1)==testFile1ContentV2);
	REQUIRE(readFile(testFile2)==testFile2ContentV2);

	//Checkout to the old commit and check if both file contents are in V1
	REQUIRE_NOTHROW(cmd_checkout(oldCommitHash));println("");
	REQUIRE(readFile(testFile1)==testFile1ContentV1);
	REQUIRE(readFile(testFile2)==testFile2ContentV1);

	//Make sure we can't commit while on checkout
	REQUIRE(cmd_commit("MESSAGE_TEXT_V2","AUTHOR_NAME")==-1);println("");

	//Come back to the latest commit and check if the file content are in V2
	REQUIRE_NOTHROW(cmd_checkout(newCommitHash));println("");
	REQUIRE(readFile(testFile1)==testFile1ContentV2);
	REQUIRE(readFile(testFile2)==testFile2ContentV2);
}

TEST_CASE("gitus log") 
{
	println("----------------------------");
	println("HISTORY LOGS ::");
	REQUIRE(cmd_log()==0);
	REQUIRE(removeFolder(".git")==0);
}