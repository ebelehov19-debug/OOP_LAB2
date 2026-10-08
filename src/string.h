#pragma once
#include <cstddef>
#include <iosfwd>

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
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;
    const char* c_str() const noexcept;
    void push_back(char c);
    void append(const char* text);
    void append(const String& other);
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);
    std::size_t find(const String& substr) const;
    void print(std::ostream& out) const;
    String wrap(std::size_t width) const;
private:
    char* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};

