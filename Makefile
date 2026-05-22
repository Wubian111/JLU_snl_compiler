SHELL := powershell.exe
.SHELLFLAGS := -NoProfile -ExecutionPolicy Bypass -Command

CXX ?= g++
TARGET ?= build/snl_compiler.exe
FILE ?= examples/test.snl
MIPS_OUT ?= output/out.asm
MIPS_INPUT ?= tests\test_input.txt
MIPS_RESULT ?= output/out.txt
MARS_JAR ?= tools/Mars for Compile 2022.jar
COMPILER_LOG ?= output/compiler.log
FLEX ?= tools/win_flex_bison/win_flex.exe
BISON ?= tools/win_flex_bison/win_bison.exe
LEXER_SPEC ?= grammar/snl_lexer.l
PARSER_SPEC ?= grammar/snl_parser.y
GENERATED_LEXER ?= src/snl_lexer_generated.cpp
GENERATED_PARSER ?= src/snl_parser_generated.cpp
GENERATED_PARSER_HEADER ?= include/snl_parser_generated.h

SOURCES := \
  src/main.cpp \
  src/snl_token.cpp \
  src/snl_ast.cpp \
  src/snl_console.cpp \
  src/snl_lexer_impl.cpp \
  $(GENERATED_LEXER) \
  src/snl_parser.cpp \
  $(GENERATED_PARSER) \
  src/snl_syntax_tree_printer.cpp \
  src/snl_semantic.cpp \
  src/snl_mips_generator.cpp \
  src/snl_compiler.cpp

HEADERS := \
  include/snl_token.h \
  include/snl_ast.h \
  include/snl_console.h \
  include/snl_lexer.h \
  include/snl_generated_lexer.h \
  include/snl_parser.h \
  include/snl_parser_driver.h \
  $(GENERATED_PARSER_HEADER) \
  include/snl_syntax_tree_printer.h \
  include/snl_semantic.h \
  include/snl_mips_generator.h \
  include/snl_compiler.h

CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -finput-charset=UTF-8 -fexec-charset=UTF-8 -Iinclude -Isrc -static -static-libstdc++ -static-libgcc
UTF8 = $$OutputEncoding = [Text.UTF8Encoding]::new($$false); [Console]::InputEncoding = $$OutputEncoding; [Console]::OutputEncoding = $$OutputEncoding
zh = $$([Text.Encoding]::UTF8.GetString([Convert]::FromBase64String('$(1)')))

.PHONY: all build dirs generate test test-mips clean help info
.SILENT:

all: build

build: dirs $(TARGET)

generate: $(GENERATED_LEXER) $(GENERATED_PARSER) $(GENERATED_PARSER_HEADER)

$(GENERATED_LEXER): $(LEXER_SPEC)
	$(UTF8); if (-not (Test-Path -LiteralPath "$(FLEX)")) { Write-Error "$(call zh,5om+5LiN5YiwIEZsZXgg5Y+v5omn6KGM5paH5Lu277ya)$(FLEX)"; exit 1 }
	& "$(FLEX)" --outfile="$@" "$<"; if ($$LASTEXITCODE -ne 0) { exit $$LASTEXITCODE }

$(GENERATED_PARSER) $(GENERATED_PARSER_HEADER): $(PARSER_SPEC)
	$(UTF8); if (-not (Test-Path -LiteralPath "$(BISON)")) { Write-Error "$(call zh,5om+5LiN5YiwIEJpc29uIOWPr+aJp+ihjOaWh+S7tu+8mg==)$(BISON)"; exit 1 }
	& "$(BISON)" --defines="$(GENERATED_PARSER_HEADER)" --output="$(GENERATED_PARSER)" "$<"; if ($$LASTEXITCODE -ne 0) { exit $$LASTEXITCODE }

$(TARGET): $(SOURCES) $(HEADERS)
	$(UTF8); Write-Host "$(call zh,5q2j5Zyo57yW6K+R) $(TARGET)"
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

dirs:
	New-Item -ItemType Directory -Path build,output -Force | Out-Null

test: build
	$(UTF8); Write-Host "$(call zh,5rWL6K+V5paH5Lu277ya)$(FILE)"; cmd /d /c "chcp 65001>nul & build\snl_compiler.exe $(FILE) 2>&1"; $$code = $$LASTEXITCODE; Write-Host "$(call zh,56iL5bqP6YCA5Ye656CB77ya)$$code"; exit 0

