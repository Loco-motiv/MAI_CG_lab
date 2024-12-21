#include "SceneManager.h"

//* Object

Object::Object(SceneManager* l_sceneManager, ObjectMaterial l_material, GLfloat l_alpha) : m_sceneManager{ l_sceneManager }, m_alpha{ l_alpha }
{
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
        m_materialDiffuse   = sf::Vector3<GLdouble>(0.0f / m_sceneManager->lightDiffuse, 0.50980392f / m_sceneManager->lightDiffuse, 0.50980392f / m_sceneManager->lightDiffuse);
        m_materialSpecular  = sf::Vector3<GLdouble>(0.50196078f / m_sceneManager->lightSpecular, 0.50196078f / m_sceneManager->lightSpecular, 0.50196078f / m_sceneManager->lightSpecular);
        m_materialShininess = 32.0f;
    }
    else if (l_material == ObjectMaterial::yellowRubber)
    {
        m_materialAmbient   = sf::Vector3<GLdouble>(0.05f / m_sceneManager->lightAmbient, 0.05f / m_sceneManager->lightAmbient, 0.0f / m_sceneManager->lightAmbient);
        m_materialDiffuse   = sf::Vector3<GLdouble>(0.5f / m_sceneManager->lightDiffuse, 0.5f / m_sceneManager->lightDiffuse, 0.4f / m_sceneManager->lightDiffuse);
        m_materialSpecular  = sf::Vector3<GLdouble>(0.7f / m_sceneManager->lightSpecular, 0.7f / m_sceneManager->lightSpecular, 0.04f / m_sceneManager->lightSpecular);
        m_materialShininess = 8.0f;
    }
    else if (l_material == ObjectMaterial::silver)
    {
        m_materialAmbient   = sf::Vector3<GLdouble>(0.19225f / m_sceneManager->lightAmbient, 0.19225f / m_sceneManager->lightAmbient, 0.19225f / m_sceneManager->lightAmbient);
        m_materialDiffuse   = sf::Vector3<GLdouble>(0.50754f / m_sceneManager->lightDiffuse, 0.50754f / m_sceneManager->lightDiffuse, 0.50754f / m_sceneManager->lightDiffuse);
        m_materialSpecular  = sf::Vector3<GLdouble>(0.508273f / m_sceneManager->lightSpecular, 0.508273f / m_sceneManager->lightSpecular, 0.508273f / m_sceneManager->lightSpecular);
        m_materialShininess = 64.0f;
    }
    else if (l_material == ObjectMaterial::turquoise)
    {
        m_materialAmbient   = sf::Vector3<GLdouble>(0.1f / m_sceneManager->lightAmbient, 0.18725f / m_sceneManager->lightAmbient, 0.1745f / m_sceneManager->lightAmbient);
        m_materialDiffuse   = sf::Vector3<GLdouble>(0.396f / m_sceneManager->lightDiffuse, 0.74151f / m_sceneManager->lightDiffuse, 0.69102f / m_sceneManager->lightDiffuse);
        m_materialSpecular  = sf::Vector3<GLdouble>(0.297254f / m_sceneManager->lightSpecular, 0.30829f / m_sceneManager->lightSpecular, 0.306678f / m_sceneManager->lightSpecular);
        m_materialShininess = 16.0f;
    }
}

Object::~Object() {}

//* LightSource

LightSource::LightSource(SceneManager* l_sceneManager) : m_sceneManager(l_sceneManager) {}

LightSource::~LightSource() {}

//* Cube

Cube::Cube(SceneManager* l_sceneManager, sf::Vector3f l_position, sf::Vector3f l_rotation,
           GLfloat l_scale, ObjectMaterial l_material, GLfloat l_alpha) : Object(l_sceneManager, l_material, l_alpha)
{
    m_translateMatrix.Move(l_position.x, l_position.y, l_position.z);
    m_rotateMatrix.Rotate(l_rotation.x, l_rotation.y, l_rotation.z);
    m_scaleMatrix.ScaleXYZ(l_scale);
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

//* Sphere

Sphere::Sphere(SceneManager* l_sceneManager, sf::Vector3f l_position, sf::Vector3f l_rotation,
               GLfloat l_scale, ObjectMaterial l_material, GLfloat l_alpha) : Object(l_sceneManager, l_material, l_alpha)
{
    m_translateMatrix.Move(l_position.x, l_position.y, l_position.z);
    m_rotateMatrix.Rotate(l_rotation.x, l_rotation.y, l_rotation.z);
    m_scaleMatrix.ScaleXYZ(l_scale);
}

Sphere::~Sphere() {}

void Sphere::Render()
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
    m_sceneManager->m_sharedContext->graphics->DrawSphere();
}

void Sphere::Update()
{
    m_modelMatrix     = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;
    m_transformMatrix = m_sceneManager->m_projectionMatrix * m_sceneManager->m_viewMatrix * m_modelMatrix;
}

//* Plane

Plane::Plane(SceneManager* l_sceneManager, sf::Vector3f l_position, sf::Vector3f l_rotation,
             GLfloat l_scale, ObjectMaterial l_material, GLfloat l_alpha) : Object(l_sceneManager, l_material, l_alpha)
{
    m_translateMatrix.Move(l_position.x, l_position.y, l_position.z);
    m_rotateMatrix.Rotate(l_rotation.x, l_rotation.y, l_rotation.z);
    m_scaleMatrix.ScaleX(100.0f);
    m_scaleMatrix.ScaleZ(100.0f);
    m_scaleMatrix.ScaleY(0.1f);
    m_scaleMatrix.ScaleXYZ(l_scale);
}

Plane::~Plane() {}

void Plane::Render()
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

