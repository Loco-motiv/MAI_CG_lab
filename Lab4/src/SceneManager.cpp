#include "SceneManager.h"

//* Object

Object::Object(SceneManager* l_sceneManager, GLfloat l_alpha) : m_sceneManager{ l_sceneManager }, m_alpha{ l_alpha } {}

Object::~Object() {}

//* LightSource

LightSource::LightSource(SceneManager* l_sceneManager) : m_sceneManager(l_sceneManager) {}

LightSource::~LightSource() {}

//* Cube

Cube::Cube(SceneManager* l_sceneManager, sf::Vector3f l_position, sf::Vector3f l_rotation,
           GLfloat l_scale, ObjectMaterial l_material, GLfloat l_alpha) : Object(l_sceneManager, l_alpha)
{
    m_translateMatrix.Move(l_position.x, l_position.y, l_position.z);
    m_rotateMatrix.Rotate(l_rotation.x, l_rotation.y, l_rotation.z);
    m_scaleMatrix.ScaleXYZ(l_scale);

    if (l_material == ObjectMaterial::obsidian)
    {
        m_materialAmbient   = sf::Vector3<GLdouble>(0.05375f / m_sceneManager->lightAmbient, 0.05f / m_sceneManager->lightAmbient, 0.06625f / m_sceneManager->lightAmbient);
        m_materialDiffuse   = sf::Vector3<GLdouble>(0.18275f / m_sceneManager->lightDiffuse, 0.17f / m_sceneManager->lightDiffuse, 0.22525f / m_sceneManager->lightDiffuse);
        m_materialSpecular  = sf::Vector3<GLdouble>(0.332741f / m_sceneManager->lightSpecular, 0.328634f / m_sceneManager->lightSpecular, 0.346435f / m_sceneManager->lightSpecular);
        m_materialShininess = 32.0f;
    }
    else if (l_material == ObjectMaterial::pearl)
    {
        m_materialAmbient   = sf::Vector3<GLdouble>(0.25f / m_sceneManager->lightAmbient, 0.20725f / m_sceneManager->lightAmbient, 0.20725f / m_sceneManager->lightAmbient);
        m_materialDiffuse   = sf::Vector3<GLdouble>(1.0f / m_sceneManager->lightDiffuse, 0.829f / m_sceneManager->lightDiffuse, 0.829f / m_sceneManager->lightDiffuse);
        m_materialSpecular  = sf::Vector3<GLdouble>(0.296648f / m_sceneManager->lightSpecular, 0.296648f / m_sceneManager->lightSpecular, 0.296648f / m_sceneManager->lightSpecular);
        m_materialShininess = 8.0f;
    }
    else if (l_material == ObjectMaterial::ruby)
    {
        m_materialAmbient   = sf::Vector3<GLdouble>(0.1745f / m_sceneManager->lightAmbient, 0.01175f / m_sceneManager->lightAmbient, 0.01175f / m_sceneManager->lightAmbient);
        m_materialDiffuse   = sf::Vector3<GLdouble>(0.61424f / m_sceneManager->lightDiffuse, 0.04136f / m_sceneManager->lightDiffuse, 0.04136f / m_sceneManager->lightDiffuse);
        m_materialSpecular  = sf::Vector3<GLdouble>(0.727811f / m_sceneManager->lightSpecular, 0.626959f / m_sceneManager->lightSpecular, 0.626959f / m_sceneManager->lightSpecular);
        m_materialShininess = 64.0f;
    }
    else if (l_material == ObjectMaterial::cyanPlastic)
    {
        m_materialAmbient   = sf::Vector3<GLdouble>(0.0f / m_sceneManager->lightAmbient, 0.1f / m_sceneManager->lightAmbient, 0.06f / m_sceneManager->lightAmbient);
        m_materialDiffuse   = sf::Vector3<GLdouble>(0.50980392f / m_sceneManager->lightDiffuse, 0.50980392f / m_sceneManager->lightDiffuse, 0.50980392f / m_sceneManager->lightDiffuse);
        m_materialSpecular  = sf::Vector3<GLdouble>(0.50196078f / m_sceneManager->lightSpecular, 0.50196078f / m_sceneManager->lightSpecular, 0.50196078f / m_sceneManager->lightSpecular);
        m_materialShininess = 32.0f;
    }
}

Cube::~Cube() {}

void Cube::Render()
{
    m_sceneManager->m_sharedContext->graphics->m_shader->SetFloatVec3("material.ambient", m_materialAmbient.x, m_materialAmbient.y, m_materialAmbient.z);
    m_sceneManager->m_sharedContext->graphics->m_shader->SetFloatVec3("material.diffuse", m_materialDiffuse.x, m_materialDiffuse.y, m_materialDiffuse.z);
    m_sceneManager->m_sharedContext->graphics->m_shader->SetFloatVec3("material.specular", m_materialSpecular.x, m_materialSpecular.y, m_materialSpecular.z);
    m_sceneManager->m_sharedContext->graphics->m_shader->SetFloat("material.shininess", m_materialShininess);

    m_sceneManager->m_sharedContext->graphics->m_shader->SetFloatVec3("viewPosition",
                                                                      m_sceneManager->m_cameraPosition.x,
                                                                      m_sceneManager->m_cameraPosition.y,
                                                                      m_sceneManager->m_cameraPosition.z);
    m_sceneManager->m_sharedContext->graphics->m_shader->SetFloatMatrix("modelMatrix", m_modelMatrix.GetArray());
    m_sceneManager->m_sharedContext->graphics->m_shader->SetFloat("alpha", m_alpha);
    m_sceneManager->m_sharedContext->graphics->m_shader->SetFloatMatrix("transformMatrix", m_transformMatrix.GetArray());
    m_sceneManager->m_sharedContext->graphics->DrawCube();
}

