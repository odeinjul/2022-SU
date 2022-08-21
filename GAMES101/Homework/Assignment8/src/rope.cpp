#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        //Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.
        Vector2D step = (start - end) / (num_nodes - 1.f);
        for(int i = 0; i < num_nodes; i++){
            Vector2D p_temp = start + i * step;
            masses.push_back(new Mass(p_temp, node_mass, true));
            if(i)
            {
                springs.push_back(new Spring(masses[i - 1], masses[i], k));
                masses[i]->pinned = false;
            }
        }
        //Comment-in this part when you implement the constructor
        //for (auto &i : pinned_nodes) {
        //    masses[i]->pinned = true;
        //}
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // Use Hooke's law to calculate the force on a node
            Vector2D p1 = s->m1->position;
            Vector2D p2 = s->m2->position;
            float distance = (p2 - p1).norm();
            Vector2D force = s->k * (distance - s->rest_length) * (p2 - p1).unit();
            s->m1->forces += force;
            s->m2->forces -= force;

            //damp
            Vector2D rel_vec = s->m2->velocity - s->m1->velocity;
            Vector2D force_damp = - 0.005 * (dot(rel_vec, (p2 - p1))) * (p2 - p1).unit();

            s->m1->forces -= force_damp;
            s->m2->forces += force_damp;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                // Add the force due to gravity, then compute the new velocity and position
                m->forces += gravity * m->mass;

                // Add global damping
                m->forces += -(0.05 * m->velocity);

                // Updating
                //std::cout << delta_t * m->velocity << std::endl;
                m->velocity += m->forces / m->mass * delta_t;
                m->position += delta_t * m->velocity;
            }

            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // Simulate one timestep of the rope using explicit Verlet （solving constraints)
            Vector2D p1 = s->m1->position;
            Vector2D p2 = s->m2->position;
            float distance = (p2 - p1).norm();
            Vector2D force = s->k * (distance - s->rest_length) * (p2 - p1).unit();
            s->m1->forces += force;
            s->m2->forces -= force;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                Vector2D temp_position = m->position;
                m->forces += gravity * m->mass;
                // Set the new position of the rope mass
                // Add global Verlet damping
                Vector2D temp_acc = m->forces / m->mass;
                float damping_factor = 0.0005;
                m->position = m->position + (1 - damping_factor) * (m->position - m->last_position) + temp_acc * delta_t * delta_t;
                m->last_position = temp_position;
            }
            m->forces =  Vector2D(0,0);
        }
    }
}
