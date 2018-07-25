//
// Created by Dasha Burmistrova on 2018-07-24.
//

#ifndef QUADRISGAME_SUBJECT_H
#define QUADRISGAME_SUBJECT_H

#include <vector>
#include <memory>

class Observer;

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void attach(std::shared_ptr<Observer>);
    void notifyObservers();
};

#endif //QUADRISGAME_SUBJECT_H
