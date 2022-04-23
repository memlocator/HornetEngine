#pragma once

#include <algorithm>

#include "Reflected.h"
#include "LuaTypeBinding.h"
#include "../Event.h"

#undef max

namespace Engine
{
	namespace Lua
	{
		const bool TestFunctions = false;

		typedef int(*LuaFunction)(lua_State*);
		typedef bool(*LuaCheckFunction)(lua_State*);

		struct LuaBinding
		{
			struct BoundMember
			{
				LuaFunction Getter = nullptr;
				LuaFunction Setter = nullptr;

				void Validate() const;
			};

			struct BoundFunction
			{
				LuaFunction Callback = nullptr;

				void Validate() const;
			};

			struct BoundEvent
			{
				LuaFunction Connect = nullptr;
				LuaFunction Disconnect = nullptr;
				LuaFunction Wait = nullptr;

				void Validate() const;
			};

			struct BoundObject
			{
				LuaFunction Create = nullptr;

				void Validate() const;
			};
		};

		struct LuaBinder
		{
			template <typename Type>
			static const Meta::ReflectedType* GetMeta()
			{
				typedef std::remove_cvref_t<Type> UnqualifiedType;

				return Meta::Reflected<UnqualifiedType>::GetMeta();
			}

			template <typename Type>
			static bool ArgumentMatches(const Meta::ReflectedType* found)
			{
				return found == GetMeta<Type>();
			}

			template <typename Type>
			struct TypeHolder
			{
				Type GetType();
			};

			lua_State* GetGlobalLuaState();
			int RegisterConnectedFunction(lua_State* lua);

			template <typename... Arguments>
			static bool ArgumentsMatch(const Meta::ReflectedType** arguments, int count)
			{
				if (sizeof...(Arguments) != count) return false;

				auto matches = []<typename T, T... Indices, typename... Holders>(const std::integer_sequence<T, Indices...>&indices, const Meta::ReflectedType** arguments, Holders... types) -> bool
				{
					auto matches = []<typename Type>(TypeHolder<Type>, const Meta::ReflectedType* argument) -> bool
					{
						return ArgumentMatches<Type>(argument);
					};
					
					return (matches(types, arguments[Indices]) && ...);
				};

				std::tuple<TypeHolder<Arguments>...> argumentsTuple;

				return std::apply([&matches, arguments]<typename... Holders>(Holders... types) -> bool { return matches(std::make_index_sequence<sizeof...(Arguments)>{}, arguments, types...); }, argumentsTuple);
			}

			template <typename ClassType>
			struct BindObjectFactory
			{
				static int FactoryFunction(lua_State* lua)
				{
					return 1;
				}

				template <typename... Arguments>
				static void FactoryFunction(lua_State* lua, const Arguments&... arguments)
				{

				}
			};

			template <typename ClassType>
			struct BindTypeFactory
			{
				static int FactoryFunction(lua_State* lua)
				{
					return 1;
				}

				template <typename... Arguments>
				static void FactoryFunction(lua_State* lua, const Arguments&... arguments)
				{

				}
			};

			template <typename ClassType, typename Type, auto PointerData>//typename PointerType, PointerType Pointer>
			struct BindMember
			{
				typedef decltype(PointerData) Traits;
				typedef Traits::PointerType PointerType;

				static inline const PointerType Pointer = PointerData.Pointer;

				template <bool IsStatic, bool IsConst>
				struct Bind;

				template <>
				struct Bind<false, false>
				{
					static int Getter(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						ClassType* pointer = object.get();

						BindType<Clean<Type>>::Push(lua, (pointer->*Pointer));

						return 1;
					}

					static int Setter(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						ClassType* pointer = object.get();

						(pointer->*Pointer) = BindType<Clean<Type>>::WithDefault<false>::Pop<void>(lua, 2);

						return 0;
					}
				};

				template <>
				struct Bind<true, false>
				{
					static int Getter(lua_State* lua)
					{
						BindType<Clean<Type>>::Push(lua, *Pointer);

						return 1;
					}

					static int Setter(lua_State* lua)
					{
						int top = 1;// lua_gettop(lua)

						*Pointer = BindType<Clean<Type>>::WithDefault<false>::Pop<void>(lua, top);

						return 0;
					}
				};

				template <>
				struct Bind<false, true>
				{
					static int Getter(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						const ClassType* pointer = object.get();

						BindType<Clean<Type>>::Push(lua, (pointer->*Pointer));

						return 1;
					}

					static int Setter(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						const ClassType* pointer = object.get();

						(pointer->*Pointer) = BindType<Clean<Type>>::WithDefault<false>::Pop<void>(lua, 2);

						return 0;
					}
				};
			};

			template <typename Type>
			using Clean = std::remove_cvref_t<Type>;

