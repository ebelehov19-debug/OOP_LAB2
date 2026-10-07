#include "string.h"

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

    for (std::size_t i = 0; i < size_; ++i)
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

String(const char* text)
{
    if(!text)
    {
        thorw std::invalid_argument("text is null ptr");
        size_ = 0;
        while(text[size_]!='\0')
        {
            size_++;
        }
        capacity_ = size_ == 0 ? 1 : size_;
        data_ = new char[capacity_+1];

        for(std::size_t i =0;i<size_;i++)
        {
            data_[i] = text[i];
        }
        data_[size_]='\0';
    }
}

void push_back(char c)
{
     if (text == nullptr)
    {
        throw std::invalid_argument("text is nullptr");
    }

    String copy(text);

    for (std::size_t i = 0; i < copy.size_; ++i)
    {
        push_back(copy.data_[i]);
    }
}
void String::append(const char* text)
{
    if(size_ == capacity_)
    {
        std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        char* new_data = new char[new_capacity + 1];
         for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }


}
void String::append(const String& other)
{
    append(other.data_ == nullptr ? "" : other.data_);
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

    for (std::size_t i = 1, j = 0; i < substr.size_; ++i)
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
    for (std::size_t i = 0, j = 0; i < size_; ++i)
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
