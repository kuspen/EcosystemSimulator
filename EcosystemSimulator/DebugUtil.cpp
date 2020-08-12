#include "DebugUtil.h"

EDebugMode g_debug_mode = EDebugMode::DEBUG_MODE_RELEASE;
FILE* g_fp = NULL;

void setDebugMode(EDebugMode mode) {
	g_debug_mode = mode;
}

EDebugMode getDebugMode() {
	return g_debug_mode;
}

void DebugOpenFile(std::string file_name) {

}

FILE* getDebugFile() {
	return g_fp;
}

void DebugCloseFIle() {

}

