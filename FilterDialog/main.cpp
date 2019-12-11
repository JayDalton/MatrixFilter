﻿#include "stdafx.h"

#include "Application/Application.h"

#include "Dialog/FilterDialog.h"

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");

   ApplicationConfig config;
   fs::path filePath{ "filterdialog.cfg" };
   //if (config.loadJsonFile(filePath))
   //{
   //   application.setConfig(config);
   //}

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
