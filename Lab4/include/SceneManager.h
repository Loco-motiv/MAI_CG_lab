#pragma once

#include "SharedContext.h"

#include <vector>

enum class ObjectMaterial
{
    obsidian,
    pearl,
    ruby,
    cyanPlastic
};

class SceneManager;

class Object
{
public:
    Object(SceneManager* l_sceneManager, GLfloat l_alpha);
    virtual ~Object() = 0;

    virtual void Render() = 0;
    virtual void Update() = 0;

    SceneManager* m_sceneManager;
    MatrixFloat m_translateMatrix;
    MatrixFloat m_rotateMatrix;
    MatrixFloat m_scaleMatrix;
    MatrixFloat m_modelMatrix;

    MatrixFloat m_transformMatrix;

    sf::Vector3f m_materialAmbient;
    sf::Vector3f m_materialDiffuse;
    sf::Vector3f m_materialSpecular;
    GLfloat m_materialShininess;

    GLfloat m_alpha;
};

class Cube : public Object
{
public:
    Cube(SceneManager* l_sceneManager, sf::Vector3f l_position, sf::Vector3f l_rotation, GLfloat l_scale,
         ObjectMaterial l_material, GLfloat l_alpha);
    ~Cube();

    void Render();
    void Update();
};

class LightSource
{
public:
    LightSource(SceneManager* l_sceneManager);
    virtual ~LightSource() = 0;

    virtual void Render() = 0;
    virtual void Update() = 0;

    SceneManager* m_sceneManager;
    MatrixFloat m_translateMatrix;
    MatrixFloat m_rotateMatrix;
    MatrixFloat m_scaleMatrix;
    MatrixFloat m_modelMatrix;

    MatrixFloat m_transformMatrix;

    sf::Vector3<GLdouble> m_lightColor;
};

class LightCube : public LightSource
{
public:
    LightCube(SceneManager* l_sceneManager, sf::Vector3f l_position, sf::Vector3f l_rotation,
              GLfloat l_scale, sf::Vector3<GLdouble> l_lightColor);
    ~LightCube();

    void Render();
    void Update();
};

class SceneManager
{
public:
    SceneManager(SharedContext* l_sharedContext);
    ~SceneManager();

    Cube* MakeCube(sf::Vector3f l_position, sf::Vector3f l_rotation, GLfloat l_scale,
                   ObjectMaterial l_material, GLfloat l_alpha = 1.0f);
    LightCube* MakeLightCube(sf::Vector3f l_position, sf::Vector3f l_rotation, GLfloat l_scale,
                             sf::Vector3<GLdouble> l_lightColor);

    void Update();
    void Render();

    SharedContext* m_sharedContext;

    MatrixFloat m_projectionMatrix;
    MatrixFloat m_viewMatrix;

    sf::Vector3f m_cameraPosition;

    GLboolean m_flagProjection = false;

    std::vector<Object*> m_objects;
    std::vector<LightSource*> m_lightSources;
};
