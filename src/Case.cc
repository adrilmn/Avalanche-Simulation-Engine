#include "Case.h"
#include "Particule.h"

using namespace std;

void Case::ajoute(Particule* p){
    particules.push_back(p);
}

void Case::retire(Particule* p){
    for (auto it = particules.begin(); it != particules.end(); ++it) {

        if (*it == p) {
            particules.erase(it);
            return;
        }
    }
}

vector<Particule*> const& Case::getParticules() const{
    return particules;
}