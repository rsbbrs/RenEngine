#pragma once

#include "PhysicsManager.h"
#include "GraphicsManager.h"
#include "ECS.h"
#include <numbers>

using namespace RenEngine;

bool coll_det(const RigidBody& rb1, const RigidBody& rb2)
{
    float d1x = rb2.min.x - rb1.max.x; //b->min.x - a->max.x;
    float d1y = rb2.min.y - rb1.max.y; //b->min.y - a->max.y;
    float d2x = rb1.min.x - rb2.max.x; //a->min.x - b->max.x;
    float d2y = rb1.min.y - rb2.max.y; //a->min.y - b->max.y;

    if (d1x < 0.0f && d1y < 0.0f && d2x < 0.0f && d2y < 0.0f)
        return true;

    return false;
}

void coll_resolve(RigidBody& rb1, RigidBody& rb2, Position& p1, Position& p2, const float coe, 
                  std::string name, int scale, GraphicsManager* gm)
{
    rb1.force.x *= -1;
    rb2.force.x *= -1;
    rb1.velocity *= -1;
    rb2.velocity *= -1;

    // Steps back the calculation and moves the objects out of one another.
    do
    {
        if(!rb1.static_obj)
        {
            p1.x += rb1.velocity.x;
            p1.y += rb1.velocity.y;
        }
        else
        {
            p2.x += rb2.velocity.x;
            p2.y += rb2.velocity.y;
        }
        
        gm->getBoxCollider(name, p1, scale, rb1.min, rb1.max);
    } 
    while (coll_det(rb1, rb2));
}

void PhysicsManager::startup(ECS* ecs, GraphicsManager* gm)
{
    start = std::chrono::steady_clock::now();
    this->gm = gm;
    this->ecs = ecs;
}

void PhysicsManager::shutdown()
{
    ecs = nullptr;
    gm = nullptr;
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
        std::string name = ecs.Get<Sprite>(e1).name;
        int scale = ecs.Get<Scale>(e1).scale;

        ecs.ForEach<RigidBody>([&](EntityID e2)
        {
            if(e1 != e2)
            {
                RigidBody& rb2 = ecs.Get<RigidBody>(e2);
                Position& p2 = ecs.Get<Position>(e2);

                hasCollided = coll_det(rb1, rb2);

                if(hasCollided)
                {
                    coll_resolve(rb1, rb2, p1, p2, 0.0f, name, scale, gm);
                    return;
                }
            }
        });

        /*
        if(hasCollided)
        {
            std::cout << "Collision Detected: " << e1 << "\n";
            return;
        }*/
    });
}

void PhysicsManager::updatePhysics(std::chrono::time_point<std::chrono::steady_clock> dt)
{
    std::chrono::duration<float> t = dt - start;

    ecs->ForEach<RigidBody>([&](EntityID e)
    {
        std::string name = ecs->Get<Sprite>(e).name;
        RigidBody& rb = ecs->Get<RigidBody>(e);
        Position& p = ecs->Get<Position>(e);
        int scale = ecs->Get<Scale>(e).scale;
        
        // Rigid body kinematic equations.
        rb.acceleration = rb.force * (1.0f / rb.mass + rb.gravity);
        rb.velocity += rb.acceleration * t.count();
        p.x +=  rb.velocity.x * t.count();
        p.y += rb.velocity.y * t.count();

        // Move collider with the object.
        gm->getBoxCollider(name, p, scale, rb.min, rb.max);
    });

    start = dt;
}