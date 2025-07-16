#ifndef PHYSX_WRAPPER_H
#define PHYSX_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void* physx_create_physics();
void physx_release_physics(void* physics);

void* physx_create_scene(void* physics);
void physx_release_scene(void* scene);

void physx_simulate(void* scene, float delta_time);
void physx_fetch_results(void* scene, int block);

void* physx_create_rigid_dynamic(void* physics, float x, float y, float z);
void* physx_create_rigid_static(void* physics, float x, float y, float z);

#ifdef __cplusplus
}
#endif

#endif // PHYSX_WRAPPER_H