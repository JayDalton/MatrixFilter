#include "stdafx.h"

#include "Dialog/ConfigEditor/ConfigurationEditor.h"
#include "Application/Application.h"

#include "Dialog/FilterDialog.h"

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");
   const auto appArguments = application.arguments();

   const auto appStringify = appArguments.join(", ").toStdString();
   spdlog::info("Application startet with args: {}", appStringify);
   bool forceConfig = appArguments.contains("-c", Qt::CaseInsensitive);

   fs::path filePath{ "matrixfilter.cfg" };

   ApplicationConfig config;
   JsonReader reader(filePath);
   if (!config.load(filePath) || forceConfig)
   {
      spdlog::warn("Force using Config Editor!");
      ConfigurationEditor editor(nullptr, config);
      if (editor.exec() == QDialog::Accepted)
      {
         JsonWriter writer(filePath);
         config.fromJson(editor.getConfig().toJson());
         config.save(filePath);
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
