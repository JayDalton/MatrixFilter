﻿#include "stdafx.h"

#include "Dialog/ConfigEditor/ConfigurationEditor.h"
#include "Application/Application.h"

#include "Dialog/FilterDialog.h"

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");

   fs::path filePath{ "filterdialog.cfg" };
   if (!fs::exists(filePath))
   {
      spdlog::warn("Config does not exists!");
   }

   ApplicationConfig config;
   if (!config.load(filePath))
   {
      spdlog::warn("Config could not read!");
      ConfigurationEditor editor(nullptr, config);
      if (editor.exec() == QDialog::Accepted)
      {
         //config.load(editor.getConfig());
         //config.save(filePath);
      }
   }

   application.setConfig(config);
   auto data = application.getDataLayer();
   
   FilterDialog dialog(data);
   dialog.setConfig(config);
   dialog.show();

   return application.exec();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
