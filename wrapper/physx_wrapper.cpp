#include "physx_wrapper.h"
#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultCpuDispatcher.h"
#include "extensions/PxExtensionsAPI.h"

using namespace physx;

extern "C" {

void* physx_create_physics() {
    static PxDefaultAllocator gAllocator;
    static PxDefaultErrorCallback gErrorCallback;
    
    PxFoundation* foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    if(!foundation) {
        printf("Failed to create foundation\n");
        return NULL;
    }
    
    bool recordMemoryAllocations = true;
    PxPhysics* physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, 
                                        PxTolerancesScale(), recordMemoryAllocations);
    if(!physics) {
        printf("Failed to create physics\n");
        foundation->release();
        return NULL;
    }
    
    if(!PxInitExtensions(*physics, NULL)) {
        printf("Failed to initialize extensions\n");
        physics->release();
        foundation->release();
        return NULL;
    }
    
    return physics;
}


void physx_release_physics(void* physics) {
    PxPhysics* pxPhysics = static_cast<PxPhysics*>(physics);
    if(pxPhysics) {
        PxFoundation& foundationRef = pxPhysics->getFoundation();
        PxFoundation* foundation = &foundationRef;
        
        PxCloseExtensions();
        pxPhysics->release();
        foundation->release();
    }
}

void* physx_create_scene(void* physics) {
    PxPhysics* pxPhysics = static_cast<PxPhysics*>(physics);
    if(!pxPhysics) return NULL;
    
    PxSceneDesc sceneDesc(pxPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
    sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
    sceneDesc.filterShader = PxDefaultSimulationFilterShader;
    
    return pxPhysics->createScene(sceneDesc);
}

void physx_release_scene(void* scene) {
    PxScene* pxScene = static_cast<PxScene*>(scene);
    if(pxScene) pxScene->release();
}

void physx_simulate(void* scene, float delta_time) {
    PxScene* pxScene = static_cast<PxScene*>(scene);
    if(pxScene) pxScene->simulate(delta_time);
}

void physx_fetch_results(void* scene, int block) {
    PxScene* pxScene = static_cast<PxScene*>(scene);
    if(pxScene) pxScene->fetchResults(block != 0);
}

void* physx_create_rigid_dynamic(void* physics, float x, float y, float z) {
    PxPhysics* pxPhysics = static_cast<PxPhysics*>(physics);
    if(!pxPhysics) return NULL;
    
    PxTransform transform(PxVec3(x, y, z));
    return pxPhysics->createRigidDynamic(transform);
}

void* physx_create_rigid_static(void* physics, float x, float y, float z) {
    PxPhysics* pxPhysics = static_cast<PxPhysics*>(physics);
    if(!pxPhysics) return NULL;
    
    PxTransform transform(PxVec3(x, y, z));
    return pxPhysics->createRigidStatic(transform);
}

} // extern "C"