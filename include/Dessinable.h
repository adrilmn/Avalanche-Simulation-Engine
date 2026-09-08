#pragma once

class SupportADessin;

class Dessinable {
    public:
        virtual ~Dessinable() = default;//ici comme on utilise le déstructeur par défaut des pointeur pour le pointeur des chose désinables
        // remise par défaut des constructeurs de copie et de déplacement
        Dessinable(Dessinable const&)            = default;
        Dessinable& operator=(Dessinable const&) = default;
        Dessinable(Dessinable&&)                 = default;
        Dessinable& operator=(Dessinable&&)      = default;

        // et remise aussi par défaut du constructeur par défaut
        Dessinable() = default;

        virtual void dessine_sur(SupportADessin&)=0;//ici la méthode est virtuel pure et est la méthode qui nous intéresse
    
};