void Plane::Update()
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
    m_cubeNumber++;
    return cube;
}

LightCube* SceneManager::MakeLightCube(sf::Vector3f l_position, sf::Vector3f l_rotation, GLfloat l_scale,
                                       sf::Vector3<GLdouble> l_lightColor)
{
    LightCube* lightCube = new LightCube(this, l_position, l_rotation, l_scale, l_lightColor);
    m_lightSources.push_back(lightCube);
    return lightCube;
}

Sphere* SceneManager::MakeSphere(sf::Vector3f l_position, sf::Vector3f l_rotation, GLfloat l_scale, ObjectMaterial l_material, GLfloat l_alpha)
{
    Sphere* sphere = new Sphere(this, l_position, l_rotation, l_scale, l_material, l_alpha);
    m_objects.push_back(sphere);
    m_sphereNumber++;
    return sphere;
}

Plane* SceneManager::MakePlane(sf::Vector3f l_position, sf::Vector3f l_rotation, GLfloat l_scale, ObjectMaterial l_material, GLfloat l_alpha)
{
    Plane* plane = new Plane(this, l_position, l_rotation, l_scale, l_material, l_alpha);
    m_objects.push_back(plane);
    return plane;
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

void SceneManager::RenderRayTracing()
{
    m_sharedContext->graphics->m_volumetricLightShader->Use();

    m_sharedContext->graphics->m_volumetricLightShader->SetInt("u_numSpheres", m_sphereNumber);
    m_sharedContext->graphics->m_volumetricLightShader->SetInt("u_numCubes", m_cubeNumber);

    int sphereCount = 0;
    for (const auto& object : m_objects)
    {
        if (sphereCount >= 10)
        {
            break; //* 10 spheres max
        }
        if (Sphere* sphere = dynamic_cast<Sphere*>(object))
        {
            m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_sphereCenters[" + std::to_string(sphereCount) + "]", sphere->m_translateMatrix[12], sphere->m_translateMatrix[13], sphere->m_translateMatrix[14]);
            m_sharedContext->graphics->m_volumetricLightShader->SetFloat("u_sphereRadii[" + std::to_string(sphereCount) + "]", sphere->m_scaleMatrix[0]);
            m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_sphereColors[" + std::to_string(sphereCount) + "]", sphere->m_materialDiffuse.x, sphere->m_materialDiffuse.y, sphere->m_materialDiffuse.z);
            m_sharedContext->graphics->m_volumetricLightShader->SetFloat("u_sphereReflectivities[" + std::to_string(sphereCount) + "]", sphere->m_materialSpecular.x);
            sphereCount++;
        }
    }

    int cubeCount = 0;
    for (const auto& object : m_objects)
    {
        if (cubeCount >= 10)
        {
            break; //* 10 cubes max
        }
        if (Cube* cube = dynamic_cast<Cube*>(object))
        {
            m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_cubeCenters[" + std::to_string(cubeCount) + "]", cube->m_translateMatrix[12], cube->m_translateMatrix[13], cube->m_translateMatrix[14]);
            m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_cubeSizes[" + std::to_string(cubeCount) + "]", cube->m_scaleMatrix[0], cube->m_scaleMatrix[5], cube->m_scaleMatrix[10]);
            m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_cubeColors[" + std::to_string(cubeCount) + "]", cube->m_materialDiffuse.x, cube->m_materialDiffuse.y, cube->m_materialDiffuse.z);
            m_sharedContext->graphics->m_volumetricLightShader->SetFloat("u_cubeReflectivities[" + std::to_string(cubeCount) + "]", cube->m_materialSpecular.x);
            cubeCount++;
        }
    }

    for (const auto& object : m_objects)
    {
        //* one plane
        if (Plane* plane = dynamic_cast<Plane*>(object))
        {
            sf::Vector3f planeNormal   = sf::Vector3f(plane->m_rotateMatrix[4], plane->m_rotateMatrix[5], plane->m_rotateMatrix[6]);
            sf::Vector3f planePosition = sf::Vector3f(plane->m_translateMatrix[12], plane->m_translateMatrix[13], plane->m_translateMatrix[14]);

            m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_planeNormal", planeNormal.x, planeNormal.y, planeNormal.z);
            m_sharedContext->graphics->m_volumetricLightShader->SetFloat("u_planeD", -Dot(planePosition, planeNormal));
            m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_planeColor", plane->m_materialDiffuse.x, plane->m_materialDiffuse.y, plane->m_materialDiffuse.z);
            m_sharedContext->graphics->m_volumetricLightShader->SetFloat("u_planeReflectivity", plane->m_materialSpecular.x);
            break;
        }
    }

    //* one light
    if (!m_lightSources.empty())
    {
        LightSource* light = m_lightSources[0];
        m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_lightPosition", light->m_translateMatrix[12], light->m_translateMatrix[13], light->m_translateMatrix[14]);
        m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_lightColor", light->m_lightColor.x, light->m_lightColor.y, light->m_lightColor.z);
    }

    m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec3("u_cameraPosition", m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z);
    m_sharedContext->graphics->m_volumetricLightShader->SetFloatMatrix("u_viewMatrix", m_viewMatrix.GetArray());
    m_sharedContext->graphics->m_volumetricLightShader->SetFloatVec2("u_resolution", m_sharedContext->window->GetWindowSize().x, m_sharedContext->window->GetWindowSize().y);
    m_sharedContext->graphics->m_volumetricLightShader->SetFloat("u_density", m_densityFactor);
    m_sharedContext->graphics->m_volumetricLightShader->SetFloat("u_absorptionFactor", m_absorptionFactor);

    m_sharedContext->graphics->DrawFullScreenRectangle();
}