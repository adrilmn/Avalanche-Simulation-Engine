#include "ParticuleRoche.h"
#include "ParticuleNeige.h"

ParticuleRoche::ParticuleRoche(Vecteur3D pos, Vecteur3D vit,
                               double m_vol, double r)
    : Particule(pos, vit, m_vol, r){}

ParticuleRoche::ParticuleRoche(ParticuleRoche const& autre)
    : Particule(autre){}

void ParticuleRoche::opere_sur(ParticuleNeige& particule) const{
    // Interaction roche -> neige : plus forte qu'une interaction neige-neige.
    particule.ajouteForceLJDepuis(*this, 2.0);
}

void ParticuleRoche::opere_sur(ParticuleRoche& particule) const{
    // Interaction roche-roche : très faible.
    particule.ajouteForceLJDepuis(*this, 0.2);
}

Particule* ParticuleRoche::copie() const{
    return new ParticuleRoche(*this);
}