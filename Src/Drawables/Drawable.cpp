#include "Drawable.h"

namespace BallTrack
{
    const Sc3D& Drawable::getScale()
    {
        return m_Scale;
    }

    void Drawable::setScale(const Sc3D& scale)
    {
        m_Scale = scale;
    }

    const Rt3D& Drawable::getRotation()
    {
        return m_Rotation;
    }

    void Drawable::setRotation(const Rt3D& rotation)
    {
        m_Rotation = rotation;
    }

    const Tr3D& Drawable::getTranslation()
    {
        return m_Translation;
    }

    void Drawable::setTranslation(const Tr3D& translation)
    {
        m_Translation = translation;
    }
}