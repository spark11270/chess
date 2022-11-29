#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>
#include <memory>
#include "observer.h"

class Observer;

class Subject: public std::enable_shared_from_this<Subject> {
    std::vector<std::shared_ptr<Observer>> observers;
    
public:
    void attach(std::shared_ptr<Observer> o);
    void notifyObservers();

    virtual ~Subject() = 0;
};

#endif
