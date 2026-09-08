#include "Obstacle.h"
#include "SupportADessin.h"
#include "ParticuleNeige.h"
#include "ParticuleRoche.h"

Obstacle::Obstacle(Vecteur3D p)
    : position(p){}

Vecteur3D Obstacle::get_position() const{
    return position;
}

void Obstacle::opere_sur(ParticuleNeige& particule) const{
    Vecteur3D point_proche(PointPlusProche(particule.get_position()));
    Vecteur3D e(point_proche - particule.get_position());

    double distance(e.norme());

    if (distance > 1e-10) {
        Vecteur3D direction(~e);
        particule.ajoute_force(direction * (2.0 * particule.forceLJ(distance)));
    }
}

void Obstacle::opere_sur(ParticuleRoche& particule) const{
    // Même interaction obstacle-roche que obstacle-neige pour l'instant.
    Vecteur3D point_proche(PointPlusProche(particule.get_position()));
    Vecteur3D e(point_proche - particule.get_position());

    double distance(e.norme());

    if (distance > 1e-10) {
        Vecteur3D direction(~e);
        particule.ajoute_force(direction * (2.0 * particule.forceLJ(distance)));
    }
}

Plan::Plan(Vecteur3D p, Vecteur3D n)
    : Obstacle(p), Vecteur_unitaire(n.unitaire()){}

Vecteur3D Plan::get_Vecteur_unitaire() const{
    return Vecteur_unitaire;
}

Vecteur3D Plan::PointPlusProche(Vecteur3D const& x_i) const{
    return x_i + ((position - x_i) * Vecteur_unitaire) * Vecteur_unitaire;
}

void Plan::affiche(std::ostream& sortie) const{
    sortie << "Plan d'origine " << position
           << " et de normale " << Vecteur_unitaire;
}

void Plan::dessine_sur(SupportADessin& support){
    support.dessine(*this);
}

Dalle::Dalle(Vecteur3D p, Vecteur3D n, double larg, double lon, Vecteur3D v_d)
    : Plan(p, n), largeur(larg), longeur(lon), VecteurL(v_d.unitaire()){}

Vecteur3D Dalle::PointPlusProche(Vecteur3D const& x_i) const{
    Vecteur3D x2(Plan::PointPlusProche(x_i));
    Vecteur3D xl(Vecteur_unitaire ^ VecteurL);

    double xkL((x2 - position) * VecteurL);
    double xkl((x2 - position) * xl);

    if (xkL > largeur) {
        x2 -= (xkL - largeur) * VecteurL;
    } else if (xkL < 0) {
        x2 -= xkL * VecteurL;
    }

    if (xkl > longeur) {
        x2 -= (xkl - longeur) * xl;
    } else if (xkl < 0) {
        x2 -= xkl * xl;
    }

    return x2;
}

void Dalle::affiche(std::ostream& sortie) const{
    sortie << "Dalle d'origine " << position
           << ", de normale " << Vecteur_unitaire
           << ", de largeur " << largeur
           << " et longueur " << longeur;
}

double Dalle::get_largeur() const{
    return largeur;
}

double Dalle::get_longuer() const{
    return longeur;
}

void Dalle::dessine_sur(SupportADessin& support){
    support.dessine(*this);
}

std::ostream& operator<<(std::ostream& sortie, Obstacle const& obs){
    obs.affiche(sortie);
    return sortie;
}