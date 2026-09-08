#include <iostream>
#include <string>
#include <cmath>
#include "Vecteur3D.h"

using namespace std;

// Accesseurs
double Vecteur3D::get_x() const { return x; }
double Vecteur3D::get_y() const { return y; }
double Vecteur3D::get_z() const { return z; }

double Vecteur3D::get_coord(unsigned int i) const {
    if (i == 0) return x;
    else if (i == 1) return y;
    else return z;
}

// Constructeur de copie
// Affichage
void Vecteur3D::affiche(ostream& exit) const {
    exit << x << " " << y << " " << z;
}

// Méthodes de calcul
bool Vecteur3D::compare(Vecteur3D const& vect2, double const erreur) const {
    return (abs(x - vect2.x) <= erreur && abs(y - vect2.y) <= erreur && abs(z - vect2.z) <= erreur);
}

void Vecteur3D::set_coord(int p, double val) {
    if (p == 0) x = val;
    else if (p == 1) y = val;
    else if (p == 2) z = val;
    else cout << "Position invalide" << endl;
}

Vecteur3D Vecteur3D::addition(Vecteur3D const& autre) const {
    return Vecteur3D(x + autre.x, y + autre.y, z + autre.z);
}

Vecteur3D Vecteur3D::soustraction(Vecteur3D const& b) const {
    return Vecteur3D(x - b.x, y - b.y, z - b.z);
}

Vecteur3D Vecteur3D::oppose() const {
    return Vecteur3D(-x, -y, -z);
}

Vecteur3D Vecteur3D::mult(double m) const {
    return Vecteur3D(x * m, y * m, z * m);
}

Vecteur3D Vecteur3D::prod_vect(Vecteur3D autre) const {
    return Vecteur3D(y * autre.z - z * autre.y,
                     z * autre.x - x * autre.z,
                     x * autre.y - y * autre.x);
}

double Vecteur3D::prod_scal(Vecteur3D const& autre) const {
    return x * autre.x + y * autre.y + z * autre.z;
}

double Vecteur3D::norme() const { return sqrt(norme2()); }
double Vecteur3D::norme2() const { return x * x + y * y + z * z; }

Vecteur3D Vecteur3D::unitaire() const {
    Vecteur3D c(*this);
    return c.normalise(); 
}

Vecteur3D& Vecteur3D::normalise() {
    double nor = norme();
    if (nor > 1e-10) {
        x /= nor; y /= nor; z /= nor;
    }
    return *this;
}

// --- Opérateurs Surchargés ---

bool Vecteur3D::operator==(Vecteur3D const& vcomp) const {
    return compare(vcomp);
}

bool Vecteur3D::operator!=(Vecteur3D const& vcomp) const {
    return !compare(vcomp); 
}

Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& v2) {
    x += v2.x; y += v2.y; z += v2.z;
    return *this;
}

Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& b) {
    x -= b.x; y -= b.y; z -= b.z;
    return *this;
}

Vecteur3D Vecteur3D::operator-() const {
    return oppose();
}

Vecteur3D Vecteur3D::operator~() const {
    return unitaire();
}

//operteur externe
Vecteur3D operator+(Vecteur3D a, Vecteur3D const& b) {
    return a += b;
}

Vecteur3D operator-(Vecteur3D a, Vecteur3D const& b) {
    return a -= b;
}

Vecteur3D operator*(Vecteur3D v, double k) {
    return v.mult(k);
}

Vecteur3D operator*(double k, Vecteur3D const& v) {
    return v * k;
}

double operator*(Vecteur3D const& v1, Vecteur3D const& v2) {
    return v1.prod_scal(v2);
}

Vecteur3D operator^(Vecteur3D const& v1, Vecteur3D const& v2) {
    return v1.prod_vect(v2);
}

ostream& operator<<(ostream& exit, Vecteur3D const& v) {
    v.affiche(exit);
    return exit;
}