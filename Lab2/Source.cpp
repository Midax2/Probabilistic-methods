#include <cmath>
#include <iostream>
#include <bitset>
using namespace std;
class GeneratorRandom {
	unsigned long long a;
	unsigned long long c;
	unsigned long long M;
	unsigned long long value;
public:
	GeneratorRandom(unsigned long long value) {
		M = pow(2, 31);
		a = 69069;
		c = 1;
		this->value = value;
	}
	float rand() {
		value = (value * a + c) % M;
		return (float)value / M;
	}
};

class RandomBit {
	unsigned long long p;
	unsigned long long q;
	unsigned long long M;
	bitset<32> value;

public:
	RandomBit() {
		p = 7;
		q = 3;
		M = pow(2, 31);
		value.set(30);
		value.set(29);
		value.set(27);
		value.set(24);
	}
	float rand() {
		//cout << value << endl;
		for (int i = 23; i >= 0; i--) {
			bool newBit = value.test(i + p) ^ value.test(i + q);
			if (newBit) value.set(i);
			else value.reset(i);
		}
		
		for (int i = 30; i >= 24; i--) {
			bool newBit = value.test(i - 24);
			if (newBit) value.set(i);
			else value.reset(i);
		}
		return static_cast<float>(value.to_ulong()) / M;
	}
};
int main() {
	GeneratorRandom gen(15);
	int count1[10] = { 0 };
	for (int i = 0; i < 100000; i++) {
		float newRandomNum = gen.rand();
		count1[(int)(newRandomNum * 10)]++;
	}
	for (int i = 0; i < 10; i++) {
		cout << count1[i] << " ";
	}
	cout << endl << endl;
	RandomBit bitGen;
	int count2[10] = {0};
	for (int i = 0; i < 100000; i++) {
		float newRandomNum = bitGen.rand();
		count2[(int)(newRandomNum * 10)]++;
	}
	for (int i = 0; i < 10; i++) {
		cout << count2[i] << " ";
	}
	return 0;
}