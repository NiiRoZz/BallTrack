#include "SphereEntity.h"

namespace BallTrack
{
    SphereEntity::SphereEntity(void)
    : PhysicEntity()
    {

    }

    SphereEntity::SphereEntity(const Model3D& model)
    : PhysicEntity(model)
    {

    }

    void SphereEntity::update(float dtSeconds)
    {
        //We take the maximum scale, so we are sure the sphere 
        float realRadius = m_Radius * std::max( std::max(m_Scale.mat[0][0], m_Scale.mat[1][1]), m_Scale.mat[2][2]);

        (void) realRadius;

        std::cout << "SphereEntity::update dtSeconds : " << dtSeconds << std::endl;
    }

    void SphereEntity::setRadius(float radius)
    {
        m_Radius = radius;
    }

    float SphereEntity::getRadius(void) const
    {
        return m_Radius;
    }
}