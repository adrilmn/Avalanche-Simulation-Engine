#include <iostream>
#pragma once

class Particule;
class Systeme;
class Obstacle;


class SupportADessin{
public:
virtual ~SupportADessin() = default;

// on suppose ici que les supports ne seront ni copiés ni déplacés
SupportADessin(SupportADessin const&)            = delete;
SupportADessin& operator=(SupportADessin const&) = delete;
SupportADessin(SupportADessin&&)            = delete;
SupportADessin& operator=(SupportADessin&&) = delete;

virtual void dessine(Particule const&) = 0;
virtual void dessine(Systeme const&) = 0;
virtual void dessine(Obstacle const&) = 0 ;

// on remet aussi la version par défaut du constructeur par défaut
SupportADessin() = default;

};
