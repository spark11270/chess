#include "subject.h"

void Subject:: attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers() {
    for (auto &o : observers) {
        o->notify(shared_from_this());
    }
}

Subject::~Subject() {}
