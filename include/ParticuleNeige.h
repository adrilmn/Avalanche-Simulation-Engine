#pragma once

#include "Particule.h"

class ParticuleNeige : public Particule {
public:
    ParticuleNeige(Vecteur3D pos, Vecteur3D vit, double m_vol, double r);
    ParticuleNeige(ParticuleNeige const& autre);

    void ajouteForce(Agent const& autre) override
    {
        autre.opere_sur(*this);
    }

    void opere_sur(ParticuleNeige& particule) const override;
    void opere_sur(ParticuleRoche& particule) const override;
    Particule* copie() const override;
};