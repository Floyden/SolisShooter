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

	const HTexture& GetTexture() const { return mTexture; }
	void SetTexture(const HTexture& texture) { mTexture = texture; }

	SPtr<Program> GetProgram() const { return mProgram; }
	void SetProgram(const SPtr<Program> program) { mProgram = program; }

private:
	HTexture mTexture;
	SPtr<Program> mProgram;

};


class DefaultMaterial : public Material
{
public:
	DefaultMaterial() {};
	~DefaultMaterial() {};
/*
	SPtr<Texture> GetTexture() const { return mTexture; }
	void SetTexture(const SPtr<Texture> texture) { mTexture = texture; }

	SPtr<Program> GetProgram() const { return mProgram; }
	void SetProgram(const SPtr<Program> program) { mProgram = program; }*/

	void Bind() {  };
private:
};

} // namespace Solis
