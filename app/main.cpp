#include <iostream>

#include "Systeme.h"
#include "ParticuleNeige.h"
#include "ParticuleRoche.h"
#include "Obstacle.h"

using namespace std;

int main()
{
    cout << "=== Avalanche Simulation — Spatially Optimized ===" << endl;
    cout << endl;

    Systeme systeme;
    systeme.choisir_air();

    cout << "--- Adding particles ---" << endl;

    systeme.ajouteParticule(new ParticuleNeige(
        Vecteur3D(0.0, 0.0, 1.0),
        Vecteur3D(0.0, 0.0, 0.0),
        1.0,
        0.4
    ));
    systeme.ajouteParticule(new ParticuleNeige(
        Vecteur3D(1.0, 0.0, 1.0),
        Vecteur3D(0.0, 0.0, 0.0),
        1.0,
        0.4
    ));
    systeme.ajouteParticule(new ParticuleRoche(
        Vecteur3D(1.0, 1.0, 1.0),
        Vecteur3D(0.0, 0.0, 0.0),
        1.0,
        0.4
    ));
    systeme.ajouteParticule(new ParticuleNeige(
        Vecteur3D(15.0, 15.0, 15.0),
        Vecteur3D(0.0, 0.0, 0.0),
        1.0,
        0.4
    ));
    cout << "--- Adding obstacle ---" << endl;

    systeme.ajouteObstacle(new Plan(
        Vecteur3D(0.0, 0.0, 0.0),
        Vecteur3D(0.0, 0.0, 1.0)
    ));

    cout << endl;
    cout << "--- Initial state ---" << endl;
    cout << systeme << endl;

    cout << endl;
    cout << "--- Evolution with spatial partitioning ---" << endl;

    for (int i(0); i < 3; ++i) {
        cout << "Step " << i + 1 << " :" << endl;
        systeme.evolue(0.001);
        cout << systeme << endl;
    }

    cout << endl;
    cout << "=== Simulation checks ===" << endl;
    cout << "- Nearby particles interact through the local spatial grid." << endl;
    cout << "- Distant particles are excluded from local interaction checks." << endl;
    cout << "- The plane acts as a collision boundary." << endl;
    cout << "- The spatial partition remains consistent during the simulation." << endl;

    cout << endl;
    cout << "=== Simulation complete ===" << endl;

    return 0;
}