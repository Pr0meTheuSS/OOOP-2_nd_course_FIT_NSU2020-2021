#ifndef ATOMTRIT_HPP
#define ATOMTRIT_HPP

#include <vector>
#include <bitset>

enum class CONDITION { False = -1, Unknown = 0, True = 1 };

using namespace std;

class AtomTrit {
private:
	bitset <2> value;
public:
	AtomTrit(CONDITION val) = default;
	~AtomTrit() = default;

	bool operator <(AtomTrit T) {};
	AtomTrit operator |(AtomTrit T) {};
	AtomTrit operator &(AtomTrit T) {};
	AtomTrit operator !() {};
};
#endif
