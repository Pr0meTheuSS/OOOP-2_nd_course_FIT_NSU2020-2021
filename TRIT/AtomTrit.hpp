#ifndef VECTOR
#define VECTOR
#include <vector>
#include <bitset>
#endif

#ifndef BITSET
#define BITSET
#include <bitset>
#endif

enum class CONDITION { False = -1, Unknown = 0, True = 1 };

using namespace std;

class AtomTrit {
private:
	bitset <2> value;
public:
	AtomTrit(CONDITION val) {};
	bool operator <(AtomTrit T) {};
	AtomTrit operator |(AtomTrit T) {};
	AtomTrit operator &(AtomTrit T) {};
	AtomTrit operator !() {};

	~AtomTrit() {};
};

