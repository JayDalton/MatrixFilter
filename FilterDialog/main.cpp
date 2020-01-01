#include "stdafx.h"

#include "Dialog/ConfigEditor/ConfigurationEditor.h"
#include "Application/Application.h"
//#include <QCommandLineParser>
#include <QDebug>

#include "Dialog/FilterDialog.h"

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");

   QCommandLineParser parser;
   parser.addOptions({
      {{"c", "config"}, QCoreApplication::translate("main", "Show config dialog on startup")},
   });

   parser.process(application.getArguments());
   bool forceConfigEditor = parser.isSet("c");

   fs::path filePath{ "matrixfilter.cfg" };

   ApplicationConfig config;
   if (!config.load(filePath) || forceConfigEditor)
   {
      spdlog::warn("Force using Config Editor!");
      ConfigurationEditor editor(nullptr, config);
      if (editor.exec() == QDialog::Accepted)
      {
         config.load(editor.getString());
         config.save(filePath);
      }
   }

   application.setConfig(config);
   auto data = application.getDataLayer();
   
   FilterDialog dialog(data);
   dialog.setConfig(config); // ???
   dialog.show();

   return application.exec();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
