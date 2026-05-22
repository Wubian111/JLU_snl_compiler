#include "snl_compiler.h"
#include "snl_console.h"

#include <iostream>
#include <string>

namespace {
// 打印命令行使用说明。
void print_usage(const char* programName) {
  std::cerr << "用法：" << programName << " <SNL源文件> [--mips 输出.asm]\n";
}
}

int main(int argc, char* argv[]) {
  // 先配置控制台编码，避免中文提示在 Windows 终端中出现乱码。
  configure_console_utf8();

  // 至少需要提供一个待编译的 SNL 源文件。
  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  std::string mipsOutputPath;
  // 支持可选参数 `--mips`，用于指定汇编输出路径。
  if (argc == 4 && std::string(argv[2]) == "--mips") {
    mipsOutputPath = argv[3];
  } else if (argc != 2) {
    print_usage(argv[0]);
    return 1;
  }

  // 调用外观类统一执行整个编译流程。
  SNLCompiler compiler;
  return compiler.run(argv[1], std::cout, std::cerr, mipsOutputPath);
}
