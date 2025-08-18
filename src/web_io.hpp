#pragma once
#include <vector>
#include <map>

#include <assimp/IOStream.hpp>
#include <assimp/IOSystem.hpp>


struct AssimpTSFile
{
    std::string path;
    std::string data;
};

class WebFileSystem : public Assimp::IOSystem
{
private:
    std::map<std::string, std::vector<uint8_t>> files;
public:
    explicit WebFileSystem(const std::vector<AssimpTSFile>& files);
    explicit WebFileSystem(const std::map<std::string, std::vector<uint8_t>>& files);
    ~WebFileSystem() override = default;

    bool Exists(const char* pFile) const override;
    Assimp::IOStream* Open(const char* pFile, const char* pMode) override;
    void Close(Assimp::IOStream* pFile) override;
    [[nodiscard]] char getOsSeparator() const override;
};

class WebFileStream : public Assimp::IOStream
{
    friend class WebFileSystem;
private:
    std::vector<uint8_t>& buffer;
    size_t pos;
protected:
    explicit WebFileStream(std::vector<uint8_t>& buffer);
public:
    ~WebFileStream() override = default;
    size_t Read(void* pvBuffer, size_t pSize, size_t pCount) override;
    size_t Write(const void* pvBuffer, size_t pSize, size_t pCount) override;
    aiReturn Seek(size_t pOffset, aiOrigin pOrigin) override;
    [[nodiscard]] size_t Tell() const override;
    [[nodiscard]] size_t FileSize() const override;
    void Flush() override;
};
