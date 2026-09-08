#pragma once

#include <vector>

class Particule;

class Case {
private:
    std::vector<Particule*> particules;

public:
    void ajoute(Particule* p);

    void retire(Particule* p);

    std::vector<Particule*> const& getParticules() const;
};