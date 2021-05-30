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
commit the test file from the test case "gitus add".
*/

std::string testFile=".test_file";
std::string testFileContentV1="TEXT_HERE";
std::string testFileContentV2="ANOTER_TEXT_HERE";
std::string contentV1SHA=getSHA1(testFileContentV1);
std::string contentV2SHA=getSHA1(testFileContentV2);

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
	
	REQUIRE((createFile(testFile)==0 || createFile(testFile)==-1));
	REQUIRE(writeInFile(testFile,testFileContentV1,true)==testFile);
	REQUIRE_NOTHROW(cmd_add(testFile));

	//Check if file was added to index
	REQUIRE(isInIndex(contentV1SHA)==true);

	//Check if the object of file was created and contains the original text content. 
	REQUIRE(getContentOfFileObject(contentV1SHA)==testFileContentV1);
}

TEST_CASE("gitus commit") 
{
	REQUIRE_NOTHROW(cmd_commit("MESSAGE_TEXT","AUTHOR_NAME"));

	//Check if file was remove from index
	REQUIRE(isInIndex(contentV1SHA)==false);

	//Check if commit object was created
	REQUIRE_NOTHROW(readFile(objectPathOfHash(readFile(".git/HEAD"))));
}

TEST_CASE("gitus checkout") 
{
	std::string oldCommitHash=readFile(".git/HEAD");

	//We change the content of the file to V2 and commit
	writeInFile(testFile,testFileContentV2,true);
	cmd_add(testFile);
	cmd_commit("MESSAGE_TEXT_V2","AUTHOR_NAME");

	std::string newCommitHash=readFile(".git/HEAD");

	//Make sure that the content of the file now is in V2
	REQUIRE(readFile(testFile)==testFileContentV2);

	//Checkout to the old commit and check if the file content are V1
	REQUIRE_NOTHROW(cmd_checkout(oldCommitHash));
	REQUIRE(readFile(testFile)==testFileContentV1);

	//Make sure we can't commit while on checkout
	REQUIRE(cmd_commit("MESSAGE_TEXT_V2","AUTHOR_NAME")==-1);

	//Come back to the latest commit and check if the file content are V2
	REQUIRE_NOTHROW(cmd_checkout(newCommitHash));
	REQUIRE(readFile(testFile)==testFileContentV2);
}
