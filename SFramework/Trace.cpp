#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
//char *__trace_file = "D:\\UIT_Project\\MegaMan\\trace.log"; 
char *__trace_file = "..//trace.log";
int __trace = 1;
using namespace std;
//void trace(const LPWSTR format, ...)
//{
//	if (!__trace) return;
//
//	FILE *f = stderr;
//
//	if (__trace_file != NULL)
//	{
//		if (fopen_s(&f, __trace_file, "a") != 0)
//		{
//			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
//			return;
//		}
//	}
//
//	va_list ap;
//	va_start(ap, format);
//	vfwprintf(f, format, ap);
//	va_end(ap);
//
//	fprintf(f, "\n");
//
//	if (__trace_file != NULL) fclose(f);
//}

void trace(string data){
	fstream f;
	f.open(__trace_file, ios::app);
	//std::string data;
	
	f << data << "\n";
	f.close();
}
