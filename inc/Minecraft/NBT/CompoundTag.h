#pragma once

#include "gsl/string_span"
#include <functional>
#include <map>
#include <memory>
#include <variant>

#include "Minecraft/NBT/Tag.h"

class CompoundTagVariant;

typedef gsl::basic_string_span<const char> string_span;
typedef std::map<std::string, CompoundTagVariant, std::less<>> TagMap;

class CompoundTag : public Tag {
#ifdef _WIN32
    typedef string_span StringView;
#else
    typedef const std::string& StringView;
#endif

    TagMap mTags;

public:
    CompoundTag();
    CompoundTag(CompoundTag&&) noexcept;
    virtual ~CompoundTag();
    float& putFloat(std::string, float);
    float getFloat(StringView) const;
    int& putInt(std::string, int);
    int getInt(StringView) const;
    short& putShort(std::string, short);
    short getShort(StringView) const;
    bool contains(StringView) const;
};

class CompoundTagVariant {
    typedef std::variant<CompoundTag> Variant;

public:
    Variant mTagStorage;

    CompoundTagVariant() {}
};