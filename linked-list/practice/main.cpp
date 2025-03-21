#include "LinkedList.hpp"

int main() {
    auto l = LinkedList<int>{};

    l.insert(10);
    l.insertAtStart(5);
    l.insert(24);
    l.insertAtStart(123);
    l.printElements();

    l.remove(123);
    l.printElements();

    l.reverse();
    l.printElements();

    return 0;
}
