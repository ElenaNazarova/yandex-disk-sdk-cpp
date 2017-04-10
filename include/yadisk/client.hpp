#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <string>
using std::string;

#include <list>

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include "url/path.hpp"

namespace yadisk
{
    class Client
    {
    public:

        Client(string token);

        auto ping() -> bool;

        auto info() -> json;

        auto info(url::path resource, json options = nullptr) -> json;

        auto list(json options = nullptr) -> json;

        auto upload(url::path to, fs::path from, bool overwrite, std::list<string> fields = std::list<string>()) -> json;

        auto upload(url::path to, string url, std::list<string> fields = std::list<string>()) -> json;

        auto download(url::path from, url::path to, std::list<string> fields = std::list<string>()) -> json;

        auto copy(url::path from, url::path to, bool overwrite, std::list<string> fields = std::list<string>()) -> json;

        ///
        /// \brief Moving a file or folder. To move files and folders on Disk, specify the current path to the resource
        ///        and its new location.
        /// \param from The path to the resource to move. For example, %2Ffoo%2Fphoto.png.
        ///        The path in the parameter value should be URL-encoded.
        /// \param to The path to the new location of the resource. For example, %2Fbar%2Fphoto.png.
        ///        The path in the parameter value should be URL-encoded.
        /// \param overwrite Flag for overwriting files. It is used if the resource is moved to a folder that already
        ///        contains a resource with the same name.
        ///        Acceptable values:
        ///            false — Do not overwrite files; cancel moving (default value).
        ///            true — Delete files with matching names and write the moved files.
        /// \param fields List of JSON keys that should be included in the response. Keys that are not included in this
        ///        list will be discarded when forming the response. If the parameter is omitted, the response is
        ///        returned in full, without discarding anything.
        ///        Only three valid fields (other fields are ignored):
        ///            1) href
        ///            2) method
        ///            3) templated
        /// \return If the request was processed without errors, the API forms the response body depending on the type of
        ///        resource specified – a response for an empty folder or file differs from the response for a non-empty
        ///        folder. (If the request led to an error, the appropriate response code is returned, and the response
        ///        body contains the error description.)
        ///        File or empty folder
        ///            The API responds with the code 201 Created (the resource was successfully moved) and returns a link
        ///            to the metainformation about the created resource in the response body, in the Link object.
        ///        Non-empty folder
        ///            Moving a non-empty folder can take an unknown amount of time, so the API responds with the code
        ///            202 Accepted (the folder moving process has started).
        ///            Applications must track the status of requested operations. The API returns a link to the status of the
        ///            operation launched by the request, in the Link object in the response body.
        ///  \include examples/move.cpp
        ///
        auto move(url::path from, url::path to, bool overwrite = false, std::list<string> fields = std::list<string>()) -> json;

        auto mkdir(url::path dir, std::list<string> fields = std::list<string>()) -> json;

        auto remove(url::path resource, bool permanently, std::list<string> fields = std::list<string>()) -> json;

        auto publish(url::path resource) -> json;

        auto unpublish(url::path resource) -> json;

        auto patch(url::path resource, json meta, std::list<string> fields = std::list<string>()) -> json;

        auto info(string public_key, url::path resource = nullptr, json options = nullptr) -> json;
      
        auto download(string public_key, fs::path to, url::path file = nullptr)-> json;
      
        auto save(string public_key, string name, url::path file = nullptr)-> json;
        
        string token;
    };

}
