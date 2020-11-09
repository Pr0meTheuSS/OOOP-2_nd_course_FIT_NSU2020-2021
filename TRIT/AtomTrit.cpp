#include "AtomTrit.h"

AtomTrit::AtomTrit(CONDITION val){
	if (val == CONDITION::False) {
		this->value[0] = 0;
		this->value[1] = 1;// 2(dec) == 10(bin)
	}
	if (val == CONDITION::Unknown) {
		this->value[0] = 0;// 0(dec) == 00(bin)
		this->value[1] = 0;
	}
	if (val == CONDITION::True) {
		this->value[0] = 1;// 1(dec) == 01(bin)
		this->value[1] = 0;
	}
};

bool AtomTrit::operator <(AtomTrit T) {
	return (this->value[1] > T.value[1] || this->value[0] < T.value[0]);
};

AtomTrit AtomTrit::operator |(AtomTrit T) {
	AtomTrit TMP =  (*this < T ? T : *this);
	return TMP;
};

AtomTrit AtomTrit::operator &(AtomTrit T) {
	AtomTrit TMP = (*this< T? *this: T);
	return TMP;
};

AtomTrit AtomTrit::operator !() {
	AtomTrit TMP(*this);
	bool tmp = TMP.value[1];
	TMP.value[1] = TMP.value[0];
	TMP.value[0] = tmp;
	return TMP;
};
