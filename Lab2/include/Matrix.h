#pragma once

#include <cmath>
#include <glad/glad.h>
#include <iostream>

class MatrixFloat
{
public:
    GLfloat m_elements[16];

    MatrixFloat()
    {
        for (GLint i = 0; i < 16; ++i)
        {
            m_elements[i] = 0.0f;
        }
        m_elements[0]  = 1.0f;
        m_elements[5]  = 1.0f;
        m_elements[10] = 1.0f;
        m_elements[15] = 1.0f;
    }

    MatrixFloat operator*(const MatrixFloat& other) const
    {
        MatrixFloat result;
        for (GLint row = 0; row < 4; ++row)
        {
            for (GLint col = 0; col < 4; ++col)
            {
                result.m_elements[row * 4 + col] = 0.0f;
                for (GLint k = 0; k < 4; ++k)
                {
                    result.m_elements[row * 4 + col] +=
                        m_elements[row * 4 + k] * other.m_elements[k * 4 + col];
                }
            }
        }
        return result;
    }

    void Rotate(GLfloat yaw, GLfloat pitch, GLfloat roll)
    {
        GLfloat yawSin   = std::sin(yaw);
        GLfloat yawCos   = std::cos(yaw);
        GLfloat pitchSin = std::sin(pitch);
        GLfloat pitchCos = std::cos(pitch);
        GLfloat rollSin  = std::sin(roll);
        GLfloat rollCos  = std::cos(roll);

        m_elements[0]  = yawCos * pitchCos;
        m_elements[1]  = yawSin * pitchCos;
        m_elements[2]  = -1 * pitchSin;
        m_elements[4]  = yawCos * pitchSin * rollSin - yawSin * rollCos;
        m_elements[5]  = yawSin * pitchSin * rollSin + yawCos * rollCos;
        m_elements[6]  = pitchCos * rollSin;
        m_elements[8]  = yawCos * pitchSin * rollCos + yawSin * rollSin;
        m_elements[9]  = yawSin * pitchSin * rollCos - yawCos * rollSin;
        m_elements[10] = pitchCos * rollCos;
    }

    void Move(GLfloat xDelta, GLfloat yDelta, GLfloat zDelta)
    {
        m_elements[12] += xDelta;
        m_elements[13] += yDelta;
        m_elements[14] += zDelta;
    }

    void PerspectiveProjection(GLfloat fovX, GLfloat aspectRatio, GLfloat front, GLfloat back)
    {
        const GLfloat DEG2RAD = std::acos(-1.0f) / 180.0f;

        GLfloat tangent = tan(fovX / 2.0f * DEG2RAD); // tangent of half fovX

        m_elements[0]  = 1.0f / tangent;
        m_elements[5]  = aspectRatio / tangent;
        m_elements[10] = -(back + front) / (back - front);
        m_elements[11] = -1.0f;
        m_elements[14] = -(2.0f * back * front) / (back - front);
    }

    void OrthographicProjection(GLfloat aspectRatio, GLfloat top, GLfloat right, GLfloat front, GLfloat back)
    {
        m_elements[0]  = 1.0f / right;
        m_elements[5]  = 1.0f / top * aspectRatio;
        m_elements[10] = -2.0f / (back - front);
        m_elements[14] = -(back + front) / (back - front);
    }

    const GLfloat* GetArray() const
    {
        return m_elements;
    }

    void Print() const
    {
        for (GLint row = 0; row < 4; ++row)
        {
            for (GLint col = 0; col < 4; ++col)
            {
                std::cout << m_elements[row * 4 + col] << ' ';
            }
            std::cout << '\n';
        }
    }

    void ScaleX(GLfloat scale)
    {
        m_elements[0] *= scale;
    }

    void ScaleY(GLfloat scale)
    {
        m_elements[5] *= scale;
    }

    void ScaleZ(GLfloat scale)
    {
        m_elements[10] *= scale;
    }

    void ScaleXYZ(GLfloat scale)
    {
        m_elements[0]  *= scale;
        m_elements[5]  *= scale;
        m_elements[10] *= scale;
    }
};