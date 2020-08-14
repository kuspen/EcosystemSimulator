#include "DebugUtil.h"

EDebugMode g_debug_mode = EDebugMode::DEBUG_MODE_RELEASE;
FILE *g_fp = NULL;

void setDebugMode(EDebugMode mode) {
	g_debug_mode = mode;
}

EDebugMode getDebugMode() {
	return g_debug_mode;
}

void DebugOpenFile(std::string file_name) {
	if (g_debug_mode == EDebugMode::DEBUG_MODE_DEBUG_FULL) {
		fopen_s(&g_fp, file_name.c_str(), "w");
	}
}

FILE* getDebugFile() {
	return g_fp;
}

void DebugCloseFile() {
	if (g_debug_mode == EDebugMode::DEBUG_MODE_DEBUG_FULL) {
		fclose(g_fp);
		g_fp = NULL;
	}
}

