#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string>

#include "DxLib.h"

enum class EDebugMode {
	DEBUG_MODE_RELEASE,
	DEBUG_MODE_DEBUG_FULL
};

void setDebugMode(EDebugMode mode);
FILE* getDebugFile();
EDebugMode getDebugMode();

template<typename ... Args>
void DebugPrint(const TCHAR *format, Args const& ... args) {

	EDebugMode debug_mode = getDebugMode();

	if (debug_mode == EDebugMode::DEBUG_MODE_DEBUG_FULL) {
		printfDx(format, args ...);
		ScreenFlip();
	}

}

template<typename ... Args>
void DebugDumpFile(const TCHAR* format, Args const& ... args) {

	EDebugMode debug_mode = getDebugMode();

	if (debug_mode == EDebugMode::DEBUG_MODE_DEBUG_FULL) {
		FILE* fp = getDebugFile();
		fprintf(fp, format, args ...);
	}
}

void DebugOpenFile(std::string fine_name);
void DebugCloseFile();
