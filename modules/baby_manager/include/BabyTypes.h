#pragma once

namespace baby
{

#define BABY_MGR_ABOUT  wxT(			\
	"Baby manager\n"					\
	"Created by Alina Kolomiitseva\n"	\
	"Kharkiv 2021\n"					\
	"Version 1.0.0.1")					\

#define BABY_NAME wxT("Name")
#define BABY_GENDER wxT("Gender")
#define BABY_BLOOD wxT("Blood type")
#define BABY_APGAR wxT("Apgar score")

#define BABY_NAME_COLON BABY_NAME wxT(":")
#define BABY_GENDER_COLON BABY_GENDER wxT(":")
#define BABY_BLOOD_COLON BABY_BLOOD wxT(":")
#define BABY_APGAR_COLON BABY_APGAR wxT(":")

enum BabyControlId {
	ID_LIST_CTRL = 1000
};


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
		ar & blood_;
		ar & apgar_;
	}


	// Construction and destruction.
public:
	BabyData() = default;
	// Constructor.
	BabyData(std::wstring name, std::wstring gender, std::wstring blood, std::wstring apgar)
		: name_(name)
		, gender_(gender)
		, blood_(blood)
		, apgar_(apgar) {
	}

	// Public types.
public:
	// Name.
	std::wstring name_;
	// Gender.
	std::wstring gender_;
	// Blood.
	std::wstring blood_;
	// Apgar.
	std::wstring apgar_;
};

// Baby data pointer type.
using BabyDataPtr = std::shared_ptr<BabyData>;
// Baby hash type.
using BabyHash = std::vector<BabyDataPtr>;

};