#include "Systeme.h"

// The system owns its simulation objects through smart pointers.
Systeme::~Systeme() {}

Systeme::Systeme(double t)
    : temps(t),
      grille(20,
             std::vector<std::vector<Case>>(20,
                 std::vector<Case>(20))){
    choisir_air(); 
}

void Systeme::ajouteParticule(Particule* p) { // Add the particle to the spatial grid.
    if (p != nullptr) {
        particules.emplace_back(p);
        ajouteDansCase(p);
    }
}

void Systeme::ajouteObstacle(Obstacle* o) {
    if (o != nullptr) {
        obstacles.emplace_back(o);
    }
}

void Systeme::ajouteSource(Source* s) {
    if (s != nullptr) {
        sources.emplace_back(s);
    }
}

void Systeme::evolue(double dt)
{
    // Les sources creent eventuellement de nouvelles particules
    for (auto& source : sources) {
        source->creation(particules, dt);
    }

    // Calcul des forces
    for (auto& p : particules) {

        // 1. Force propre : poids + frottements
        p->ajouteForce();

        // 2. Forces dues aux obstacles
        for (auto const& obstacle : obstacles) {
            p->ajouteForce(*obstacle);
        }

        // 3. Forces dues aux particules proches uniquement
        Vecteur3D pos(p->get_position());

        int i(pos.get_x() / taille_case);
        int j(pos.get_y() / taille_case);
        int k(pos.get_z() / taille_case);

        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                for (int dk = -1; dk <= 1; ++dk) {

                    int ni(i + di);
                    int nj(j + dj);
                    int nk(k + dk);

                    if (ni >= 0 and ni < 20
                     and nj >= 0 and nj < 20
                     and nk >= 0 and nk < 20) {

                        for (auto autre : grille[ni][nj][nk].getParticules()) {
                            if (p.get() != autre) {
                                p->ajouteForce(*autre);
                            }
                        }
                    }
                }
            }
        }
    }

    // Deplacement des particules
    for (auto& p : particules) {
        p->bouger(dt);
    }

    // Mise a jour du temps
    temps += dt;

    // Remise a zero de la grille
    for (auto& plan2D : grille) {
        for (auto& ligne : plan2D) {
            for (auto& c : ligne) {
                c = Case();
            }
        }
    }

    // On replace chaque particule dans sa nouvelle case
    for (auto& p : particules) {
        ajouteDansCase(p.get());
    }
}

// Render a textual representation of the current simulation state.
void Systeme::affiche(std::ostream& sortie) const {
    // Affichage des particules
    sortie << "Simulation contains " << particules.size() << " particles:" << std::endl;
    for (auto const& p : particules) {
        // On utilise l'opérateur << de Particule (qui appelle p->affiche)
        sortie << *p << std::endl;
    }

    //Affichage des obstacles
    if (!obstacles.empty()) {
        sortie << "and " << obstacles.size() << " obstacles:" << std::endl;
        for (auto const& o : obstacles) {
            o->affiche(sortie);
            sortie << std::endl;
        }
    }
}

void Systeme::choisir_air(){
    Particule::choisir_milieu(1.8e-2, 1.3e-3);
}

void Systeme::choisir_eau(){
    Particule::choisir_milieu(1.0, 1.0);
}

void Systeme::ajouteDansCase(Particule* p)
{
    Vecteur3D pos(p->get_position());

    int i(pos.get_x() / taille_case);
    int j(pos.get_y() / taille_case);
    int k(pos.get_z() / taille_case);

    if (i >= 0 and i < 20
     and j >= 0 and j < 20
     and k >= 0 and k < 20) {

        grille[i][j][k].ajoute(p);
    }
}

// Stream operator.
std::ostream& operator<<(std::ostream& sortie, Systeme const& sys) {
    sys.affiche(sortie);
    return sortie;
}