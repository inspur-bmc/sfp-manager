#pragma once

#include <unistd.h>

class FileDescriptor
{
  public:
    FileDescriptor() = default;
    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor(FileDescriptor&&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;
    FileDescriptor& operator=(FileDescriptor&&) = delete;

    FileDescriptor(int fd) : fd(fd)
    {
    }

    ~FileDescriptor()
    {
        if (fd != -1)
        {
            close(fd);
        }
    }

    int operator()()
    {
        return fd;
    }

    operator bool() const
    {
        return fd != -1;
    }

    void set(int descriptor)
    {
        fd = descriptor;
    }

  private:
    int fd = -1;
};
