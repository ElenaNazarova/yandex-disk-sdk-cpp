/*
 * Move file and print result of operation to stdout
 */
#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <iostream>
#include <string>

#include <url/path.hpp>
using url::path;

int main() {
	path old_path { "our_file" };
	path new_path { "new_name_of_our_file" };
	ydclient client{ "token" };

	auto answer = client.move(old_path, new_path);
	std::cout << answer << std::endl;
}
