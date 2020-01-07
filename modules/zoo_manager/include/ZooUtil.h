#pragma once

namespace zoo
{

// Zoo db file path.
const wxFileName zoo_db_path(wxT("zoo_db.dat"));

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

}; // namespace zoo