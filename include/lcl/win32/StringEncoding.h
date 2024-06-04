#pragma once

#include <Windows.h>

#include <string>

namespace lcl::win32::StringEncoding
{

namespace
{

[[nodiscard]] inline std::string Wc2Mb(UINT const mbCodePage, std::wstring const &wstr)
{
    auto result = std::string{};

    auto const flags = DWORD{0};

    auto const size = ::WideCharToMultiByte(         //
        mbCodePage, flags,                           //
        wstr.c_str(), static_cast<int>(wstr.size()), //
        nullptr, 0,                                  //
        nullptr, nullptr);

    if (0 < size)
    {
        result.resize(size);

        ::WideCharToMultiByte(                              //
            mbCodePage, flags,                              //
            wstr.c_str(), static_cast<int>(wstr.size()),    //
            result.data(), static_cast<int>(result.size()), //
            nullptr, nullptr);
    }

    return result;
}

[[nodiscard]] inline std::wstring Mb2Wc(UINT const mbCodePage, std::string const &str)
{
    auto result = std::wstring{};

    auto const flags = DWORD{0};

    auto const size = ::MultiByteToWideChar(       //
        mbCodePage, flags,                         //
        str.c_str(), static_cast<int>(str.size()), //
        nullptr, 0);

    if (0 < size)
    {
        result.resize(size);

        ::MultiByteToWideChar(                         //
            mbCodePage, flags,                         //
            str.c_str(), static_cast<int>(str.size()), //
            result.data(), static_cast<int>(result.size()));
    }

    return result;
}

} // namespace

[[nodiscard]] inline std::wstring Utf8ToUtf16Le(std::string const &utf8Str)
{
    return Mb2Wc(CP_UTF8, utf8Str);
}

[[nodiscard]] inline std::string Utf16LeToUtf8(std::wstring const &utf16Str)
{
    return Wc2Mb(CP_UTF8, utf16Str);
}

[[nodiscard]] inline std::wstring MultiByteToUtf16Le(std::string const &mbStr)
{
    return Mb2Wc(CP_ACP, mbStr);
}

[[nodiscard]] inline std::string Utf16LeToMultiByte(std::wstring const &utf16Str)
{
    return Wc2Mb(CP_ACP, utf16Str);
}

} // namespace lcl::win32::StringEncoding
