#include "MetaData.h"

namespace Engine
{
	namespace Meta
	{
		const Member* ReflectedType::GetMember(const std::string& name) const
		{
			Dictionary::const_iterator key = MemberKeys.find(name);

			if (key != MemberKeys.end())
				return &Members[key->second];

			return nullptr;
		}

		const Property* ReflectedType::GetProperty(const std::string& name) const
		{
			Dictionary::const_iterator key = PropertyKeys.find(name);

			if (key != PropertyKeys.end())
				return &Properties[key->second];

			return nullptr;
		}

		const Event* ReflectedType::GetEvent(const std::string& name) const
		{
			Dictionary::const_iterator key = EventKeys.find(name);

			if (key != EventKeys.end())
				return &Events[key->second];

			return nullptr;
		}

		const Function* ReflectedType::GetFunction(const std::string& name) const
		{
			Dictionary::const_iterator key = FunctionKeys.find(name);

			if (key != FunctionKeys.end())
				return &Functions[key->second];

			return nullptr;
		}

		const EnumItem* ReflectedType::GetEnumItem(int value) const
		{
			if (value < int(EnumItems.size()) && value >= 0)
				return &EnumItems[value];

			EnumDictionary::const_iterator item = UnorderedEnumItems.find(value);

			if (item != UnorderedEnumItems.end())
				return &item->second;

			return nullptr;
		}

		const EnumItem* ReflectedType::GetEnumItem(const std::string& name) const
		{
			Dictionary::const_iterator item = EnumKeys.find(name);

			if (item != EnumKeys.end())
				return GetEnumItem(item->second);

			return nullptr;
		}

		void ReflectedType::AddMember(const Member& member)
		{
			MemberKeys[member.Name] = int(Members.size());
			Members.push_back(member);
		}

		void ReflectedType::AddMember(const Property& member)
		{
			PropertyKeys[member.Name] = int(Properties.size());
			Properties.push_back(member);
		}

		void ReflectedType::AddMember(const Event& member)
		{
			EventKeys[member.Name] = int(Events.size());
			Events.push_back(member);
		}

		void ReflectedType::AddMember(const Function& member)
		{
			if (member.IsConstructor)
			{
				Constructor = member;

				return;
			}

			FunctionKeys[member.Name] = int(Functions.size());
			Functions.push_back(member);
		}

		void ReflectedType::AddValue(const EnumItem& item)
		{
			EnumKeys[item.Name] = item.Value;

			if (item.Value == int(EnumItems.size()))
			{
				EnumItems.push_back(item);

				return;
			}

			UnorderedEnumItems[item.Value] = item;
		}

		template <typename Container>
		void CopyData(const ReflectedType* meta, ReflectedType::Dictionary& keys, Container& members, const ReflectedType::Dictionary& otherKeys, const Container& otherMembers)
		{
			for (ReflectedType::Dictionary::const_iterator i = otherKeys.begin(); i != otherKeys.end(); ++i)
			{
				keys[i->first] = int(members.size());
				members.push_back(otherMembers[i->second]);

				members.back().InheritedBy = meta;
			}
		}

		void ReflectedType::CopyMembers(const ReflectedType* parent)
		{
			CopyData(this, MemberKeys, Members, parent->MemberKeys, parent->Members);
			CopyData(this, PropertyKeys, Properties, parent->PropertyKeys, parent->Properties);
			CopyData(this, EventKeys, Events, parent->EventKeys, parent->Events);
			CopyData(this, FunctionKeys, Functions, parent->FunctionKeys, parent->Functions);
		}

		const ReflectedType* ReflectedTypes::GetMeta(const std::string& name) const
		{
			Dictionary::const_iterator meta = MetaKeys.find(name);

			if (meta != MetaKeys.end())
				return Reflected[meta->second];

			return nullptr;
		}

		const ReflectedTypes* ReflectedTypes::GetScope(const std::string& name) const
		{
			Dictionary::const_iterator child = ScopeKeys.find(name);

			if (child != ScopeKeys.end())
				return ChildScopes[child->second];

			return nullptr;
		}

		ReflectedTypes* ReflectedTypes::GetScope(const std::string& name)
		{
			Dictionary::iterator child = ScopeKeys.find(name);

			if (child != ScopeKeys.end())
				return ChildScopes[child->second];

			return nullptr;
		}

		int ReflectedTypes::GetCount() const
		{
			return int(Reflected.size());
		}

		const ReflectedType* ReflectedTypes::Get(int index) const
		{
			if (index >= 0 && index < int(Reflected.size()))
				return Reflected[index];

			return nullptr;
		}

		int ReflectedTypes::GetScopeCount() const
		{
			return int(ChildScopes.size());
		}

		const ReflectedTypes* ReflectedTypes::GetScope(int index) const
		{
			if (index >= 0 && index < int(ChildScopes.size()))
				return ChildScopes[index];

			return nullptr;
		}

		const ReflectedTypes* ReflectedTypes::GetGlobalScope()
		{
			return &ReflectionGlobalScope::GlobalScope;
		}

		void ReflectedTypes::RegisterType(const ReflectedType* meta)
		{
			ReflectedTypes* currentNamespace = &ReflectionGlobalScope::GlobalScope;

			if (currentNamespace->Name == "")
				currentNamespace->Name = "Global";

			for (const std::string& name : meta->Namespaces)
			{
				ReflectedTypes* next = currentNamespace->GetScope(name);

				if (next == nullptr)
				{
					next = new ReflectedTypes();

					next->Name = name;
					currentNamespace->ScopeKeys[name] = int(currentNamespace->ChildScopes.size());
					currentNamespace->ChildScopes.push_back(next);
				}

				currentNamespace = next;
			}

			currentNamespace->MetaKeys[meta->Name] = int(currentNamespace->Reflected.size());
			currentNamespace->Reflected.push_back(meta);
		}
	}
}