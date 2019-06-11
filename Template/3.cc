#include <iostream>
#include <map>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

template <typename T>
class BarGraph {
  public:
    void operator+=(const T &datum) {
        data[datum]++;
    }
    void dump() const {
	for (const auto &val : data)
	    cout << right << setw(10) << val.first << ' '
		 << string(val.second, '*') << '\n';
        cout << '\n';
    }
  private:
    map<T, unsigned> data;
};

template <>
class BarGraph<bool> {
    unsigned false_count = 0, true_count = 0;
  public:
    void operator+=(bool datum) {
	datum ? true_count++ : false_count++;
    }
    void dump() const {
        cout << "     false " << string(false_count, '*') << "\n"
                "      true " << string(true_count,  '*') << "\n\n";
    }
};
template<>
class BarGraph<char> {
    public:
    void operator+=(char &datum) {
        data[datum]++;
    }
    void operator+=(string &datum) {
        for (int i = 0, i < datum.size(); i++) {
            data[datum[i]]++;
        }
    }
    void dump() const {
	for (const auto &val : data)
	    cout << right << setw(10) << val << ' '
		 << string(val, '*') << '\n';
        cout << '\n';
    }
    private:
    char data[num_limits<int>::max()];
};

int main() {
    BarGraph<int> alpha;
    alpha += 12;
    alpha += 6;
    alpha += 4;
    alpha += 6;
    alpha.dump();

    BarGraph<double> beta;
    beta += 3.14;
    beta += 2.71828;
    beta += 6.023e23;
    beta += 2.71828;
    beta.dump();

    BarGraph<bool> gamma;
    gamma += false;
    gamma += true;
    gamma += false;
    gamma += true;
    gamma += true;
    gamma.dump();

    BarGraph<char> delta;
    delta += 'G';
    delta += 'e';
    delta += 'o';
    delta += 'f';
    delta += 'f';
    delta.dump();

    return 0;
}
