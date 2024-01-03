#include "Bubble.h"

#include "MathCustom.h"

double BubbleParticle::getDistanceToCamera(glm::vec3 cameraPos) const {

	auto [a, b, c, d] = coords;

	a += position;
	b += position;
	c += position;
	d += position;

	glm::vec3 middleFst = (a + b + c) / 3.f;
	glm::vec3 middleSec = (c + d + a) / 3.f;

	float d1 = glm::abs(glm::distance(middleFst, cameraPos));
	float d2 = glm::abs(glm::distance(middleSec, cameraPos));

	if (d1 <= d2)
		return MathCustom::closestPointToTriangleDivideEtImpera(cameraPos, a, b, c);
	return MathCustom::closestPointToTriangleDivideEtImpera(cameraPos, c, d, a);
}

void BubbleParticle::renderMesh() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

glm::vec3 BubbleParticle::getPosition() const
{
	return position;
}

unsigned BubbleParticle::getDiffuseTextureId() const
{
	return diffuseTextureId;
}

unsigned BubbleParticle::getSize() const
{
	return size;
}

void BubbleParticleGenerator::generateParticles()
{
	original_coords.resize(numberOfParticles);
	coords.resize(numberOfParticles);
	speed.resize(numberOfParticles);
	radius.resize(numberOfParticles);
	size.resize(numberOfParticles);

	std::random_device rd;

	std::uniform_real_distribution<float> RNGcoordsX(coord_min.x, coord_max.x);
	std::uniform_real_distribution<float> RNGcoordsY(coord_min.y, coord_max.y);
	std::uniform_real_distribution<float> RNGcoordsZ(coord_min.z, coord_max.z);
	std::uniform_real_distribution<float> RNGspeed(speedLimits.first, speedLimits.second);
	std::uniform_real_distribution<float> RNGradius(radiusLimits.first, radiusLimits.second);
	std::uniform_real_distribution<float> RNGsize(sizeLimits.first, sizeLimits.second);

	for (int i = 0; i < numberOfParticles; i++)
	{
		original_coords[i] = { RNGcoordsX(rd), RNGcoordsY(rd), RNGcoordsZ(rd) };
		coords[i] = original_coords[i];
		speed[i] = RNGspeed(rd);
		radius[i] = RNGradius(rd);
		size[i] = RNGsize(rd);
	}
}

void BubbleParticleGenerator::updateParticles(float currentFrame)
{
	for (int i = 0; i < numberOfParticles; i++)
	{
		coords[i].x = original_coords[i].x + sinf(currentFrame * 2 * speed[i]) * radius[i];
		coords[i].z = original_coords[i].z + cosf(currentFrame * 2 * speed[i]) * radius[i];
		coords[i].y += 0.004 * speed[i];
		if (coords[i].y >= coord_max.y)
			coords[i].y = coord_min.y;

		coords[i].x = std::max(std::min(coords[i].x, coord_max.x), coord_min.x);
		coords[i].z = std::max(std::min(coords[i].z, coord_max.z), coord_min.z);
	}
}

std::vector<BubbleParticle> BubbleParticleGenerator::getParticles() const
{
	std::vector<BubbleParticle> rsp;

	for (int i = 0; i < numberOfParticles; i++)
	{
		rsp.emplace_back(coords[i], diffuseTextureId, meshVAO, std::tuple<glm::vec3, glm::vec3, glm::vec3, glm::vec3>{ vertices[0].position, vertices[1].position, vertices[2].position, vertices[4].position }, size[i]);
	}

	return rsp;
}