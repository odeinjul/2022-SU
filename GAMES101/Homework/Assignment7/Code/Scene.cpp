//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // Implement Path Tracing Algorithm here
    float epsilon = 0.0001;
    Vector3f L_indir, L_dir;

    Intersection p_in = intersect(ray);
    if(!p_in.happened) //No intersection
        return Vector3f();
    if(p_in.m->hasEmission()) //Intersect with light
        return p_in.m->getEmission();

    Intersection p_out_light;
    float pdf_light = 0.0f;
    sampleLight(p_out_light, pdf_light);
    Vector3f p = p_in.coords;
    Vector3f x = p_out_light.coords;
    Vector3f p_out_dir = (x - p).normalized();
    float p_out_dis = (x - p).norm();
    Vector3f p_norm = p_in.normal.normalized();
    Vector3f x_norm = p_out_light.normal.normalized();
    Vector3f x_emit = p_out_light.emit;

    Ray ws_ray(p, p_out_dir);
    Intersection ws_ray_inter = intersect(ws_ray);
    if(std::abs(ws_ray_inter.distance - p_out_dis) <= epsilon)
    {
        L_dir = x_emit * p_in.m->eval(ray.direction, ws_ray.direction, p_norm) * dotProduct(ws_ray.direction, p_norm)
                * dotProduct(-ws_ray.direction, x_norm) / std::pow(p_out_dis, 2) / pdf_light;
    }

    L_indir = 0.0;
    if(get_random_float() < RussianRoulette)
    {
        Vector3f p_out_ndir = p_in.m->sample(ray.direction, p_norm).normalized();
        Ray wi_ray(p, p_out_ndir);
        Intersection p_out_obj = intersect(wi_ray);
        if(p_out_obj.happened && (!p_out_obj.m->hasEmission())) //check happen before emission
        {
            L_indir = castRay(wi_ray, depth + 1) * p_in.m->eval(ray.direction,wi_ray.direction,p_norm)
                      * dotProduct(wi_ray.direction, p_norm)
                      / p_in.m->pdf(ray.direction,wi_ray.direction,p_norm)
                      / RussianRoulette;
        }
    }
    return L_dir + L_indir;
}
