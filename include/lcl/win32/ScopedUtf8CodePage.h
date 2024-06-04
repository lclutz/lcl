#pragma once

#include <Windows.h>

namespace lcl::win32
{

//! @brief Sets the code page to utf-8 for the enclosing scope
class ScopedUtf8CodePage final
{
  public:
    explicit ScopedUtf8CodePage()
        : previousCodePage(::GetConsoleOutputCP())
    {
        ::SetConsoleOutputCP(CP_UTF8);
    }

    ScopedUtf8CodePage(ScopedUtf8CodePage const &) = delete;
    ScopedUtf8CodePage(ScopedUtf8CodePage &&) noexcept = delete;

    ~ScopedUtf8CodePage()
    {
        ::SetConsoleOutputCP(previousCodePage);
    }

    ScopedUtf8CodePage &operator=(ScopedUtf8CodePage const &) = delete;
    ScopedUtf8CodePage &operator=(ScopedUtf8CodePage &&) noexcept = delete;

  private:
    UINT const previousCodePage;
};

} // namespace lcl::win32
