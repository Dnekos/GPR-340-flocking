#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce = Vector2::zero();
    float cohesionMagnitude = 5;

    if (neighborhood.size() > 0)
    {
        Vector2 centerOfMass;
        for (const auto& neighbor : neighborhood) {
            if (boid != neighbor) {
                centerOfMass += neighbor->getPosition();
            }
        }

        Vector2 distanceToBoid = (centerOfMass / neighborhood.size()) - boid->getPosition();
        float distance = Vector2::getDistance((centerOfMass / neighborhood.size()), boid->getPosition());
        cohesionForce = distanceToBoid.normalized() * (distance * boid->getDetectionRadius()) * cohesionMagnitude;
    }

    return cohesionForce;
}