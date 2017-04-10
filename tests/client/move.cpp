#include <catch.hpp>
#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <string>

#include <url/path.hpp>
using url::path;

std::string valid_token = "AQAAAAATPnx3AAQXOJS1w4zmPUdrsJNR1FATxEM";
std::string wrong_token = "wrongtoken";
std::string non_exist_file = "not_existed_file11123243.dat";
std::string valid_file = "file.dat";
std::string new_valid_file = "file.dat.mov";

TEST_CASE("try to move a file with wrong toker", "[client][move]")
{
	// Given
	path old_path { valid_file };
	path new_path { new_valid_file };
	ydclient client{ wrong_token };

	// When
	auto answer = client.move(old_path, new_path);
	
	// Then
	REQUIRE(answer["error"].get<std::string>() == "UnauthorizedError");
}

TEST_CASE("try to move non existed file", "[client][move]")
{
	// Given
	path old_path { non_exist_file };
	path new_path { new_valid_file };
	ydclient client{ valid_token };

	// When
	auto answer = client.move(old_path, new_path);

	// Then
	REQUIRE(answer["error"].get<std::string>() == "DiskNotFoundError");
}
