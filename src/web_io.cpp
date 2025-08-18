#include "web_io.hpp"

#include <assimp/ai_assert.h>


WebFileSystem::WebFileSystem(const std::map<std::string, std::vector<uint8_t>>& files)
    : files(files)
{ }

WebFileSystem::WebFileSystem(const std::vector<AssimpTSFile>& files)
{
    for (const auto& [path, data] : files)
        this->files[path] = std::vector<uint8_t>(data.begin(), data.end());
}

bool WebFileSystem::Exists(const char* pFile) const
{
    ai_assert(pFile != nullptr);
    return files.find(pFile) != files.end();
}

Assimp::IOStream* WebFileSystem::Open(const char* pFile, const char* /*pMode*/)
{
    ai_assert(pFile != nullptr);
    const auto it = files.find(pFile);
    if (it == files.end())
        return nullptr;
    return new WebFileStream(it->second);
}
void WebFileSystem::Close(Assimp::IOStream* pFile)
{
    ai_assert(pFile != nullptr);
    delete pFile;
}

char WebFileSystem::getOsSeparator() const
{
    return '/';
}


WebFileStream::WebFileStream(std::vector<uint8_t>& buffer)
    : buffer(buffer), pos(0)
{
}

size_t WebFileStream::Read(void* pvBuffer, const size_t pSize, const size_t pCount)
{
    ai_assert(nullptr != pvBuffer);
    ai_assert(0 != pSize);

    const size_t cnt = std::min(pCount, (buffer.size() - pos) / pSize);
    const size_t ofs = pSize * cnt;
    ai_assert(ofs <= buffer.size() - pos);

    std::memcpy(pvBuffer, buffer.data() + pos, ofs);
    pos += ofs;

    return cnt;
}

size_t WebFileStream::Write(const void* pvBuffer, size_t pSize, size_t pCount)
{
    ai_assert(nullptr != pvBuffer);
    ai_assert(0 != pSize);

    pSize *= pCount;
    if (pos + pSize > buffer.size())
        buffer.resize(pos + pSize);

    ai_assert(pos + pSize <= buffer.size());
    std::memcpy(buffer.data() + pos, pvBuffer, pSize);
    pos += pSize;
    return pCount;
}

aiReturn WebFileStream::Seek(const size_t pOffset, const aiOrigin pOrigin)
{
    switch (pOrigin)
    {
    case aiOrigin_CUR:
        if (pOffset + pos > buffer.size()) return AI_FAILURE;
        pos += pOffset;
        break;
    case aiOrigin_END:
        if (pOffset > buffer.size()) return AI_FAILURE;
        pos = buffer.size() - pOffset;
        break;
    case aiOrigin_SET:
        if (pOffset > buffer.size()) return AI_FAILURE;
        pos = pOffset;
        break;
    default:
        return AI_FAILURE;
    }

    return AI_SUCCESS;
}

size_t WebFileStream::Tell() const
{
    return pos;
}

size_t WebFileStream::FileSize() const
{
    return buffer.size();
}

void WebFileStream::Flush()
{
    // No-op
}
