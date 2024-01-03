#pragma once
#include <random>
#include <tuple>
#include <utility>
#include <vector>
#include <vec3.hpp>

#include "IRenderable.h"
#include "AquariumPane.h"


class BubbleParticle : public IRenderable
{
public:
	BubbleParticle(glm::vec3 pos, unsigned diffTexId, unsigned VAO, const std::tuple<glm::vec3, glm::vec3, glm::vec3, glm::vec3>& crds, float sz)
		: position(pos), diffuseTextureId(diffTexId), VAO(VAO), coords(crds), size(sz) {}

	virtual ~BubbleParticle() = default;

	double getDistanceToCamera(glm::vec3 cameraPos) const override;

	void renderMesh() const override;


	glm::vec3 getPosition() const override;

	unsigned getDiffuseTextureId() const override;

	unsigned getSize() const;

protected:
	glm::vec3 position;
	unsigned diffuseTextureId;
	unsigned VAO;
	std::tuple<glm::vec3, glm::vec3, glm::vec3, glm::vec3> coords;
	float size;
};

class BubbleParticleGenerator : public AquariumPane
{
public:
	BubbleParticleGenerator(float len, float wid) :
		AquariumPane(len, wid, { 0,0,0 })
	{
		generateParticles();
	};

	~BubbleParticleGenerator() override = default;

	void generateParticles();

	void updateParticles(float currentFrame);

	std::vector<BubbleParticle> getParticles() const;


protected:
	glm::vec3 coord_min = { -2.3,0.5,-3.5 };
	glm::vec3 coord_max = { 2.3,3,-2.5 };

	std::pair<float, float> speedLimits = { 0.5f, 1.0f };
	std::pair<float, float> radiusLimits = { 0.0f, 0.4f };
	std::pair<float, float> sizeLimits = { 0.8f, 2.8f };
	int numberOfParticles = 20;

	std::vector<glm::vec3> coords;
	std::vector<glm::vec3> original_coords;
	std::vector<float> speed;
	std::vector<float> radius;
	std::vector<float> size;
};
