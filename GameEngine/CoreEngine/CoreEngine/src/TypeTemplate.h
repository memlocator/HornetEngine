#pragma once

import <string>;

/*****
	TODO: Register new type to ObjectRegistration.cpp. Use the #include as a shortcut to open it.

	Remove this once registered.

	Warning: order of registration is crucial. Register this before any item that depends on it.
*****/

/*
	Quick note about reflected types and Lua:
	Types are expected to be passed around by value and Lua will create new copies of objects each time they are referenced from Lua.
	If you need an item to be passed around by reference consider turning it into a game object instead of a type.
	Only explicitly reflected items will be usable from Lua and file I/O. Reflection isn't a requirement for every item in a class.

	It is highly recommended to create a separate .meta.cpp file for each reflected enum, type, and object class.
*/

/*
	CoreType is inherited purely for ease of use with Handle<> objects internally.
	It allows Lua's binding code to pass it around without caring what type it is, but still maintaining the capability to deduce types.
	To create an object of this type in Lua, use "TypeName()"
*/
class TemplateType
{
public:
	int ExampleMember;

	// Example Constructor
	TemplateType(int exampleParam, int exampleParam2 = 0) {} TemplateType() {}

	// Example operator overload; used internally by Lua's metatable dictionary of operator overloads
	int operator-() const { return -ExampleMember; }

	// Example string conversion; used internally by Lua's tostring() if reflected
	operator std::string() const { return ""; }
};

// Example inheritance
struct InheritedTemplate : public TemplateType
{
	// Example function with multiple overloads
	void ExampleMethod() {}
	static int ExampleMethod(int arg1) { return arg1; }
};