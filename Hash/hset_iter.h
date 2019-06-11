#include <list>
#include <vector>

// Each hset_iter contains a reference to its associated hash,
// and an int indicating progress within the hash.

template <typename T>
class hset_iter {
  private:
    typedef typename std::vector< std::list<T> > table_t;
    const table_t &parent;
    int num;

  public:
    hset_iter(table_t &table, int n) : parent(table), num(n) { }

    bool operator==(const hset_iter &rhs) const {
	return num == rhs.num;
    }

    bool operator!=(const hset_iter &rhs) const {
	return !(*this == rhs);
    }

    // Return a pointer to the num'th element,
    // where num==0 is the first element.

    T operator*() const {
	unsigned int remaining = num;
	int i;
	// First, find the right list:
	for (i=0; parent[i].size() <= remaining; i++)
	    remaining -= parent[i].size();

	// Second, find the right slot within that list:
	auto it = parent[i].begin();
	for ( ; remaining >0; --remaining)
	    ++it;

	return *it;
    }

    // Pre-increment
    void operator++() {
	++num;
    }
};
