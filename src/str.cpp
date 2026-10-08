#include "string.h"
#include <cctype>
#include <limits>
#include <ostream>
#include <stdexcept>

String::String()
{
    data_ = new char[2];
    size_ = 0;
    capacity_ = 1;

    data_[0] = '\0';
}

String::~String()
{
    delete[] data_;
}

String::String(const String& other)
{
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (capacity_ == 0)
    {
        capacity_ = 1;

    }
    
    data_ = new char[capacity_ + 1];

    for (std::size_t i = 0; i < size_; i++)
    {
        data_[i] = other.data_[i];
    }

    data_[size_] = '\0';
}

String::String(String&& other) noexcept
{
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

}

void String::swap(String& other) noexcept
{
    if (this == &other)
    {
        return;
    }

    char* temp = data_;
    data_ = other.data_;
    other.data_ = temp;

    size_ ^= other.size_;
    other.size_ ^= size_;
    size_ ^= other.size_;

    capacity_ ^= other.capacity_;
    other.capacity_ ^= capacity_;
    capacity_ ^= other.capacity_;
}

String& String::operator=(String other)
{
    swap(other);
    return *this;
}

std::size_t String::size() const noexcept
{
    return size_;
}

std::size_t String::capacity() const noexcept
{
    return capacity_;
}

bool String::empty() const noexcept
{
    return size_ == 0;
}

const char* String::c_str() const noexcept
{
    return data_ == nullptr ? "" : data_;
}

String::String(const char* text)
{
    if (text == nullptr)
    {
        throw std::invalid_argument("text is nullptr");
    }

    while (text[size_] != '\0')
    {
        size_++;
    }
    capacity_ = size_ == 0 ? 1 : size_;
    data_ = new char[capacity_ + 1];

    for (std::size_t i = 0; i < size_; i++)
    {
        data_[i] = text[i];
    }
    data_[size_] = '\0';
}

void String::push_back(char c)
{
    if (size_ == capacity_)
    {
        if (capacity_ > (std::numeric_limits<std::size_t>::max() - 1) / 2)
        {
            throw std::length_error("String is too large");
        }
        std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        char* new_data = new char[new_capacity + 1];
        for (std::size_t i = 0; i < size_; i++)
        {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    data_[size_] = c;
    size_++;
    data_[size_] = '\0';
}

void String::append(const char* text)
{
    String copy(text);

    for (std::size_t i = 0; i < copy.size_; i++)
    {
        push_back(copy.data_[i]);
    }
}

void String::append(const String& other)
{
    String copy(other);

    for (std::size_t i = 0; i < copy.size_; i++)
    {
        push_back(copy.data_[i]);
    }
}

std::size_t String::find(const String& substr) const
{
    if (substr.size_ == 0)
    {
        return 0;
    }

    if (substr.size_ > size_)
    {
        return npos;
    }

    std::size_t* prefix = new std::size_t[substr.size_]{};

    for (std::size_t i = 1, j = 0; i < substr.size_; i++)
    {
        while (j > 0 && substr.data_[i] != substr.data_[j])
        {
            j = prefix[j - 1];
        }

        if (substr.data_[i] == substr.data_[j])
        {
            j++;
        }

        prefix[i] = j;
    }
    for (std::size_t i = 0, j = 0; i < size_; i++)
    {
        while (j > 0 && data_[i] != substr.data_[j])
        {
            j = prefix[j - 1];
        }

        if (data_[i] == substr.data_[j])
        {
            j++;
        }

        if (j == substr.size_)
        {
            const std::size_t position = i + 1 - substr.size_;
            delete[] prefix;
            return position;
        }
    }

    delete[] prefix;
    return npos;
}

void String::print(std::ostream& out) const
{
    for (std::size_t i = 0; i < size_; i++)
    {
        out.put(data_[i]);
    }
}

String String::wrap(std::size_t width) const
{
    if (width == 0)
    {
        throw std::invalid_argument("width must be positive");
    }

    String result;
    std::size_t i = 0;
    std::size_t line_size = 0;

    while (i < size_)
    {
        while (i < size_ && std::isspace(static_cast<unsigned char>(data_[i])))
        {
            i++;
        }

        std::size_t start = i;

        while (i < size_ && !std::isspace(static_cast<unsigned char>(data_[i])))
        {
            i++;
        }

        std::size_t word_size = i - start;

        if (word_size == 0)
        {
            break;
        }

        if (line_size > 0)
        {
            if (line_size >= width || word_size > width - line_size - 1)
            {
                result.push_back('\n');
                line_size = 0;
            }
            else
            {
                result.push_back(' ');
                line_size++;
            }
        }

        for (std::size_t j = start; j < i; j++)
        {
            result.push_back(data_[j]);
        }

        line_size += word_size;
    }

    return result;
}
