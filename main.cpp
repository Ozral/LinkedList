#include "LinkedList.hpp"

using namespace std;

int main() {
    LinkedList<int> list;
    list << 1 << 2 << 3;
    list.forEach([](int item) { cout << item << endl; });
    return 0;
}
