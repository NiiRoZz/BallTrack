#include "Entity.h"

namespace BallTrack
{
    Entity::Entity(const Model3D& model)
    : m_Model3D(model)
    {
    }

    void Entity::render(const TG3D& parentMat)
    {
        TG3D modelMatrix = parentMat * getModelMatrix();

        m_Model3D.render(modelMatrix);
    }

    const Sc3D& Entity::getScale()
    {
        return m_Scale;
    }

    void Entity::setScale(const Sc3D& scale)
    {
        m_Scale = scale;
    }

    const Rt3D& Entity::getRotation()
    {
        return m_Rotation;
    }

    void Entity::setRotation(const Rt3D& rotation)
    {
        m_Rotation = rotation;
    }

    const Pos3D& Entity::getPosition()
    {
        return m_Position;
    }

    void Entity::setPosition(const Pos3D& pos)
    {
        m_Position = pos;
    }

    TG3D Entity::getModelMatrix(void) const
    {
        return Tr3D(m_Position) * m_Rotation * m_Scale;
    }
}