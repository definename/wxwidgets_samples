#pragma once

namespace zoo
{

// Zoo event type.
// enum ZooEvent {
// 	ID_ADD = 0,
// 	ID_UPDATE,
// 	ID_REMOVE,
// 	ID_EXIT,
// 	ID_ABOUT,
// };

// struct ZooData
// {
// 	// Friend class.
// 	friend boost::serialization::access;
// 	// Serialization.
// 	template<class Archive>
// 	void serialize(Archive& ar, const unsigned int version) {
// 		ar & name_;
// 		ar & gender_;
// 		ar & age_;
// 		ar & cell_;
// 	}
// 
// 
// 	// Construction and destruction.
// public:
// 	ZooData() = default;
// 	// Constructor.
// 	ZooData(std::wstring name, std::wstring gender, std::wstring age, std::wstring cell)
// 		: name_(name)
// 		, gender_(gender)
// 		, age_(age)
// 		, cell_(cell) {
// 	}
// 
// 	// Public types.
// public:
// 	// Animal name.
// 	std::wstring name_;
// 	// Animal gender.
// 	std::wstring  gender_;
// 	// Animal age.
// 	std::wstring age_;
// 	// Animal cell.
// 	std::wstring cell_;
// };

// Zoo data pointer type.
using ZooDataPtr = std::shared_ptr<ZooData>;
// Zoo hash type.
using ZooHash = std::unordered_map<int, ZooDataPtr>;

}; // namespace zoo