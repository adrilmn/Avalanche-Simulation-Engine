#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "Vecteur3D.h"
#include "Particule.h"
#include "Aleatoire.h"
#include "Source.h"

Source::Source(Particule& modele, Vecteur3D position, Vecteur3D vitesse_moy, 
               double et_v, double et_r, unsigned int debit, 
               Aleatoire& gen, bool etat)
    : modele(modele), position(position), vitesse_moy(vitesse_moy), 
      et_vitesse(et_v), et_rayon(et_r), debit(debit), 
      etat(etat), generateur(gen) 
{}

void Source::on() { etat = true; }
void Source::off() { etat = false; }

void Source::creation(std::vector<std::unique_ptr<Particule>>& systeme, double dt) {
    if (!etat) return; // Si la source est éteinte, on ne fait rien

    // 1. Déterminer le nombre de particules à générer, algorithme donné.
    double fraction(debit * dt);
    int nombre(fraction);
    fraction -= nombre;
    if (generateur.uniforme(0.0, 1.0) < fraction) ++nombre;

    // 2. Générer chaque particule
    for (int i(0); i < nombre; ++i) {
        // Copie du modèle
        std::unique_ptr<Particule> nouvelle(modele.copie());

        // On positionne la particule à l'endroit de la source
        nouvelle->set_pos(position);

        // Tirage de la vitesse (Gaussienne sur chaque composante)
        Vecteur3D nouvelle_vit(
            generateur.gaussienne(vitesse_moy.get_x(), et_vitesse),
            generateur.gaussienne(vitesse_moy.get_y(), et_vitesse),
            generateur.gaussienne(vitesse_moy.get_z(), et_vitesse)
        );
        nouvelle->set_vit(nouvelle_vit);

        // Tirage du rayon (Gaussienne centrée sur le rayon du modèle)
        double nouveau_r = generateur.gaussienne(modele.get_rayon(), et_rayon);
        if (nouveau_r < 0.1) nouveau_r = 0.1; // Sécurité pour rayon positif
        nouvelle->set_rayon(nouveau_r);

        //On la decale de dt
        nouvelle->bouger(dt);

        // Ajout au système (tableau de pointeurs), 
        systeme.emplace_back(std::move(nouvelle));   //remplacer push_back par emplace_back car ptr intelligent
    }
}