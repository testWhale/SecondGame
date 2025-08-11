#include "filesystem.h"
#include <cstdlib>  // for getenv
#include <string>
#include <sstream>
#include <iostream>

namespace FileSystem {

    std::string getPath(const std::string& relativePath) {
        // You can adapt this to your project structure
        // This example assumes you are running your binary from the root project directory
        return relativePath;
    }

}