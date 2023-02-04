#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Error: Missing path to .exe file." << std::endl;
    return 1;
  }

  // Get the path to the .exe file.
  std::string path = argv[1];

  // Convert the path to wide string format.
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring wPath = converter.from_bytes(path);

  // Start the process.
  STARTUPINFO startupInfo = { 0 };
  startupInfo.cb = sizeof(startupInfo);
  PROCESS_INFORMATION processInfo = { 0 };
  if (!CreateProcessW(wPath.c_str(), nullptr, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &startupInfo, &processInfo)) {
    std::cerr << "Error: Failed to create process." << std::endl;
    return 1;
  }

  // Wait for the process to complete.
  WaitForSingleObject(processInfo.hProcess, INFINITE);

  // Clean up.
  CloseHandle(processInfo.hProcess);
  CloseHandle(processInfo.hThread);

  return 0;
}
