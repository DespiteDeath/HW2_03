#include <catch.hpp>
#include "main.hpp"
TEST_CASE("Check functions", "[explorer]") {
	SECTION("Check data")
	{
		fs::create_directory("dir");
		fs::path filePath.string("dir");
		getFileData(filePath);
		REQUIRE(true);
	}
}