test-mips: build
	$(UTF8); & "$(TARGET)" "$(FILE)" --mips "$(MIPS_OUT)" > "$(COMPILER_LOG)"; if ($$LASTEXITCODE -ne 0) { Get-Content -Encoding UTF8 -LiteralPath "$(COMPILER_LOG)"; exit $$LASTEXITCODE }; Write-Host "$(call zh,5bey55Sf5oiQ) $(MIPS_OUT)"
	$(UTF8); if (-not (Test-Path -LiteralPath "$(MARS_JAR)")) { Write-Error "$(call zh,5om+5LiN5YiwIE1BUlMgamFy44CC56S65L6L77yabWFrZSB0ZXN0LW1pcHMgTUFSU19KQVI9RDpcdG9vbHNcTWFycy5qYXI=)"; exit 1 }
	$(UTF8); Get-Content -LiteralPath "$(MIPS_INPUT)" | java -jar "$(MARS_JAR)" nc "$(MIPS_OUT)" | Set-Content -Encoding UTF8 -LiteralPath "$(MIPS_RESULT)"
	if (Test-Path -LiteralPath "InstructionStatistics.txt") { Move-Item -LiteralPath "InstructionStatistics.txt" -Destination "output\InstructionStatistics.txt" -Force }
	$(UTF8); Write-Host "$(call zh,TUlQUyDnqIvluo/ov5DooYznu5Pmnpzlt7LlhpnlhaU=) $(MIPS_RESULT)"

info:
	$(UTF8); Write-Host "$(call zh,5a6e546w5pa55byP77yaRmxleCDor43ms5XliIbmnpDlmajjgIFCaXNvbiDor63ms5XliIbmnpDlmajjgIFBU1QgVmlzaXRvcuOAgeivreS5ieWIhuaekOWZqOWSjCAzMiDkvY0gTUlQUyDnlJ/miJDlmajjgII=)"
	Write-Host "$(call zh,55Sf5oiQ55qE5YmN56uv5rqQ56CB5L+d55WZ5ZyoIHNyYy9pbmNsdWRlIOS4re+8jOS+v+S6juacqumHjeaWsOeUn+aIkOaXtuS5n+iDveebtOaOpee8luivkeOAgg==)"

clean:
	if (Test-Path -LiteralPath "build") { Get-ChildItem -LiteralPath "build" -File | Remove-Item -Force }
	if (Test-Path -LiteralPath "output") { Get-ChildItem -LiteralPath "output" -File | Remove-Item -Force }
	if (Test-Path -LiteralPath "InstructionStatistics.txt") { Remove-Item -LiteralPath "InstructionStatistics.txt" -Force }

help:
	$(UTF8); Write-Host "$(call zh,5Y+v55So55uu5qCH77ya)"
	Write-Host "$(call zh,ICBtYWtlIGdlbmVyYXRlICAgICAgICAgICAgICAgICDph43mlrDnlJ/miJAgRmxleCAvIEJpc29uIOa6kOeggQ==)"
	Write-Host "$(call zh,ICBtYWtlIGJ1aWxkICAgICAgICAgICAgICAgICAgICDnvJbor5EgYnVpbGQvc25sX2NvbXBpbGVyLmV4ZQ==)"
	Write-Host "$(call zh,ICBtYWtlIHRlc3QgRklMRT08c291cmNlLnNubD4gICDov5DooYzliY3nq6/liIbmnpDmtYHnqIs=)"
	Write-Host "$(call zh,ICBtYWtlIHRlc3QtbWlwcyBGSUxFPTxzb3VyY2Uuc25sPiAg55Sf5oiQIE1JUFMg5bm25L2/55SoIE1BUlMg6L+Q6KGM)"
	Write-Host "$(call zh,ICBtYWtlIGluZm8gICAgICAgICAgICAgICAgICAgICDmmL7npLrlrp7njrDmlrnlvI/mpoLov7A=)"
	Write-Host "$(call zh,ICBtYWtlIGNsZWFuICAgICAgICAgICAgICAgICAgICDliKDpmaQgYnVpbGQg5ZKMIG91dHB1dCDkuK3nmoTkuqfniak=)"
	Write-Host "$(call zh,56S65L6L77yabWFrZSB0ZXN0IEZJTEU9dGVzdHNcc3ludGF4X21pc3NpbmdfdGhlbi5zbmw=)"
