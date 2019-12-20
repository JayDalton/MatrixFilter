#include <stdafx.h>

#include "ApplicationConfig.h"

using namespace std::string_literals;

ApplicationConfig::ApplicationConfig()
   : Configuration{ "AppConfig", "Anwendungs Konfiguration" }
{
   registerParameter(StringParameter{DEFAULT_IMPORT_MATRIX, 
      "Standard Matrix Datei", "current"
      }
   );

   registerParameter(StringParameter{DEFAULT_IMPORT_FOLDER, 
      "Standard Import Ordner", "application.cfg"
      }
   );

   registerParameter(StringParameter{DEFAULT_LOGGER_FOLDER, 
      "Standard Logfile", "logfiles/dialog.log"
      }
   );

   registerParameter(IntegerParameter{DEFAULT_SIGNED_VALUE,
      "Standard Integer Wert", 1'234, 1'000'000
      }
   );

   registerParameter(DoubleParameter{DEFAULT_DOUBLE_VALUE,
      "Standard Gleitkomma Wert", 1'234.0, 1'000'000.0
      }
   );

   //registerListParameter(ListParameter{
   //   MATRIX_FOLDER_FILELIST, "Standard Datei Liste", 
   //   {
   //      "path/to/next/sub/folder/1"s,
   //      "path/to/next/sub/folder/2"s,
   //      "path/to/next/sub/folder/3"s,
   //      "path/to/next/sub/folder/4"s,
   //   }
   //});
}

std::string ApplicationConfig::getDefaultImportMatrix() const
{
   //return getStringParameter(DEFAULT_MATRIX_IMPORT);
   return {};
}

void ApplicationConfig::setDefaultImportMatrix(const std::string& file)
{
   //setParameter(DEFAULT_MATRIX_IMPORT, file);
}

signed ApplicationConfig::getDefaultSignedValue() const
{
   return 0;
}

void ApplicationConfig::setDefaultSignedValue(signed value)
{
}

double ApplicationConfig::getDefaultDoubleValue() const
{
   return 0.0;
}

void ApplicationConfig::setDefaultDoubleValue(double value)
{
}

std::string ApplicationConfig::getDefaultImportFolder() const
{
   //return getStringParameter(DEFAULT_MATRIX_FOLDER);
   return {};
}

void ApplicationConfig::setDefaultImportFolder(std::string_view file)
{
}

std::vector<std::string> ApplicationConfig::getFolderFilelist() const
{
   //const ListParameter& param = getListParameter(MATRIX_FOLDER_FILELIST);
   //if (std::holds_alternative<std::vector<std::string>>(param.m_current))
   //{
   //   return std::get<ListParameter>(param);
   //}
   return std::vector<std::string>();
}

void ApplicationConfig::setFolderFilelist(const std::vector<std::string>& list)
{
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)

