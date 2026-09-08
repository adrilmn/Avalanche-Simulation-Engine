#include <iostream>
#include <cmath>

#include "Particule.h"
#include "SupportADessin.h"

using namespace std;

const double Particule::PI = std::acos(-1.0);

double Particule::g_val = -9.81e3;
double Particule::eta_air = 1.8e-2;
double Particule::rho_air = 1.3e-3;

Particule::Particule(Vecteur3D pos, Vecteur3D vit, double m_vol, double r)
    : position(pos), vitesse(vit), force(0, 0, 0),
      mvolumique(m_vol), rayon(r){}

Particule::Particule(Particule const& autre)
    : position(autre.position), vitesse(autre.vitesse), force(0, 0, 0),
      mvolumique(autre.mvolumique), rayon(autre.rayon){}

double Particule::masse() const{
    return (4.0 / 3.0) * PI * pow(rayon, 3) * mvolumique;
}

double Particule::lambda() const{
    double v(vitesse.norme());
    double limite((80.0 * eta_air) / (3.0 * rho_air * rayon));

    if (v <= limite) {
        return 6.0 * PI * rayon * eta_air;
    } else {
        return (9.0 * PI / 40.0) * pow(rayon, 2) * rho_air * v;
    }
}

double Particule::f(double x) const{
    if (x <= 1.0) {
        return -1.0;
    } else if (x < 2.0) {
        return (pow(x, 6) - 2.0) / pow(x, 13);
    } else {
        return 0.0;
    }
}

void Particule::choisir_milieu(double eta, double rho){
    eta_air = eta;
    rho_air = rho;
}

double Particule::forceLJ(double distance) const{
    double x(distance / sigma);
    return (24.0 * epsilon / (sigma * sigma)) * f(x);
}

double Particule::forceLJ(Particule const& autre) const{
    double distance((autre.position - position).norme());
    return forceLJ(distance);
}

void Particule::ajouteForce(Vecteur3D const& f_ext){
    force += f_ext;
}

void Particule::ajouteForce(){
    Vecteur3D pesanteur(0, 0, g_val);
    force += (pesanteur * masse()) - (vitesse * lambda());
}

void Particule::ajouteForceLJDepuis(Particule const& autre, double facteur){
    Vecteur3D e(autre.position - position);
    double distance(e.norme());

    if (distance > 1e-10) {
        Vecteur3D direction(~e);
        force += direction * (facteur * forceLJ(distance));
    }
}

void Particule::bouger(double dt){
    vitesse += force * (dt / masse());
    position += vitesse * dt;
    force = Vecteur3D(0, 0, 0);
}

void Particule::set_pos(Vecteur3D const& nouvelle_pos){
    position = nouvelle_pos;
}

void Particule::set_vit(Vecteur3D const& nouvelle_vit){
    vitesse = nouvelle_vit;
}

void Particule::set_rayon(double nouveau_r){
    if (nouveau_r > 0) {
        rayon = nouveau_r;
    }
}

double Particule::get_rayon() const{
    return rayon;
}

Vecteur3D Particule::get_position() const{
    return position;
}

ostream& Particule::affiche(ostream& sortie) const{
    sortie << "[ pos = " << position
           << ", v = " << vitesse
           << ", m = " << masse()
           << ", r = " << rayon << " ]";
    return sortie;
}

void Particule::dessine_sur(SupportADessin& support){
    support.dessine(*this);
}

void Particule::ajoute_force(Vecteur3D const& f){
    force += f;
}

ostream& operator<<(ostream& sortie, Particule const& p){
    return p.affiche(sortie);
}