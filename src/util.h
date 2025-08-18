#pragma once
#include "string"
#include <assimp/Exporter.hpp>

static const std::string exportFormatsUnion = []() {
    std::string formatUnionStr;
    const Assimp::Exporter exporter;
    const size_t numExportFormats = exporter.GetExportFormatCount();
    for (size_t i = 0; i < numExportFormats; ++i)
    {
        if (i != 0) formatUnionStr += "|";
        const aiExportFormatDesc* formatDesc = exporter.GetExportFormatDescription(i);
        formatUnionStr += std::string("\"") + formatDesc->id + "\"";
    }
    return formatUnionStr;
}();
