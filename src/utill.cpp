#include "utill.hpp"

namespace utill{
    std::string read_file(const std::string& path)
    {
        std::ifstream file(path);
        if (file.fail())
        {
            std::cout << "Failed to read file " << path  << "\n";
            assert(false);
        }
        std::stringstream buffer;

        buffer << file.rdbuf();

        file.close();
        
        return buffer.str();
    }
}