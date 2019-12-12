#include "stdafx.h"

#include "Dialog/ConfigEditor/ConfigurationEditor.h"
#include "Application/Application.h"

#include "Dialog/FilterDialog.h"

int main(int argc, char *argv[])
{
   fs::path filePath{ "filterdialog.cfg" };
   if (!fs::exists(filePath))
   {
      spdlog::warn("Config does not exists!");
   }

   ApplicationConfig config;
   if (!config.load(filePath))
   {
      spdlog::warn("Config could not read!");
      ConfigurationEditor editor;
      //editor.load(config);
      if (editor.exec() == QDialog::Accepted)
      {
         //config.load(editor.getConfig());
         //config.save(filePath);
      }
   }

   Application application(argc, argv, "Matrix Filter");
   application.setConfig(config);

   //auto matrix = config.getDefaultImportMatrix();
   //auto folder = config.getDefaultMatrixFolder();
   //auto filelist = config.getFolderFilelist();

   //if (config.saveJsonFile(filePath))
   //{
   //   qDebug() << "";
   //}
   //else {
   //   qDebug() << "";
   //}

   //FilterDialogUPtr m_dialog{ nullptr };

   //FilterDialog()



   //QApplication a(argc, argv);
    FilterDialog w(nullptr);
    w.show();
   // return a.exec();
   return application.exec();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