			template <typename ClassType, typename Type, typename PointerType, auto Pointer>
			struct BindGetter
			{
				template <bool IsStatic, bool IsConst>
				struct Bind;

				template <>
				struct Bind<false, false>
				{
					static const inline int MinimumArguments = 1;
					static const inline int MaximumArguments = 1;

					static constexpr int GetArguments() { return MaximumArguments; }

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						return ArgumentsMatch<ClassType>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						ClassType* pointer = object.get();

						BindType<Clean<Type>>::Push(lua, (pointer->*Pointer)());

						return 1;
					}
				};

				template <>
				struct Bind<true, false>
				{
					static const inline int MinimumArguments = 0;
					static const inline int MaximumArguments = 1;

					static constexpr int GetArguments() { return MaximumArguments; }

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						if (count == 1)
							return ArgumentMatches<ClassType>(arguments[0]);

						return ArgumentsMatch<>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						BindType<Clean<Type>>::Push(lua, Pointer());

						return 1;
					}
				};

				template <>
				struct Bind<false, true>
				{
					static const inline int MinimumArguments = 1;
					static const inline int MaximumArguments = 1;

					static constexpr int GetArguments() { return MaximumArguments; }

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						return ArgumentsMatch<ClassType>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						const ClassType* pointer = object.get();

						BindType<Clean<Type>>::Push(lua, (pointer->*Pointer)());

