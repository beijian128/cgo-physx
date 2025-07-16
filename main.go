package main

/*
#cgo windows CXXFLAGS: -std=c++11 -I${SRCDIR}/physx/include
#cgo windows LDFLAGS: -L${SRCDIR}/physx/lib -lphysx_wrapper -lPhysX_64 -lPhysXCommon_64 -lPhysXFoundation_64 -lPhysXCooking_64 -lPhysXExtensions_static_64 -lPhysXPvdSDK_static_64 -luser32 -lgdi32 -lwinmm -lws2_32

#include "wrapper/physx_wrapper.h"  // 必须包含头文件
*/
import "C"
import (
	"fmt"
	"unsafe"
)

type Physics struct {
	ptr unsafe.Pointer
}

type Scene struct {
	ptr unsafe.Pointer
}

type RigidDynamic struct {
	ptr unsafe.Pointer
}

type RigidStatic struct {
	ptr unsafe.Pointer
}

func CreatePhysics() *Physics {
	phys := &Physics{
		ptr: C.physx_create_physics(),
	}
	if phys.ptr == nil {
		panic("Failed to create PhysX physics instance")
	}
	return phys
}

func (p *Physics) Release() {
	C.physx_release_physics(p.ptr)
	p.ptr = nil
}

func (p *Physics) CreateScene() *Scene {
	return &Scene{
		ptr: C.physx_create_scene(p.ptr),
	}
}

func (s *Scene) Release() {
	C.physx_release_scene(s.ptr)
	s.ptr = nil
}

func (s *Scene) Simulate(deltaTime float32) {
	C.physx_simulate(s.ptr, C.float(deltaTime))
}

func (s *Scene) FetchResults(block bool) {
	var b C.int
	if block {
		b = 1
	}
	C.physx_fetch_results(s.ptr, b)
}

func (p *Physics) CreateRigidDynamic(x, y, z float32) *RigidDynamic {
	return &RigidDynamic{
		ptr: C.physx_create_rigid_dynamic(p.ptr, C.float(x), C.float(y), C.float(z)),
	}
}

func (p *Physics) CreateRigidStatic(x, y, z float32) *RigidStatic {
	return &RigidStatic{
		ptr: C.physx_create_rigid_static(p.ptr, C.float(x), C.float(y), C.float(z)),
	}
}

func main() {
	physics := CreatePhysics()
	defer physics.Release()

	scene := physics.CreateScene()
	defer scene.Release()

	// 创建并实际使用刚体
	dynamicBody := physics.CreateRigidDynamic(0, 5, 0)
	staticBody := physics.CreateRigidStatic(0, 0, 0)

	// 添加调试输出或实际使用
	fmt.Printf("Created dynamic body at %v\n", dynamicBody.ptr)
	fmt.Printf("Created static body at %v\n", staticBody.ptr)

	// 模拟循环
	for i := 0; i < 60; i++ {
		scene.Simulate(1.0 / 60.0)
		scene.FetchResults(true)
	}
}
