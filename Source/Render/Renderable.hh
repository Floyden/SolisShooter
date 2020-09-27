#pragma once
#include "Mesh.hh"
#include "Material.hh"

namespace Solis
{
class Renderable
{
public:
	void SetMesh(const SPtr<Mesh>& mesh) { mMesh = mesh; }
	SPtr<Mesh> GetMesh() const { return mMesh; }

	void SetMaterial(const SPtr<DefaultMaterial>& material) { mMaterial = material; }
	SPtr<DefaultMaterial> GetMaterial() const { return mMaterial; }

private:
	SPtr<Mesh> mMesh;
	SPtr<DefaultMaterial> mMaterial;

};
}// namespace Solis