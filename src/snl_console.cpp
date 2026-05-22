#include "snl_console.h"

#include <clocale>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

void configure_console_utf8() {
  // 设置 C 标准库 locale，使标准输入输出按 UTF-8 处理字符串。
  std::setlocale(LC_ALL, ".UTF-8");

#ifdef _WIN32
  // Windows 控制台默认编码常常不是 UTF-8，这里显式切换到 65001。
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif
}
