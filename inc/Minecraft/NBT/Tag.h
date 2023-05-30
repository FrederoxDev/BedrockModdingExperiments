#pragma once

#include <string>

class Tag {
public:
    enum class Type : unsigned char {
        End,
        Byte,
        Short,
        Int,
        Int64,
        Float,
        Double,
        ByteArray,
        String,
        List,
        Compound,
        IntArray
    };

    virtual ~Tag() = default;
};