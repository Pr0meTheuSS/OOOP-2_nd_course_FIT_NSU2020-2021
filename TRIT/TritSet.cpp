#include "TritSet.h"


//Необходимо вынести выравнивание трит сетов по размерности в отдельный метод ?

TritSet::TritSet(CONDITION val, size_t size) {

	if (val == CONDITION::Unknown) {
		this->Set = vector <AtomTrit>(1, AtomTrit(val));
		this->get_set().shrink_to_fit();
	}
	else
		this->Set = vector <AtomTrit>(size, AtomTrit(val));	
};

TritSet::TritSet(const TritSet& TS) {
	for (size_t i = 0; i < TS.Set.size(); i++)
		this->Set.push_back(TS.Set[i]);
};

TritSet TritSet::operator |(TritSet TS) {
	size_t min_len = (this->Set.size() <= TS.Set.size() ? this->Set.size() : TS.Set.size());

	if(min_len == TS.Set.size())
		for (size_t i = 0; i < min_len; i++)
			this->Set[i] = this->Set[i] | TS.Set[i];

	if (min_len == this->Set.size())
		for (size_t i = 0; i < min_len; i++)
			TS.Set[i] = this->Set[i] | TS.Set[i];

	return (this->Set.size() >= TS.Set.size() ? *this : TS);
};

TritSet TritSet::operator &(TritSet TS) {
	size_t min_len = (this->Set.size() <= TS.Set.size() ? this->Set.size() : TS.Set.size());

	if (min_len == TS.Set.size())
		for (size_t i = 0; i < min_len; i++)
			this->Set[i] = this->Set[i] & TS.Set[i];

	if (min_len == this->Set.size())
		for (size_t i = 0; i < min_len; i++)
			TS.Set[i] = this->Set[i] & TS.Set[i];

	return (this->Set.size() >= TS.Set.size() ? *this : TS);
};

TritSet TritSet::operator !(void) {
	for (size_t i = 0; i < this->Set.size(); i++)
		this->Set[i] = !this->Set[i];
	return *this;
};
