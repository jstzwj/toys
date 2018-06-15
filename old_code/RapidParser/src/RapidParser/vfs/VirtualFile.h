#pragma once
#ifndef RAPIDPARSER_VIRTUALFILE
#define RAPIDPARSER_VIRTUALFILE
#include<cinttypes>
#include<string>
#include"../config.h"
namespace rpr
{
	namespace vfs
	{
		typedef rpr_int Handle;
		typedef rpr_int64_t rpr_file_size;
		class VirtualFile
		{
		public:
			VirtualFile() = default;
			virtual ~VirtualFile();
		public:
			
		};
		class FileReader :public VirtualFile
		{
		public:
			FileReader() = default;
			FileReader(const rpr_string & filepath) :path(filepath) {}
			FileReader(const rpr_string && filepath) :path(filepath) {}
		private:
			rpr_string path;
		public:
			rpr_string readAll();
		};
		class FileWriter :public VirtualFile
		{
		public:
			FileWriter() = default;
			FileWriter(const rpr_string & filepath) :path(filepath) {}
			FileWriter(const rpr_string && filepath) :path(filepath) {}
		private:
			rpr_string path;
		public:
			void writeAll(const rpr_string & filepath);
		};
	}
	
}

#endif // !RAPIDPARSER
