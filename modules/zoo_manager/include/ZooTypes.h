#pragma once

namespace zoo
{

struct ZooData
{
	//! Friend class.
	friend boost::serialization::access;
	//! Serialization.
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & name_;
		ar & gender_;
		ar & age_;
		ar & cell_;
	}


	// Construction and destruction.
public:
	ZooData() = default;
	// Constructor.
	ZooData(std::wstring name, std::wstring gender, std::wstring age, std::wstring cell)
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

// Zoo data pointer type.
using ZooDataPtr = wxSharedPtr<ZooData>;

template <typename TOArch, typename TSource, typename TTarget>
void SerializeTo(const TSource& source, TTarget& target) {
	TOArch oa(target);
	oa << source;
}

template <typename TIArch, typename TSource, typename TTarget>
void DeserializeFrom(TSource& source, TTarget& target) {
	TIArch ia(source);
	ia >> target;
}

}; // namespace zoo