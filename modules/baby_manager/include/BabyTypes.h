#pragma once

namespace baby
{

// Event type.
enum BabyEvent {
	ID_ADD = 0,
	ID_UPDATE,
	ID_REMOVE,
	ID_EXIT,
	ID_ABOUT,
};

struct BabyData
{
	// Friend class.
	friend boost::serialization::access;
	// Serialization.
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & name_;
		ar & gender_;
		ar & age_;
		ar & cell_;
	}


	// Construction and destruction.
public:
	BabyData() = default;
	// Constructor.
	BabyData(std::wstring name, std::wstring gender, std::wstring age, std::wstring cell)
		: name_(name)
		, gender_(gender)
		, age_(age)
		, cell_(cell) {
	}

	// Public types.
public:
	// Animal name.
	std::wstring name_;
	// Animal gender.
	std::wstring  gender_;
	// Animal age.
	std::wstring age_;
	// Animal cell.
	std::wstring cell_;
};

// Baby data pointer type.
using BabyDataPtr = std::shared_ptr<BabyData>;
// Baby hash type.
using BabyHash = std::unordered_map<int, BabyDataPtr>;

};