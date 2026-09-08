#pragma once

#include <iostream>
#include <cmath>

#include "Vecteur3D.h"
#include "Dessinable.h"
#include "Agent.h"

class SupportADessin;

class Particule : public Dessinable, public Agent {
protected:
    Vecteur3D position;
    Vecteur3D vitesse;
    Vecteur3D force;

    double mvolumique;
    double rayon;

    static double g_val;
    static double eta_air;
    static double rho_air;

    double f(double x) const;

public:
    static constexpr double epsilon = 25.0;
    static constexpr double sigma = 0.885;
    static const double PI;

    Particule(Vecteur3D pos, Vecteur3D vit, double m_vol, double r);
    Particule(Particule const& autre);
    virtual ~Particule() = default;

    double masse() const;
    double get_rayon() const;
    Vecteur3D get_position() const;

    void set_pos(Vecteur3D const& nouvelle_pos);
    void set_vit(Vecteur3D const& nouvelle_vit);
    void set_rayon(double nouveau_r);

    double lambda() const;
    double forceLJ(double distance) const;
    double forceLJ(Particule const& autre) const;

    void ajouteForce(Vecteur3D const& f_ext);
    void ajouteForce();
    void ajouteForceLJDepuis(Particule const& autre, double facteur = 1.0);

    virtual void ajouteForce(Agent const& autre) = 0;
    virtual Particule* copie() const = 0;
    void ajoute_force(Vecteur3D const& f);

    void bouger(double dt);

    static void choisir_milieu(double eta, double rho);

    virtual std::ostream& affiche(std::ostream& sortie) const;
    virtual void dessine_sur(SupportADessin& support) override;
};

std::ostream& operator<<(std::ostream& sortie, Particule const& p);