void Cube::Update()
{
    m_modelMatrix     = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;
    m_transformMatrix = m_sceneManager->m_projectionMatrix * m_sceneManager->m_viewMatrix * m_modelMatrix;
}

//* LightCube

LightCube::LightCube(SceneManager* l_sceneManager, sf::Vector3f l_position, sf::Vector3f l_rotation,
                     GLfloat l_scale, sf::Vector3<GLdouble> l_lightColor) : LightSource(l_sceneManager)
{
    m_translateMatrix.Move(l_position.x, l_position.y, l_position.z);
    m_rotateMatrix.Rotate(l_rotation.x, l_rotation.y, l_rotation.z);
    m_scaleMatrix.ScaleXYZ(l_scale);

    m_lightColor = l_lightColor;
}

LightCube::~LightCube() {}

void LightCube::Render()
{
    m_sceneManager->m_sharedContext->graphics->m_lightSourceShader->SetFloatMatrix("transformMatrix", m_transformMatrix.GetArray());
    m_sceneManager->m_sharedContext->graphics->m_lightSourceShader->SetFloatVec3("lightColor", m_lightColor.x, m_lightColor.y, m_lightColor.z);
    m_sceneManager->m_sharedContext->graphics->DrawLightSourceCube();
}

void LightCube::Update()
{
    m_modelMatrix     = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;
    m_transformMatrix = m_sceneManager->m_projectionMatrix * m_sceneManager->m_viewMatrix * m_modelMatrix;
}

//* SceneManager

SceneManager::SceneManager(SharedContext* l_sharedContext) : m_sharedContext{ l_sharedContext } {}

SceneManager::~SceneManager()
{
    for (const auto elem : m_objects)
    {
        delete elem;
    }
    for (const auto elem : m_lightSources)
    {
        delete elem;
    }
}

Cube* SceneManager::MakeCube(sf::Vector3f l_position, sf::Vector3f l_rotation, GLfloat l_scale,
                             ObjectMaterial l_material, GLfloat l_alpha)
{
    Cube* cube = new Cube(this, l_position, l_rotation, l_scale, l_material, l_alpha);
    m_objects.push_back(cube);
    return cube;
}

LightCube* SceneManager::MakeLightCube(sf::Vector3f l_position, sf::Vector3f l_rotation, GLfloat l_scale,
                                       sf::Vector3<GLdouble> l_lightColor)
{
    LightCube* lightCube = new LightCube(this, l_position, l_rotation, l_scale, l_lightColor);
    m_lightSources.push_back(lightCube);
    return lightCube;
}

void SceneManager::Update()
{
    m_cameraPosition = m_sharedContext->camera->getPosition();

    m_viewMatrix = m_sharedContext->camera->getViewMatrix();

    if (m_flagProjection)
    {
        m_projectionMatrix.OrthographicProjection((float)m_sharedContext->window->GetWindowSize().x /
                                                      (float)m_sharedContext->window->GetWindowSize().y,
                                                  1.0f, -1.0f, 1.0f, -1.0f, 0.1f, 100.0f);
    }
    else
    {
        m_projectionMatrix.PerspectiveProjection(m_sharedContext->camera->getFOV(),
                                                 (float)m_sharedContext->window->GetWindowSize().x /
                                                     (float)m_sharedContext->window->GetWindowSize().y,
                                                 0.1f, 100.0f);
    }

    for (const auto elem : m_objects)
    {
        elem->Update();
    }
    for (const auto elem : m_lightSources)
    {
        elem->Update();
    }
}

void SceneManager::Render()
{
    m_sharedContext->graphics->m_shader->SetFloatVec3("light.ambient",
                                                      m_lightSources[0]->m_lightColor.x * lightAmbient,
                                                      m_lightSources[0]->m_lightColor.y * lightAmbient,
                                                      m_lightSources[0]->m_lightColor.z * lightAmbient);
    m_sharedContext->graphics->m_shader->SetFloatVec3("light.diffuse",
                                                      m_lightSources[0]->m_lightColor.x * lightDiffuse,
                                                      m_lightSources[0]->m_lightColor.y * lightDiffuse,
                                                      m_lightSources[0]->m_lightColor.z * lightDiffuse);
    m_sharedContext->graphics->m_shader->SetFloatVec3("light.specular",
                                                      m_lightSources[0]->m_lightColor.x * lightSpecular,
                                                      m_lightSources[0]->m_lightColor.y * lightSpecular,
                                                      m_lightSources[0]->m_lightColor.z * lightSpecular);
    m_sharedContext->graphics->m_shader->SetFloatVec3("light.position", 1.0f, 1.0f, 1.0f);

    for (const auto elem : m_objects)
    {
        elem->Render();
    }
    for (const auto elem : m_lightSources)
    {
        elem->Render();
    }
}