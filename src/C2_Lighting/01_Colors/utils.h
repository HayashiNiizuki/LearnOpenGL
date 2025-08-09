#include <filesystem>
#include <string>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

namespace fs = std::filesystem;

inline fs::path exec_dir() {
  char buffer[1024];
#if defined(_WIN32)
  GetModuleFileNameA(NULL, buffer, sizeof(buffer));
#elif defined(__linux__)
  ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
  buffer[len] = '\0';
#elif defined(__APPLE__)
  uint32_t size = sizeof(buffer);
  if (_NSGetExecutablePath(buffer, &size) == 0) {
    // buffer 里可能包含符号链接，可以用 fs::canonical 转换
  }
#endif
  return fs::path(buffer).parent_path();
}
