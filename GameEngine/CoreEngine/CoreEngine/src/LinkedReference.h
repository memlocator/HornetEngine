#pragma once

#include <vector>

template <typename ReferenceType, typename OtherReferenceType>
class LinkedReference
{
public:
	typedef LinkedReference<OtherReferenceType, ReferenceType> PairReference;

	ReferenceType ThisReference;
	PairReference* OtherReference = nullptr;
	int ReferenceIndex = -1;

	LinkedReference() {}
	LinkedReference(const ReferenceType& thisReference) : ThisReference(thisReference) {}
	LinkedReference(LinkedReference&& oldReference) : ThisReference(oldReference.ThisReference), ReferenceIndex(oldReference.ReferenceIndex)
	{
		OtherReference = oldReference.OtherReference;
		ReferenceIndex = oldReference.ReferenceIndex;

		if (oldReference.OtherReference)
			oldReference.OtherReference->MoveReference(this);

		oldReference.OtherReference = nullptr;
		oldReference.ReferenceIndex = -1;
	}

	virtual ~LinkedReference()
	{
		if (OtherReference != nullptr)
			OtherReference->Disconnect(this);
	}

	virtual ReferenceType Get(LinkedReference* otherReference)
	{
		return ThisReference;
	}

protected:
	void Disconnect()
	{
		OtherReference = nullptr;
		ReferenceIndex = -1;
	}

	virtual int Disconnect(const LinkedReference* otherReference)
	{
		int referred = ReferenceIndex;

		Disconnect();

		return referred;
	}

	virtual std::pair<int, int*> AddReference(PairReference* otherReference)
	{
		OtherReference = otherReference;
		
		return std::make_pair(-1, &ReferenceIndex);
	}

	virtual void MoveReference(LinkedReference* otherReference)
	{
		OtherReference = otherReference;
	}

	virtual void SetIndex(LinkedReference* otherReference, int newIndex)
	{
		ReferenceIndex = newIndex;
	}

	virtual int GetIndex(LinkedReference* otherReference)
	{
		return ReferenceIndex;
	}

	LinkedReference& operator=(const ReferenceType& thisReference) { ThisReference = thisReference; }

	LinkedReference& operator=(PairReference& otherReference)
	{
		if (OtherReference != nullptr)
			OtherReference->Disconnect(this);

		Disconnect();

		auto thisRef = AddReference(otherReference);
		auto otherRef = otherReference->AddReference(this);

		*thisRef.second = otherRef.first;
		*otherRef.second = thisRef.first;
	}

	LinkedReference& operator=(LinkedReference&& oldReference)
	{
		if (OtherReference != nullptr)
			OtherReference->Disconnect(this);

		OtherReference = oldReference.OtherReference;
		ReferenceIndex = oldReference.ReferenceIndex;

		if (oldReference.OtherReference)
			oldReference.OtherReference->MoveReference(this);

		oldReference.OtherReference = nullptr;
		oldReference.ReferenceIndex = -1;
	}

	OtherReferenceType* operator->()
	{
		if (OtherReference != nullptr)
			return OtherReference->Get(this);

		return nullptr;
	}
};

template <typename ReferenceType, typename OtherReferenceType>
class LinkedMultiReference : LinkedReference<ReferenceType, OtherReferenceType>
{
public:
	typedef LinkedReference<ReferenceType, OtherReferenceType> ParentReference;

	std::vector<std::pair<PairReference*, int>> OtherReferences;

	LinkedMultiReference() {}
	LinkedMultiReference(const ReferenceType& thisReference) : ParentReference(thisReference) {}
	LinkedMultiReference(LinkedMultiReference&& oldReference) : ThisReference(oldReference.ThisReference)
	{
		MoveAllReferences(oldReference);
	}

	virtual ~LinkedReference()
	{
		for (auto& otherReference : OtherReferences)
			otherReference->Disconnect(this);
	}

	void Add(LinkedReference* otherReference)
	{
		auto thisRef = AddReference(otherReference);
		auto otherRef = otherReference->AddReference(this);

		*thisRef.second = otherRef.first;
		*otherRef.second = thisRef.first;
	}

	virtual ReferenceType Get(LinkedReference* otherReference)
	{
		return OtherReferences[otherReference->GetIndex(this)].first;
	}

	ReferenceType Get(int index)
	{
		return OtherReferences[index].first;
	}

	int GetCount() const
	{
		return (int)OtherReferences.size();
	}

protected:
	void Disconnect(int index)
	{
		OtherReferences.back().second = index;

		std::swap(OtherReferences[index], OtherReferences.back());

		OtherReferences.pop_back();
	}

	virtual int Disconnect(const LinkedReference* otherReference)
	{
		int index = otherReference->GetIndex();
		int referred = OtherReferences[index].second;

		Disconnect(index);

		return referred;
	}

	virtual std::pair<int, int*> AddReference(PairReference* otherReference)
	{
		OtherReferences.push_back(std::make_pair(otherReference, -1));

		return std::make_pair((int)OtherReferences.size() - 1, &OtherReferences.back().second);
	}

	virtual void MoveReference(LinkedReference* otherReference)
	{
		OtherReferences[otherReference->GetIndex(this)].first = otherReference;
	}

	virtual void SetIndex(LinkedReference* otherReference, int newIndex)
	{
		OtherReferences[otherReference->GetIndex(this)].second = newIndex;
	}

	virtual int GetIndex(LinkedReference* otherReference)
	{
		return OtherReferences[otherReference->GetIndex(this)].second;
	}

	LinkedReference& operator=(const ReferenceType& thisReference) { ThisReference = thisReference; }

	LinkedReference& operator=(LinkedReference&& oldReference)
	{
		for (auto& otherReference : OtherReferences)
			otherReference->Disconnect(this);

		MoveAllReferences(oldReference);
	}

private:
	void MoveAllReferences(LinkedMultiReference&& oldReference)
	{
		OtherReferences = std::move(oldReference.OtherReferences);

		for (auto& otherReference : OtherReferences)
			otherReference.first->MoveReference(this);
	}
};