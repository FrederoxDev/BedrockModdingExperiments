#pragma once

#include <string>
#include <memory>

class IDataInput;
class IDataOutput;
class PrintStream;

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

public:
	virtual ~Tag();
	virtual void deleteChildren();
	virtual bool equals(const Tag&) const;
	virtual void print(PrintStream&) const;
	virtual void print(const std::string&, PrintStream&) const;

	// Begin Non-Virtual Functions
	static std::unique_ptr<Tag, std::default_delete<Tag>> readNamedTag(IDataInput&, std::string&);
	static void writeNamedTag(const std::string&, const Tag&, IDataOutput&);
	static std::unique_ptr<Tag,std::default_delete<Tag>> newTag(Tag::Type);
	static std::string getTagName(Tag::Type);

	// Begin Variables
	// public: static class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const Tag::NullString;
};