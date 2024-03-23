#include <random>

using namespace std;

int rand(int x, int y) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(x, y)(rng);
}