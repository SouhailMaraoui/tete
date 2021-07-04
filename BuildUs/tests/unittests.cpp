#define CATCH_CONFIG_MAIN

#include "catch.hpp"

std::string test="test";


TEST_CASE("test") 
{
	REQUIRE((test=="test" || test=="test2"));
	CHECK(test=="test");
	if(test=="test")
	{
		REQUIRE(test!="var");
	}
}