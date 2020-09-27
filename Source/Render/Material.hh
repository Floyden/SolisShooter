#pragma once
#include "Defines.hh"
#include "Program.hh"
#include "Math.hh"
#include "Texture.hh"

namespace Solis
{

class Material
{
public:
	virtual ~Material() {}
	virtual void Bind() = 0;

private:

};


class DefaultMaterial : public Material
{
public:
	SPtr<Texture> GetTexture() const { return mTexture; }
	void SetTexture(const SPtr<Texture> texture) { mTexture = texture; }

	void Bind();
private:
	SPtr<Texture> mTexture;
};
} // namespace Solis
