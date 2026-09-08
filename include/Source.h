#include <vector>
#include "Vecteur3D.h"
#include "Particule.h"
#include "Aleatoire.h"
#include <memory>
#pragma once

class Source {
private:
    Particule& modele;       // Modèle de particule à copier
    Vecteur3D position;      // Position de la source
    Vecteur3D vitesse_moy;   // Vitesse initiale moyenne
    double et_vitesse;       // Écart-type pour la vitesse
    double et_rayon;         // Écart-type pour le rayon
    unsigned int debit;      // Particules par unité de temps
    bool etat;               // Allumé ou éteint
    Aleatoire& generateur;   // Référence vers le générateur unique

public:
    Source(Particule& modele, Vecteur3D position, Vecteur3D vitesse_moy, 
           double et_v, double et_r, unsigned int debit, 
           Aleatoire& gen, bool etat = true);

    void on();               // Allumer la source
    void off();              // Éteindre la source

    // Méthode de génération des particules
    void creation(std::vector<std::unique_ptr<Particule>>& systeme, double dt);
};