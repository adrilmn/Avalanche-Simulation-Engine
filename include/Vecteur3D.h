#pragma once

#include <iostream>

class Vecteur3D {
private:
    double x, y, z;

public:
    // Constructeurs
    Vecteur3D(double valx = 0, double valy = 0, double valz = 0) : x(valx), y(valy), z(valz) {}
    Vecteur3D(const Vecteur3D& vc) = default;
    Vecteur3D& operator=(const Vecteur3D& other) = default;

    // Getters
    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_coord(unsigned int i) const;

    // Setters
    void set_coord(int p, double val);

    // Affichage
    void affiche(std::ostream& exit) const;

    // Méthodes de calcul
    bool compare(Vecteur3D const& vect2, double const erreur = 1e-10) const;
    Vecteur3D addition(Vecteur3D const& autre) const;
    Vecteur3D soustraction(Vecteur3D const& b) const;
    Vecteur3D oppose() const;
    Vecteur3D mult(double m) const;
    Vecteur3D prod_vect(Vecteur3D autre) const;
    double prod_scal(Vecteur3D const& autre) const;
    double norme() const;
    double norme2() const;
    Vecteur3D unitaire() const;
    Vecteur3D& normalise();

    // Opérateurs membres
    bool operator==(Vecteur3D const& vcomp) const;
    bool operator!=(Vecteur3D const& vcomp) const;
    Vecteur3D& operator+=(Vecteur3D const& v2);
    Vecteur3D& operator-=(Vecteur3D const& b);
    Vecteur3D operator-() const;
    Vecteur3D operator~() const;
};

// Opérateurs externes
Vecteur3D operator+(Vecteur3D a, Vecteur3D const& b);
Vecteur3D operator-(Vecteur3D a, Vecteur3D const& b);
Vecteur3D operator*(Vecteur3D v, double k);
Vecteur3D operator*(double k, Vecteur3D const& v);
double operator*(Vecteur3D const& v1, Vecteur3D const& v2); // Produit scalaire
Vecteur3D operator^(Vecteur3D const& v1, Vecteur3D const& v2);
std::ostream& operator<<(std::ostream& exit, Vecteur3D const& v);

