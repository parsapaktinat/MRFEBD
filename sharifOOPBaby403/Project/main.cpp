#include <iostream>
#include <vector>
#include <filesystem>
#include <string>

class Element{};

std::vector<std::string> getFilenames(const std::string &directory) {
    std::vector<std::string> filenames;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (std::filesystem::is_regular_file(entry)) {
            filenames.push_back(entry.path().filename().string());
        }
    }
    return filenames;
}

std::vector<Element> getElementsFromTXTFile(const std::string &fileName) {

}

int main()
{

    return 0;
}
