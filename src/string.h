#pragma once
#include <cstddef>

class String
{
public:
    String();
    String(const String& other);
    String(String&& other) noexcept;
    ~String();
    String(const char* text);
    String& operator=(String other);
    void swap(String& other) noexcept;
    void push_back(char c);
    void append(const char* text);     
    void append(const String& other);  
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);
    std::size_t find(const String& substr) const;
    void print(const String& teat)
private:
    char* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};

