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

void PhysicsManager::collision(ECS& ecs)
{
    // This is doing an O(n^2) comparisons, which isnt' good.
    // But it works for now.
    ecs.ForEach<RigidBody>([&](EntityID e1)
    {
        bool hasCollided = false;

        RigidBody& rb1 = ecs.Get<RigidBody>(e1);
        Position& p1 = ecs.Get<Position>(e1);

        ecs.ForEach<RigidBody>([&](EntityID e2)
        {
            if(e1 != e2)
            {
                RigidBody& rb2 = ecs.Get<RigidBody>(e2);
                Position& p2 = ecs.Get<Position>(e2);

                float d1x = rb2.min.x - rb1.max.x; //b->min.x - a->max.x;
                float d1y = rb2.min.y - rb1.max.y; //b->min.y - a->max.y;
                float d2x = rb1.min.x - rb2.max.x; //a->min.x - b->max.x;
                float d2y = rb1.min.y - rb2.max.y; //a->min.y - b->max.y;

                if (d1x < 0.0f && d1y < 0.0f && d2x < 0.0f && d2y < 0.0f)
                    hasCollided = true;
            }
        });

        if(hasCollided)
        {
            std::cout << "Collision Detected: " << e1 << "\n";
            return;
        }
    });
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