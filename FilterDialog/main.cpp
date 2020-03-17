#include "stdafx.h"

#include "Dialog/ConfigEditor/ConfigurationEditor.h"
#include "Application/Application.h"
#include "Dialog/FilterDialog.h"

#include <QCommandLineParser>

int main(int argc, char *argv[])
{
   Application application{ argc, argv, "Matrix Filter" };

   QCommandLineParser parser;
   parser.addOptions({
      {{"c", "config"}, QCoreApplication::translate("main", "Show config dialog on startup")},
   });

   parser.process(application.getArguments());
   bool forceConfigEditor = parser.isSet("c");

   ApplicationConfig config;
   application.setConfig(config);

   fs::path filePath{ "matrixfilter.cfg" };
   if (!config.readFile(filePath) || forceConfigEditor)
   {
      SPDLOG_INFO("Force using Config Editor!");
      ConfigurationEditor editor(nullptr, config);
      if (editor.exec() == QDialog::Accepted)
      {
         config.updateParameter(editor.toVector());
         application.setConfig(config);
         config.saveFile(filePath);
      }
      else { return 0; }
   }

   FilterDialog dialog{ application.getDataLayer() };
   dialog.show();

   return application.exec();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
