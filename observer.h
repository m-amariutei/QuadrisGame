//
// Created by Dasha Burmistrova on 2018-07-24.
//

#ifndef QUADRISGAME_OBSERVER_H
#define QUADRISGAME_OBSERVER_H

class Observer {
public:
    virtual void notify() = 0;
    virtual ~Observer() = default;
};

#endif //QUADRISGAME_OBSERVER_H
