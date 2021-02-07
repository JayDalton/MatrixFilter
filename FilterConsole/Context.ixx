#include <string>
//#include <iostream>

//import std.core;
//import std.regex;
//import std.string;
//import std.vector;
//import std.filesystem;

export module Context;

export struct Context
{
   std::string getString() const
   {
      return "Hello World!";
   }

   signed getX() const
   {
      return x;
   }

private:
   signed x{ 0 };
};