						return 1;
					}
				};
			};

			template <typename ClassType, typename Type, typename PointerType, auto Pointer>
			struct BindSetter
			{
				template <bool IsStatic, bool IsConst>
				struct Bind;

				template <>
				struct Bind<false, false>
				{
					static const inline int MinimumArguments = 2;
					static const inline int MaximumArguments = 2;

					static constexpr int GetArguments() { return MaximumArguments; }

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						return ArgumentsMatch<ClassType, Clean<Type>>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						ClassType* pointer = object.get();

						(pointer->*Pointer)(BindType<Clean<Type>>::WithDefault<false>::Pop<void>(lua, 2));

						return 0;
					}
				};

				template <>
				struct Bind<true, false>
				{
					static const inline int MinimumArguments = 1;
					static const inline int MaximumArguments = 2;

					static constexpr int GetArguments() { return MaximumArguments; }

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						if (count == 2)
							return ArgumentMatches<ClassType, Clean<Type>>(arguments[0]);

						return ArgumentsMatch<Clean<Type>>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						int top = 1;// lua_gettop(lua)

						Pointer(BindType<Clean<Type>>::WithDefault<false>::Pop<void>(lua, top));

						return 0;
					}
				};

				template <>
				struct Bind<false, true>
				{
					static const inline int MinimumArguments = 2;
					static const inline int MaximumArguments = 2;

					static constexpr int GetArguments() { return MaximumArguments; }

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						return ArgumentsMatch<ClassType, Clean<Type>>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						const ClassType* pointer = object.get();

						(pointer->*Pointer)(BindType<Clean<Type>>::WithDefault<false>::Pop<void>(lua, 2));

						return 0;
					}
				};
			};

			template <typename ReturnType>
			struct CallbackWrapper
			{
				template <auto Function, typename PointerType, typename... Arguments>
				static int Invoke(PointerType pointer, lua_State* lua, const Arguments&... arguments)
				{
					BindType<Clean<ReturnType>>::Push(lua, (pointer->*Function)(arguments...));

					return 1;
				}

				template <auto Function, typename... Arguments>
				static int Invoke(lua_State* lua, const Arguments&... arguments)
				{
					BindType<Clean<ReturnType>>::Push(lua, (*Function)(arguments...));

					return 1;
				}
			};

			template <>
			struct CallbackWrapper<void>
			{
				template <auto Function, typename PointerType, typename... Arguments>
				static int Invoke(PointerType pointer, lua_State* lua, const Arguments&... arguments)
				{
					(pointer->*Function)(arguments...);

					return 0;
				}

				template <auto Function, typename... Arguments>
				static int Invoke(lua_State* lua, const Arguments&... arguments)
				{
					(*Function)(arguments...);

					return 0;
				}
			};

			template <auto Pointer, int MinimumArguments, int MaximumArguments, typename ClassType, typename ReturnType, typename... Arguments>
			struct BindOverload
			{
				template <bool IsStatic, bool IsConst>
				struct Bind;

				template <>
				struct Bind<false, false>
				{
					static const inline int MinimumArguments = MinimumArguments + 1;
					static const inline int MaximumArguments = MaximumArguments + 1;

					static constexpr int GetArguments()
					{
						return MaximumArguments;
					}

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						return ArgumentsMatch<ClassType, Clean<typename Arguments::Type>...>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						ClassType* pointer = object.get();

						auto invoke = []<typename... Type>(lua_State * lua, ClassType* pointer, const Type&... arguments)
						{
							return CallbackWrapper<ReturnType>::template Invoke<Pointer, ClassType*, Type...>(pointer, lua, arguments...);
						};

						auto pop = []<typename Argument>(lua_State* lua, Argument)
						{
							return std::move(BindType<Clean<Argument::Type>>::WithDefault<Argument::HasDefault>::Pop<Argument::DefaultValue>(lua, Argument::Index));
						};

						return invoke(lua, pointer, pop(lua, Arguments{})...);
					}
				};

				template <>
				struct Bind<true, false>
				{
					static const inline int MinimumArguments = MinimumArguments;
					static const inline int MaximumArguments = MaximumArguments + 1;

					static constexpr int GetArguments()
					{
						return MaximumArguments;
					}

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						if (count == sizeof...(Arguments) + 1)
							return ArgumentsMatch<ClassType, Clean<typename Arguments::Type>...>(arguments, count);

						return ArgumentsMatch<Clean<typename Arguments::Type>...>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						int top = 1;// lua_gettop(lua)

						auto invoke = []<typename... Type>(lua_State* lua, const Type&... arguments)
						{
							return CallbackWrapper<ReturnType>::template Invoke<Pointer, Type...>(lua, arguments...);
						};

						auto pop = []<typename Argument>(lua_State* lua, Argument)
						{
							return std::move(BindType<Clean<Argument::Type>>::WithDefault<Argument::HasDefault>::Pop<Argument::DefaultValue>(lua, Argument::Index));
						};

						return invoke(lua, pop(lua, Arguments{})...);
					}
				};

				template <>
				struct Bind<false, true>
				{
					static const inline int MinimumArguments = MinimumArguments + 1;
					static const inline int MaximumArguments = MaximumArguments + 1;

					static constexpr int GetArguments()
					{
						return MaximumArguments;
					}

					static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
					{
						return ArgumentsMatch<ClassType, Clean<typename Arguments::Type>...>(arguments, count);
					}

					static int Callback(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						const ClassType* pointer = object.get();


						auto invoke = []<typename... Type>(lua_State* lua, const ClassType* pointer, const Type&... arguments)
						{
							return CallbackWrapper<ReturnType>::template Invoke<Pointer, const ClassType*, Type...>(pointer, lua, arguments...);
						};

						auto pop = []<typename Argument>(lua_State* lua, Argument)
						{
							return std::move(BindType<Clean<Argument::Type>>::WithDefault<Argument::HasDefault>::Pop<Argument::DefaultValue>(lua, Argument::Index));
						};

						return invoke(lua, pointer, pop(lua, Arguments{})...);
					}
				};
			};
			template <int MinimumArguments, int MaximumArguments, typename ClassType, typename... Arguments>
			struct BindConstructorOverload
			{
				static const inline int MinimumArguments = MinimumArguments;
				static const inline int MaximumArguments = MaximumArguments;

				static constexpr int GetArguments()
				{
					return MaximumArguments;
				}

				static bool MatchesOverload(const Meta::ReflectedType** arguments, int count)
				{
					return ArgumentsMatch<Clean<Arguments::Type>...>(arguments, count);
				}

				template <bool IsObject>
				static int Callback(lua_State* lua)
				{
					auto pop = []<typename Argument>(lua_State * lua, Argument)
					{
						return std::move(BindType<Clean<Argument::Type>>::WithDefault<Argument::HasDefault>::Pop<Argument::DefaultValue>(lua, Argument::Index));
					};

					BindObjectFactory<ClassType>::template FactoryFunction<typename Arguments::Type...>(lua, pop(lua, Arguments{})...);

					return 1;
				}

				template <>
				static int Callback<false>(lua_State* lua)
				{
					auto pop = []<typename Argument>(lua_State * lua, Argument)
					{
						return std::move(BindType<Clean<Argument::Type>>::WithDefault<Argument::HasDefault>::Pop<Argument::DefaultValue>(lua, Argument::Index));
					};

					BindTypeFactory<ClassType>::template FactoryFunction<Arguments::Type...>(lua, pop(lua, Arguments{})...);

					return 1;
				}
			};

			static const Meta::ReflectedType* GetArgumentType(int index) { return nullptr; }

			template <typename... Overloads>
			struct ArgumentCounter;

			template <typename Overload, typename... Overloads>
			struct ArgumentCounter<Overload, Overloads...>
			{
				static consteval int GetMaxArguments()
				{
					constexpr int arguments = Overload::GetArguments();

					return std::max(arguments, ArgumentCounter<Overloads...>::GetMaxArguments());
				}
			};

			template <>
			struct ArgumentCounter<>
			{
				static consteval int GetMaxArguments()
				{
					return 0;
				}
			};

			template <typename... Overloads>
			struct BindFunction
			{
				static inline const int MaxArguments = std::max(1, ArgumentCounter<Overloads...>::GetMaxArguments());

				static int Callback(lua_State* lua)
				{
					const Meta::ReflectedType* arguments[MaxArguments] = { nullptr };
					int stackTop = 0; // lua_gettop(lua);
					int returnedValues = 0;

					for (int i = 0; i < stackTop && i < MaxArguments; ++i)
						arguments[i] = GetArgumentType(i);

					auto attemptOverload = [lua, &arguments, &returnedValues, stackTop]<typename Overload>(Overload)
					{
						if (TestFunctions || Overload::MatchesOverload(arguments, stackTop))
						{
							returnedValues = Overload::Callback(lua);

							return true;
						}

						return false;
					};

					std::tuple<Overloads...> overloadTuple;

					std::apply([&attemptOverload](Overloads... overload) { (attemptOverload(overload) || ...); }, overloadTuple);

					return returnedValues;
				}

				template <bool IsObject>
				struct Constructor;

				template <>
				struct Constructor<true>
				{
					static int Callback(lua_State* lua)
					{
						const Meta::ReflectedType* arguments[MaxArguments] = { nullptr };
						int stackTop = 0; // lua_gettop(lua);
						int returnedValues = 0;
						
						for (int i = 0; i < stackTop && i < MaxArguments; ++i)
							arguments[i] = GetArgumentType(i);
						
						auto attemptOverload = [lua, &arguments, &returnedValues, stackTop]<typename Overload>(Overload)
						{
							if (TestFunctions || Overload::MatchesOverload(arguments, stackTop))
							{
								returnedValues = Overload::Callback<true>(lua);
						
								return true;
							}
						
							return false;
						};
						
						std::tuple<Overloads...> overloadTuple;
						
						std::apply([&attemptOverload](Overloads... overload) { (attemptOverload(overload) || ...); }, overloadTuple);

						return 0;
					}
				};

				template <>
				struct Constructor<false>
				{
					static int Callback(lua_State* lua)
					{
						const Meta::ReflectedType* arguments[MaxArguments] = { nullptr };
						int stackTop = 0; // lua_gettop(lua);
						int returnedValues = 0;
						
						for (int i = 0; i < stackTop && i < MaxArguments; ++i)
							arguments[i] = GetArgumentType(i);
						
						auto attemptOverload = [lua, &arguments, &returnedValues, stackTop]<typename Overload>(Overload)
						{
							if (TestFunctions || Overload::MatchesOverload(arguments, stackTop))
							{
								returnedValues = Overload::Callback<false>(lua);
						
								return true;
							}
						
							return false;
						};
						
						std::tuple<Overloads...> overloadTuple;
						
						std::apply([&attemptOverload](Overloads... overload) { (attemptOverload(overload) || ...); }, overloadTuple);

						return 0;
					}
				};
			};

			template <typename PointerType, PointerType Pointer, typename ClassType, typename... Arguments>
			struct BindEvent
			{
				typedef Engine::Event<typename Arguments::Type...> BoundEvent;

				void ConnectEvent(lua_State* lua, BoundEvent& event)
				{
					int functionId = RegisterConnectedFunction(lua);

					int connection = Pointer->Connect(
						[functionId](Arguments::Type... arguments)
						{
							lua_State* lua = GetGlobalLuaState();

							FetchConnectedFunction(lua, functionId);

							(CoreTypes<Arguments::Type>::Push(lua, arguments), ...);

							lua_call(lua, sizeof...(Arguments), 1);

							bool keepConnectionAlive = true;

							if (lua_isboolean(lua, -1))
								keepConnectionAlive = lua_toboolean(lua, -1) == 1;

							return keepConnectionAlive;
						}
					);

					lua_pushinteger(lua, connection);
				}

				template <bool IsStatic>
				struct Bind;

				template <>
				struct Bind<true>
				{
					static int Connect(lua_State* lua)
					{
						ConnectEvent(*Pointer);

						return 1;
					}

					static int Disconnect(lua_State* lua)
					{
						return 0;
					}

					static int Wait(lua_State* lua)
					{
						return 0;
					}
				};

				template <>
				struct Bind<false>
				{
					static int Connect(lua_State* lua)
					{
						const std::shared_ptr<ClassType>& object = GetObject<ClassType>(lua);
						const ClassType* pointer = object.get();

						ConnectEvent(pointer->*Pointer);

						return 0;
					}

					static int Disconnect(lua_State* lua)
					{
						return 0;
					}

					static int Wait(lua_State* lua)
					{
						return 0;
					}
				};
			};
		};
	}

	namespace Meta
	{
		typedef Lua::LuaBinding ActiveBinding;
	}

	namespace Reflection
	{
		typedef Lua::LuaBinder ActiveBinder;
	}
}