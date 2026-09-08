#pragma once

class ParticuleNeige;
class ParticuleRoche;

class Agent {
public:
    virtual ~Agent() = default;

    virtual void opere_sur(ParticuleNeige& particule) const = 0;
    virtual void opere_sur(ParticuleRoche& particule) const = 0;
};