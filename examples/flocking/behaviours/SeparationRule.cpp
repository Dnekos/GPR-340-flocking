#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include <iostream>

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2 position = boid->transform.position;
        int countCloseFlockmates = 0;

        for (const auto& neighbor : neighborhood) {

            if (boid != neighbor && Vector2::getDistance(boid->getPosition(), neighbor->getPosition()) < desiredDistance) {

                separatingForce += boid->getPosition() - neighbor->getPosition();
            }
        }
        // clamping magnitude
        float magnitude = std::max(std::min(4.0f, 1 / (separatingForce.getMagnitude() / neighborhood.size())), 0.1f);
        separatingForce = Vector2::normalized(separatingForce) * magnitude;
    }
    separatingForce = Vector2::normalized(separatingForce);

    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
