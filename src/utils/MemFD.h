#pragma once

#include <linux/memfd.h>
#include <string>

enum class MemFDFlags : int {
  CLOEXEC = MFD_CLOEXEC,
  ALLOW_SEALING = MFD_ALLOW_SEALING,
};

class MemFD {
 public:
  const std::string filename;
  int fd;

  explicit MemFD(const std::string& filename);

  bool open(unsigned int flags);

  bool setSize(size_t size);

  bool seal();

  void close();

  ~MemFD();
};
