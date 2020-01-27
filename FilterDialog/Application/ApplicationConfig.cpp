#include <stdafx.h>

#include "ApplicationConfig.h"

using namespace std::string_literals;

ApplicationConfig::ApplicationConfig()
   : Configuration{ "AppConfig", "Anwendungs Konfiguration" }
{
   registerParameter(StringParameter{DEFAULT_IMPORT_MATRIX, 
      "Matrix Datei", "current"
      }
   );

   registerParameter(StringParameter{DEFAULT_IMPORT_FOLDER, 
      "Import Ordner", "application.cfg"
      }
   );

   registerParameter(StringParameter{DEFAULT_LOGGER_FOLDER, 
      "Logfile", "logfiles/dialog.log"
      }
   );

   registerParameter(IntegerParameter{DEFAULT_SIGNED_VALUE,
      "Integer Wert", 825, 1000, 800
      }
   );

   registerParameter(DoubleParameter{DEFAULT_DOUBLE_VALUE,
      "Gleitkomma Wert", 321.5, 1000.0, 300.0
      }
   );

   registerParameter(BooleanParameter{DEFAULT_BOOLEAN_VALUE,
      "Boolean Wert", true
      }
   );

   registerParameter(ListParameter{DEFAULT_SIGNED_FILELIST, 
      "Integer Liste", { 12, 23, 34, 45, 56 }, 200
      }
   );

   registerParameter(ListParameter{DEFAULT_MATRIX_FILELIST, 
      "Datei Liste", 
      {
         "path/to/next/sub/folder/1"s,
         "path/to/next/sub/folder/2"s,
         "path/to/next/sub/folder/3"s,
         "path/to/next/sub/folder/4"s,
      }
   });
}

std::string ApplicationConfig::getDefaultImportMatrix() const
{
   return getStringParameter(DEFAULT_IMPORT_MATRIX).getCurrent();
}

void ApplicationConfig::setDefaultImportMatrix(const std::string& file)
{
   getStringParameter(DEFAULT_IMPORT_MATRIX).setCurrent(file);
}

signed ApplicationConfig::getDefaultSignedValue() const
{
   return getIntegerParameter(DEFAULT_SIGNED_VALUE).getCurrent();
}

void ApplicationConfig::setDefaultSignedValue(signed value)
{
   getIntegerParameter(DEFAULT_SIGNED_VALUE).setCurrent(value);
}

double ApplicationConfig::getDefaultDoubleValue() const
{
   return getDoubleParameter(DEFAULT_DOUBLE_VALUE).getCurrent();
}

void ApplicationConfig::setDefaultDoubleValue(double value)
{
   getStringParameter(DEFAULT_IMPORT_FOLDER).getCurrent();
}

std::string ApplicationConfig::getDefaultImportFolder() const
{
   return getStringParameter(DEFAULT_IMPORT_FOLDER).getCurrent();
}

void ApplicationConfig::setDefaultImportFolder(std::string_view folder)
{
   getStringParameter(DEFAULT_IMPORT_FOLDER).setCurrent(folder.data());
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

