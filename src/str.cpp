#include "string.h"

String::String()
{
    data_ = new char[2];
    size_ = 0;
    capacity_ = 1;

    data_[0] = '\0';
}

String:: ~String()
{
    delete [] data_;
}

String:: String(const String& other)
{
    size_ = other.size_;
    capacity_ = other.capacity_;
    if(capacity_ == 0)
    {
        capacity_ = 1;

    }
    
    data_ = new char[capacity_+1];

    for(size_t i =0;i<size_;i++)
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