#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce = Vector2::zero();

    if (!neighborhood.empty())
    {
        Vector2 centerOfMass;
        for (const auto& neighbor : neighborhood) {
            if (boid != neighbor) {
                centerOfMass += neighbor->getPosition();
            }
        }

        Vector2 distanceToBoid = (centerOfMass / neighborhood.size()) - boid->getPosition();
        //float distance = Vector2::getDistance((centerOfMass / neighborhood.size()), boid->getPosition());
        cohesionForce = distanceToBoid / neighborhood.size();// *(distance * boid->getDetectionRadius());
    }

    return cohesionForce.normalized();
}