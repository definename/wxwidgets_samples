#pragma once

namespace baby
{

#define BABY_NAME wxT("Name")
#define BABY_GENDER wxT("Gender")
#define BABY_BLOOD wxT("Blood type")
#define BABY_APGAR wxT("Apgar score")

#define BABY_NAME_COLON BABY_NAME wxT(":")
#define BABY_GENDER_COLON BABY_GENDER wxT(":")
#define BABY_BLOOD_COLON BABY_BLOOD wxT(":")
#define BABY_APGAR_COLON BABY_APGAR wxT(":")


// Data id.
enum BabyDataId {
	ID_NAME = 0,
	ID_GENDER,
	ID_BLOOD_TYPE,
	ID_APGAR_SCORE
};

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