#include "string"
#include "vector"

#include <assimp/version.h>
#include <assimp/Importer.hpp>
#include "assimp/Exporter.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "post_process.hpp"
#include "util.h"
#include "web_io.hpp"


std::string getAssimpVersion()
{
    return
        std::to_string(aiGetVersionMajor()) + "." +
        std::to_string(aiGetVersionMinor()) + "." +
        std::to_string(aiGetVersionPatch());
}

EMSCRIPTEN_DECLARE_VAL_TYPE(AssimpTSFileList);
EMSCRIPTEN_DECLARE_VAL_TYPE(SupportedFileFormatsStr);
EMSCRIPTEN_DECLARE_VAL_TYPE(Uint8ArrayVector);
Uint8ArrayVector processFiles(
    const AssimpTSFileList& files,
    const SupportedFileFormatsStr& exportFormat,
    const unsigned int flags
) {
    std::vector<AssimpTSFile> fileVec = emscripten::vecFromJSArray<AssimpTSFile>(files);
    Assimp::Importer importer;
    importer.SetIOHandler(new WebFileSystem(fileVec));
    // TODO: Allow optionally registering a progress handler JS callback
    //  importer.SetProgressHandler()

    const aiScene* scene = nullptr;
    // We do not know what the "primary" model file is
    // TODO: Make this actually work to load multi-file models :sob:
    for (auto& [path, fileData] : fileVec)
    {
        scene = importer.ReadFile(path, flags);
        if (scene != nullptr && scene->HasMeshes())
            break;
    }
    if (scene == nullptr) {
        return Uint8ArrayVector(emscripten::val::array());
    }

    // TODO: I might need to export an entire file system? Not sure.
    Assimp::Exporter exporter;
	Assimp::ExportProperties exportProperties;
    exportProperties.SetPropertyBool("JSON_SKIP_WHITESPACES", true);
    const aiExportDataBlob* blob = exporter.ExportToBlob(
        scene,
        exportFormat.as<std::string>().c_str(),
        0,
        &exportProperties
    );
    if (blob == nullptr) {
        return Uint8ArrayVector(emscripten::val::array());
    }

    const emscripten::val arr = emscripten::val::array();
    while (blob) {
        emscripten::val u8 = emscripten::val::global("Uint8Array").new_(blob->size);
        u8.call<void>("set", emscripten::typed_memory_view(blob->size, static_cast<uint8_t*>(blob->data)));
        arr.call<void>("push", u8);
        blob = blob->next;
    }
    return Uint8ArrayVector(arr);
}

EMSCRIPTEN_BINDINGS(assimpts)
{
    emscripten::function("getAssimpVersion", &getAssimpVersion);
    // TODO: Build step to generate TS union with all supported export formats,
    //  and set it as the type of processFiles exportFormat.
    //  Maybe also export JS string arrays of supported input and output formats as part of the API
    emscripten::function("processFiles", &processFiles);

    emscripten::register_type<Uint8ArrayVector>("Uint8Array[]");
    emscripten::value_object<AssimpTSFile>("AssimpTSFile")
        .field("path", &AssimpTSFile::path)
        .field("data", &AssimpTSFile::data);
    emscripten::register_type<AssimpTSFileList>("AssimpTSFile[]");
    emscripten::register_type<SupportedFileFormatsStr>(exportFormatsUnion.c_str());

    // Cursed macro shenanigans to "cleanly" bind the enum values
    emscripten::enum_<PostProcessFlags>("PostProcessFlags")
#define X(n, _) .value(#n, PostProcessFlags::n)
        POST_PROCESS_FLAGS(X)
        POST_PROCESS_PRESETS(X);
#undef X
}
