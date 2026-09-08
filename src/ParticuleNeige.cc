#include "ParticuleNeige.h"
#include "ParticuleRoche.h"

ParticuleNeige::ParticuleNeige(Vecteur3D pos, Vecteur3D vit,
                               double m_vol, double r)
    : Particule(pos, vit, m_vol, r)
{}

ParticuleNeige::ParticuleNeige(ParticuleNeige const& autre)
    : Particule(autre)
{}

void ParticuleNeige::opere_sur(ParticuleNeige& particule) const
{
    particule.ajouteForceLJDepuis(*this);
}

void ParticuleNeige::opere_sur(ParticuleRoche& particule) const
{
    // Interaction neige -> roche : même modèle, mais un peu moins fort.
    particule.ajouteForceLJDepuis(*this, 0.5);
}

Particule* ParticuleNeige::copie() const
{
    return new ParticuleNeige(*this);
}