#include "subject.h"
#include "observer.h"

using namespace std;

void Subject::attach(shared_ptr<Observer> o) {

    observers.push_back(o);
}

void Subject::notifyObservers(bool clear) {

    for (auto it = observers.begin(); it != observers.end(); ++it) {

            (*it)->notify(*this);
    }
}

