#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2 AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 averageVelocity = Vector2::zero();

    if (!neighborhood.empty()) {
        for (const auto& neighbor : neighborhood) {
            if (boid != neighbor) {
                averageVelocity += neighbor->getVelocity();
            }
        }
        averageVelocity /= neighborhood.size();
    }

    return Vector2::normalized(averageVelocity);
}