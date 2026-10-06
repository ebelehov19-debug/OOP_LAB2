#pragma once
#include <cstddef>

class String
{
public:
    String();
    String(const String& other);
    String(String&& other) noexcept;
    ~String();

    String& operator=(String other);
    void swap(String& other) noexcept;

private:
    char* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};
