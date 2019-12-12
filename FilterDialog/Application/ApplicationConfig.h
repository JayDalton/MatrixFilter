#pragma once

#include "Config/Configuration.h"

struct ApplicationConfig : public Configuration
{
   ApplicationConfig();

   std::string getDefaultImportFolder() const;
   void setDefaultImportFolder(std::string_view folder);

   std::string getDefaultImportMatrix() const;
   void setDefaultImportMatrix(const std::string& file);

   std::vector<std::string> getFolderFilelist() const;
   void setFolderFilelist(const std::vector<std::string>& list);

private:
   static inline const char* DEFAULT_IMPORT_MATRIX{"ImportMatrix"};
   static inline const char* DEFAULT_IMPORT_FOLDER{"ImportFolder"};
   static inline const char* DEFAULT_LOGFILE_FOLDER{"LogFileFolder"};
   static inline const char* MATRIX_FOLDER_FILELIST{"folderFileFist"};
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
