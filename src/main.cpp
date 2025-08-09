#include <iostream>
#include <string>
#include <assimp/version.h>
#include <emscripten/bind.h>


std::string getAssimpVersion() {
    return std::to_string(aiGetVersionMajor()) + "." +
           std::to_string(aiGetVersionMinor()) + "." +
           std::to_string(aiGetVersionPatch());
}

EMSCRIPTEN_BINDINGS(assimpts) {
    emscripten::function("getAssimpVersion", &getAssimpVersion);
}
