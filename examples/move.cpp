#include <yadisk/client.hpp>

int main () 
{
    yandisk::Client client { "token" };
    url::path from = "/example1";
    url::path to = "/example2";
    bool over = true;
    std::list<std::string> fields {"name"};
    auto move = client.move(from,to);
    auto code = move ["code"];
    auto link = move ["href"];
    ctdout << code << link;
      
}
