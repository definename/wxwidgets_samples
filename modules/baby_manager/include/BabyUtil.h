#pragma once

namespace baby
{

// Database file path.
const wxFileName db_path(wxT("zoo_db.dat"));

// Serialization interface.
template <typename TOArch, typename TSource, typename TTarget>
void SerializeTo(const TSource& source, TTarget& target) {
	TOArch oa(target);
	oa << source;
}

// De-serialization interface.
template <typename TIArch, typename TSource, typename TTarget>
void DeserializeFrom(TSource& source, TTarget& target) {
	TIArch ia(source);
	ia >> target;
}

};