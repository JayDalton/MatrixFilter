#include "stdafx.h"

#include "Dialog/ConfigEditor/ConfigurationEditor.h"
#include "Application/Application.h"
#include "Dialog/FilterDialog.h"
#include "Logger/Logger.h"

#include <QCommandLineParser>

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");

   std::ifstream input( "C:\\Final.gif", std::ios::binary );
   std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

   QCommandLineParser parser;
   parser.addOptions({
      {{"c", "config"}, QCoreApplication::translate("main", "Show config dialog on startup")},
   });

   parser.process(application.getArguments());
   bool forceConfigEditor = parser.isSet("c");

   fs::path filePath{ "matrixfilter.cfg" };

   ApplicationConfig config;
   application.setConfig(config);

   if (!config.readFile(filePath) || forceConfigEditor)
   {
      spdlog::warn("Force using Config Editor!");
      ConfigurationEditor editor(nullptr, config);
      if (editor.exec() == QDialog::Accepted)
      {
         config.updateParameter(editor.toVector());
         //config.readFrom(editor.toString());
         application.setConfig(config);
         config.saveFile(filePath);
      }
      else { return 0; }
   }

   auto data = application.getDataLayer();
   
   FilterDialog dialog(data);
   dialog.setConfig(config); // ???
   dialog.show();

   return application.exec();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
