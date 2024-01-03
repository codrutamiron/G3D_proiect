#pragma once
#include <glm.hpp>
#include <cmath>
#include <algorithm>

namespace MathCustom
{
    static float closestPointToTriangleDivideEtImpera(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
    {
        const float precision = 0.01;

        glm::vec3 center = (a + b + c);
        center /= 3.f;

        float da = glm::abs(glm::length(center - a));
        float db = glm::abs(glm::length(center - b));
        float dc = glm::abs(glm::length(center - c));

        if (da < precision && db < precision && dc <= precision)
            return  glm::abs(glm::length(center - p));

        glm::vec3 m_ab = (a + b) * 0.5f;
        glm::vec3 m_ac = (a + c) * 0.5f;
        glm::vec3 m_bc = (b + c) * 0.5f;

        float d1 = glm::abs(glm::length(p - a));
        float d2 = glm::abs(glm::length(p - b));
        float d3 = glm::abs(glm::length(p - c));
        float d0 = glm::abs(glm::length(p - center));

        float minDist = std::min({ d1, d2, d3, d0 });

        if (minDist == d1)
            return closestPointToTriangleDivideEtImpera(p, a, m_ab, m_ac);
        if (minDist == d2)
            return closestPointToTriangleDivideEtImpera(p, b, m_ab, m_ac);
        if (minDist == d3)
            return closestPointToTriangleDivideEtImpera(p, c, m_ac, m_bc);
        return closestPointToTriangleDivideEtImpera(p, m_ab, m_bc, m_ac);
    }
}
