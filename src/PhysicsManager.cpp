#pragma once

#include "PhysicsManager.h"
#include "GraphicsManager.h"
#include "ECS.h"
#include <numbers>

using namespace RenEngine;

bool PhysicsManager::coll_det(const EntityID e1, const EntityID e2)
{
    RigidBody& rb1 = ecs->Get<RigidBody>(e1);
    RigidBody& rb2 = ecs->Get<RigidBody>(e2);
    float d1x = rb2.min.x - rb1.max.x; //b->min.x - a->max.x;
    float d1y = rb2.min.y - rb1.max.y; //b->min.y - a->max.y;
    float d2x = rb1.min.x - rb2.max.x; //a->min.x - b->max.x;
    float d2y = rb1.min.y - rb2.max.y; //a->min.y - b->max.y;

    if (d1x < 0.0f && d1y < 0.0f && d2x < 0.0f && d2y < 0.0f)
        return true;

    return false;
}

void PhysicsManager::coll_resolve(EntityID e1, EntityID e2, Position& p1, Position& p2, 
                  std::string name1, std::string name2, int scale1, int scale2, const float coe, GraphicsManager* gm)
{

    RigidBody& rb1 = ecs->Get<RigidBody>(e1);
    RigidBody& rb2 = ecs->Get<RigidBody>(e2);

    // Simple rebounding calculation.
    // Will need to be more detailed in order to really
    // mimic a real physics body.
    vec2 tempVel1 = vec2(-1 * rb1.velocity.x, -1 * rb1.velocity.y);
    vec2 tempVel2 = vec2(-1 * rb2.velocity.x, -1 * rb2.velocity.y);

    Position current = p1;

    // Steps back the calculation and moves the objects out of one another.
    // Currently, it's just attempting to move the objects away from one
    // another by 1% of the inverted velocity. This way, the objects don't
    // travel too far out.
    do
    {
        if(!rb1.static_obj)
        {
            p1.x += tempVel1.x * 0.01f;
            // p1.y += tempVel1.y * 0.01f;
            gm->getBoxCollider(name1, p1, scale1, rb1.min, rb1.max);
        }

        if(!rb2.static_obj)
        {
            p2.x += tempVel2.x * 0.01f;
            // p2.y += tempVel2.y * 0.01f;
            gm->getBoxCollider(name2, p2, scale2, rb2.min, rb2.max);
        }
        
    } 
    while (coll_det(e1, e2));

    vec2 j1 = (-(1 + coe) * (rb1.velocity - rb2.velocity)) / ((1.0f / rb1.mass) + (1.0f / rb2.mass));
    vec2 j2 = (-(1 + coe) * (rb2.velocity - rb1.velocity)) / ((1.0f / rb2.mass) + (1.0f / rb1.mass));

    // A static object should not move after a collision
    if (!rb1.static_obj)
    {
        rb1.velocity += (1.0f / rb1.mass) * (j1 * 1.25f);
        rb1.force.x *= -1;
    }
    
    if (!rb2.static_obj)
    {
        rb2.velocity += (1.0f / rb2.mass) * (j2 * 1.25f);
        rb2.force.x *= -1;
    }
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

void PhysicsManager::collision()
{
    // This is doing an O(n^2) comparisons, which isnt' good.
    // But it works for now.
    ecs->ForEach<RigidBody>([&](EntityID e1)
    {
        bool hasCollided = false;

        RigidBody& rb1 = ecs->Get<RigidBody>(e1);
        Position& p1 = ecs->Get<Position>(e1);
        std::string name1 = ecs->Get<Sprite>(e1).name;
        int scale1 = ecs->Get<Scale>(e1).scale;

        ecs->ForEach<RigidBody>([&](EntityID e2)
        {
            if(e1 != e2)
            {
                RigidBody& rb2 = ecs->Get<RigidBody>(e2);
                Position& p2 = ecs->Get<Position>(e2);
                std::string name2 = ecs->Get<Sprite>(e1).name;
                int scale2 = ecs->Get<Scale>(e1).scale;

                hasCollided = coll_det(e1, e2);

                if(hasCollided)
                {
                    printf("Potatoooo");
                    coll_resolve(e1, e2, p1, p2, name1, name2, scale1, scale2, 1.0f, gm);
                    return;
                }
            }
        });

        
/*         if(hasCollided)
        {
            std::cout << "Collision Detected: " << e1 << "\n";
            return;
        } */
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