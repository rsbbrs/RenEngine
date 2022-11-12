#pragma once

#include "PhysicsManager.h"
#include "ECS.h"
#include <numbers>

using namespace RenEngine;

void PhysicsManager::startup(ECS* manager)
{
    start = std::chrono::steady_clock::now();
    this->manager = manager;
}

void PhysicsManager::shutdown()
{
    manager = nullptr;
}

void PhysicsManager::collisionDetection()
{
    // Nothing right now.
}

void PhysicsManager::collisionResolution()
{
    // Nothing right now.
}

void PhysicsManager::updatePhysics(std::chrono::time_point<std::chrono::steady_clock> dt)
{
    std::chrono::duration<float> t = dt - start;

    manager->ForEach<RigidBody>([&](EntityID e)
    {
        RigidBody& rb = manager->Get<RigidBody>(e);
        Position& p = manager->Get<Position>(e);
        Rotation& r = manager->Get<Rotation>(e);

        auto pi = 3.14159265358979323846;

        // Rigid body kinematic equations.
        rb.acceleration = rb.force * (1.0f/rb.mass + rb.gravity);
        rb.velocity += rb.acceleration * t.count();
        p.x += -std::sin(manager->Get<Rotation>(e).angle *  pi / 180.f) * rb.velocity.x * t.count();
        p.y += std::cos(manager->Get<Rotation>(e).angle * pi / 180.f) * rb.velocity.y * t.count();
    });

    start = dt;
}