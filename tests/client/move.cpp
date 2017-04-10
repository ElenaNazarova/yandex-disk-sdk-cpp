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
std::string empty_dir = "empty_directory";
std::string new_empty_dir = "empty_directory_new_name";

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

TEST_CASE("moving file to new valid name", "[client][move]")
{
	// Given
	path old_path { valid_file };
	path new_path { new_valid_file };
	ydclient client{ valid_token };

	// When
	auto answer = client.move(old_path, new_path);
	// restore back for correct next tests
	client.move(new_path, old_path);

	// Then
	REQUIRE(answer["href"].get<std::string>() == "https://cloud-api.yandex.net/v1/disk/resources?path=disk%3A%2Ffile.dat.mov");
	REQUIRE(answer["method"].get<std::string>() == "GET");
	REQUIRE(answer["templated"].get<bool>() == false);
}

TEST_CASE("moving empty dir to new valid name", "[client][move]")
{
	// Given
	path old_path { empty_dir };
	path new_path { new_empty_dir };
	ydclient client{ valid_token };

	// When
	auto answer = client.move(old_path, new_path);
	// restore back for correct next tests
	client.move(new_path, old_path);

	// Then
	REQUIRE(answer["href"].get<std::string>() == "https://cloud-api.yandex.net/v1/disk/resources?path=disk%3A%2Fempty_directory_new_name");
	REQUIRE(answer["method"].get<std::string>() == "GET");
	REQUIRE(answer["templated"].get<bool>() == false);
}

TEST_CASE("work with valid fields", "[client][move]")
{
	// Given
	path old_path { empty_dir };
	path new_path { new_empty_dir };
	ydclient client{ valid_token };
	std::list<string> fields {"href", "method"};

	// When
	auto answer = client.move(old_path, new_path, false, fields);
	// restore back for correct next tests
	client.move(new_path, old_path);

	// Then
	REQUIRE(answer["href"].get<std::string>() == "https://cloud-api.yandex.net/v1/disk/resources?path=disk%3A%2Fempty_directory_new_name");
	REQUIRE(answer["method"].get<std::string>() == "GET");
	REQUIRE(answer.find("templated") == answer.end());
}

TEST_CASE("work with all invalid fields", "[client][move]")
{
	// Given
	path old_path { empty_dir };
	path new_path { new_empty_dir };
	ydclient client{ valid_token };
	std::list<string> fields {"name", "date"};

	// When
	auto answer = client.move(old_path, new_path, false, fields);
	// restore back for correct next tests
	client.move(new_path, old_path);

	// Then
	REQUIRE(answer["href"].get<std::string>() == "https://cloud-api.yandex.net/v1/disk/resources?path=disk%3A%2Fempty_directory_new_name");
	REQUIRE(answer["method"].get<std::string>() == "GET");
	REQUIRE(answer["templated"].get<bool>() == false);
}

TEST_CASE("work with invalid and valid fields", "[client][move]")
{
	// Given
	path old_path { empty_dir };
	path new_path { new_empty_dir };
	ydclient client{ valid_token };
	std::list<string> fields {"method", "date"};

	// When
	auto answer = client.move(old_path, new_path, false, fields);
	// restore back for correct next tests
	client.move(new_path, old_path);

	// Then
	REQUIRE(answer.find("href") == answer.end());
	REQUIRE(answer["method"].get<std::string>() == "GET");
	REQUIRE(answer.find("templated") == answer.end());
	REQUIRE(answer.find("date") == answer.end());
}
