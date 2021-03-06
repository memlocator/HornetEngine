#pragma once

import <string>;
import <functional>;
import <vector>;
import <source_location>;
import <sstream>;

class JsonParserException : public std::exception
{
public:
	const char* Message = nullptr;
	std::source_location Caller;
	std::string ErrorMessage;

	JsonParserException(const char* message, const std::source_location& caller = std::source_location::current()) throw()
	{
		Caller = caller;

		std::stringstream error;

		error << Caller.file_name() << " [" << Caller.line() << "]: " << Caller.function_name() << ": " << Message;

		ErrorMessage = error.str();
	}
	JsonParserException(const std::string& message, const std::source_location& caller = std::source_location::current()) throw()
	{
		Caller = caller;

		std::stringstream error;

		error << Caller.file_name() << " [" << Caller.line() << "]: " << Caller.function_name() << ": " << Message;

		ErrorMessage = error.str();
	}

	virtual const char* what() throw()
	{
		return ErrorMessage.c_str();
	}
};

class JsonParser
{
public:
	typedef std::vector<char> Buffer;
	typedef std::function<void(const std::string& key)> KeyCallback;
	typedef std::function<void(int index)> IndexCallback;
	typedef std::function<void(float value, char modifier)> NumberCallback;
	typedef std::function<void(const std::string& value)> StringCallback;
	typedef std::function<void(bool value)> BoolCallback;
	typedef std::function<void()> PopCallback;

	KeyCallback ReadKey = DefaultReadKey;
	IndexCallback ReadIndex = DefaultReadIndex;
	NumberCallback ReadNumber = DefaultReadNumber;
	StringCallback ReadString = DefaultReadString;
	BoolCallback ReadBool = DefaultReadBool;
	BoolCallback PushContainer = DefaultPushContainer;
	PopCallback PopContainer = DefaultPopContainer;

	Buffer InputBuffer;
	std::string Input;

	JsonParser(const std::string& data, bool isPath = true);

	void Parse();

private:
	struct StackItem
	{
		int Index = 0;
		bool IsArray = false;
	};
	
	typedef std::vector<StackItem> ObjectStack;

	std::string FilePath = "JSON";
	ObjectStack Stack;
	int Index = 0;
	int LineStart = 0;
	int LineNumber = 1;

	void SkipWhitespace();
	void Throw(const std::string& error);
	void ReadArrayItem();
	void ReadDictionaryItem();
	void ReadArrayNumber();
	void ReadRawNumber();
	void ReadTrue();
	void ReadFalse();
	std::string ReadRawString();
	void CheckForComma();
	void FinishNumber(int start);
	bool Finished();

	static void DefaultReadKey(const std::string& key) {}
	static void DefaultReadIndex(int index) {}
	static void DefaultReadNumber(float value, char modifier) {}
	static void DefaultReadString(const std::string& value) {}
	static void DefaultReadBool(bool value) {}
	static void DefaultPushContainer(bool isArray) {}
	static void DefaultPopContainer() {}
};