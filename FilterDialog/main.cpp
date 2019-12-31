#include "stdafx.h"

#include "Dialog/ConfigEditor/ConfigurationEditor.h"
#include "Application/Application.h"
#include <QCommandLineParser>

#include "Dialog/FilterDialog.h"

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");
   //const auto appArguments = application.arguments();

   //const auto appStringify = appArguments.join(", ").toStdString();
   //spdlog::info("Application startet with args: {}", appStringify);
   //bool forceConfig = appArguments.contains("-c", Qt::CaseInsensitive);

   QCommandLineParser parser;
   parser.setApplicationDescription("Test helper");
   //parser.addHelpOption();
   //parser.addVersionOption();

   parser.addOptions({
      {{"c", "config"}, QCoreApplication::translate("main", "Show config dialog on startup")},
   });

   //parser.process(application);
   qDebug() << QCoreApplication::arguments();
   parser.process(QCoreApplication::arguments());
   bool forceConfigEditor = parser.isSet("c");

   fs::path filePath{ "matrixfilter.cfg" };

   ApplicationConfig config;
   JsonReader reader(filePath);
   if (!config.load(reader) || forceConfigEditor)
   {
      spdlog::warn("Force using Config Editor!");
      ConfigurationEditor editor(nullptr, config);
      if (editor.exec() == QDialog::Accepted)
      {
         JsonWriter writer(filePath);
         config.save(writer);

         config.load(JsonReader(editor.getString()));

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
