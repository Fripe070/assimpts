#include <iostream>
#include <string>
#include <assimp/version.h>


std::string getAssimpVersion() {
    return std::to_string(aiGetVersionMajor()) + "." +
           std::to_string(aiGetVersionMinor()) + "." +
           std::to_string(aiGetVersionPatch());
}

int main() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Assimp Version: " << getAssimpVersion() << std::endl;
    return 0;
}