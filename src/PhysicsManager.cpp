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

void PhysicsManager::collision()
{
    
}

void PhysicsManager::updatePhysics(std::chrono::time_point<std::chrono::steady_clock> dt)
{
    std::chrono::duration<float> t = dt - start;

    manager->ForEach<RigidBody>([&](EntityID e)
    {
        RigidBody& rb = manager->Get<RigidBody>(e);
        Position& p = manager->Get<Position>(e);
        
        // Rigid body kinematic equations.
        rb.acceleration = rb.force * (1.0f / rb.mass + rb.gravity);
        rb.velocity += rb.acceleration * t.count();
        p.x +=  rb.velocity.x * t.count();
        p.y += rb.velocity.y * t.count();
    });

    start = dt;
}