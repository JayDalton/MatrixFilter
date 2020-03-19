#pragma once

#include <array>
#include <string>
#include <optional>
#include <filesystem>
#include <string_view>

namespace fs = std::filesystem;

struct MatrixFileInfo
{
   enum class Type { None, Graymap, Dicom, Count };

   explicit MatrixFileInfo(std::string_view filePath);
   //explicit MatrixFileInfo(const std::string& filePath);

   const fs::path& getPath() const;

   bool isValid() const;
   Type getFileType() const;
   unsigned getFileSize() const;
   std::string getFileName() const;
   std::string getFilePath() const;
   std::string getExtension() const;

private:
   fs::path m_path;
   static constexpr std::array m_validExtensions{".pgm", ".dcm"};
};

using MatrixFileUPtr = std::unique_ptr<MatrixFileInfo>;
using MatrixFileSPtr = std::shared_ptr<MatrixFileInfo>;
using MatrixFileList = std::vector<MatrixFileInfo>;
using MatrixFileOpt = std::optional<MatrixFileInfo>;

using MatrixFileRepository = std::vector<MatrixFileInfo>;

