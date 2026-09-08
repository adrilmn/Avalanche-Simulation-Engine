#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Dessinable.h"
#include "SupportADessin.h"
#include "Particule.h"
#include "Obstacle.h"
#include "Source.h"
#include "Case.h"

class Systeme : public Dessinable {
private://Pointeurs pour polymorphisme, car on aura des sous classes de particules, obstacles etc.
    std::vector<std::unique_ptr<Particule>> particules;
    std::vector<std::unique_ptr<Obstacle>>  obstacles;
    std::vector<std::unique_ptr<Source>>    sources;
    double temps;
    static constexpr double taille_case = 2.0;
    std::vector<std::vector<std::vector<Case>>> grille;
    void ajouteDansCase(Particule* p);

public:
    // Constructor.
    Systeme(double t = 0.0);

    // Virtual destructor.
    virtual ~Systeme();

    // Copying a simulation would duplicate ownership; keep the system non-copyable.
    Systeme(Systeme const&) = delete;  //erreur si j essaye de copier un systeme
    Systeme& operator=(Systeme const&) = delete; //surcharge d operateur = 

    // Ownership is transferred to the system.
    void ajouteParticule(Particule* p);
    void ajouteObstacle(Obstacle* o);
    void ajouteSource(Source* s);

    // Text output.
    void affiche(std::ostream& sortie) const;

    // Drawing interface.
    
    virtual void dessine_sur(SupportADessin& support) override
    { support.dessine(*this); }

    void evolue(double dt);

    void choisir_air();
    void choisir_eau();

};

// Stream operator for the simulation.
std::ostream& operator<<(std::ostream& sortie, Systeme const& sys);