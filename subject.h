#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>
#include <memory>
#include "observer.h"

class Observer;

class Subject {
    std::vector<Observer*> observers;
    
public:
    void attach(Observer *o);
    void detach(Observer *o);    
    void notifyObservers();

    virtual ~Subject() = default;
};

#endif
