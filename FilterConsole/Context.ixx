module; //begins global module fragment

#include <string>
#include <iostream>
#include <filesystem>

//#include <Matrix/FileManager.h>
//#include <Matrix/FilterManager.h>
//#include <Matrix/MatrixManager.h>

#include <Logger/Logger.h>

//import std.core;
//import std.regex;
//import std.string;
//import std.vector;
//import std.filesystem;

export module Context;

export class Context
{
public:
   Context();

   std::string getString() const
   {
      return "Hello World!";
   }

   int test();

private:

private:
   //FileManager m_fileManger;
   //MatrixManager m_matrixManager;
   //FilterManager m_filterManager;
};

module :private; // Everything beyond this point is not available to importers of 'm'.

Context::Context()
{
   spdlog::flush_on(spdlog::level::debug);
   spdlog::set_level(spdlog::level::trace);
   
   Logger::appendLoggerSink(Logger::createMsvcLoggerSink());
   Logger::appendLoggerSink(Logger::createFileLoggerSink("console.log"));
   
   spdlog::info("===============================================");
   spdlog::info("Logging: {0} - {1}", "Console", "0.0.1");
   spdlog::info("===============================================");
}

int Context::test()
{
   return 42;
}