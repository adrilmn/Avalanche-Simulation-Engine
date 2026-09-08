#pragma once

#include <iostream>

#include "Vecteur3D.h"
#include "Dessinable.h"
#include "Agent.h"

class SupportADessin;
class ParticuleNeige;
class ParticuleRoche;

class Obstacle : public Dessinable, public Agent {
protected:
    Vecteur3D position;

public:
    Obstacle(Vecteur3D p);
    virtual ~Obstacle() = default;

    Vecteur3D get_position() const;

    virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const = 0;
    virtual void affiche(std::ostream& sortie) const = 0;

    void opere_sur(ParticuleNeige& particule) const override;
    void opere_sur(ParticuleRoche& particule) const override;
};


class Plan : public Obstacle {
protected:
    Vecteur3D Vecteur_unitaire;

public:
    Plan(Vecteur3D p, Vecteur3D n);

    Vecteur3D get_Vecteur_unitaire() const;
    Vecteur3D PointPlusProche(Vecteur3D const& x_i) const override;

    void affiche(std::ostream& sortie) const override;
    void dessine_sur(SupportADessin& support) override;
};

class Dalle : public Plan {
private:
    double largeur;
    double longeur;
    Vecteur3D VecteurL;

public:
    Dalle(Vecteur3D p, Vecteur3D n, double larg, double lon, Vecteur3D v_d);

    Vecteur3D PointPlusProche(Vecteur3D const& x_i) const override;
    void affiche(std::ostream& sortie) const override;

    double get_largeur() const;
    double get_longuer() const;

    void dessine_sur(SupportADessin& support) override;
};

std::ostream& operator<<(std::ostream& sortie, Obstacle const& obs);