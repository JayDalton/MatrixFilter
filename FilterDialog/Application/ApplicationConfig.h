#pragma once

#include "Config/Configuration.h"

struct ApplicationConfig : public Configuration
{
   ApplicationConfig();

   std::string getDefaultImportFolder() const;
   void setDefaultImportFolder(std::string_view folder);

   std::string getDefaultImportMatrix() const;
   void setDefaultImportMatrix(const std::string& file);

   signed getDefaultSignedValue() const;
   void setDefaultSignedValue(signed value);

   double getDefaultDoubleValue() const;
   void setDefaultDoubleValue(double value);

   std::vector<std::string> getFolderFilelist() const;
   void setFolderFilelist(const std::vector<std::string>& list);

private:
   static inline const std::string DEFAULT_IMPORT_MATRIX{"ImportMatrix"};
   static inline const std::string DEFAULT_IMPORT_FOLDER{"ImportFolder"};
   static inline const std::string DEFAULT_LOGGER_FOLDER{"LogFileFolder"};

   static inline const std::string MATRIX_FOLDER_FILELIST{"folderFileFist"};

   static inline const std::string DEFAULT_SIGNED_VALUE{ "SignedValue" };
   static inline const std::string DEFAULT_DOUBLE_VALUE{ "DoubleValue" };
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
