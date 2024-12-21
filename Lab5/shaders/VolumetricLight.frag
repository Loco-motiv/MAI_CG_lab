#version 460 core

out vec4 FragColor;

uniform int u_numSpheres;
uniform int u_numCubes;

uniform vec3 u_sphereCenters[10];
uniform float u_sphereRadii[10];
uniform vec3 u_sphereColors[10];
uniform float u_sphereReflectivities[10];

uniform vec3 u_cubeCenters[10];
uniform vec3 u_cubeSizes[10];
uniform vec3 u_cubeColors[10];
uniform float u_cubeReflectivities[10];

uniform vec3 u_planeNormal;
uniform float u_planeD;
uniform vec3 u_planeColor;
uniform float u_planeReflectivity;

uniform vec3 u_lightPosition;
uniform vec3 u_lightColor;

uniform vec2 u_resolution;
uniform vec3 u_cameraPosition;
uniform mat4 u_viewMatrix;

uniform float u_density;
uniform float u_absorptionFactor;

const float u_scatterFactor = 0.1;
const int u_maxSteps = 100;
const float u_stepSize = 0.1;

const int MAX_BOUNCES = 3;

struct Sphere {
    vec3 center;
    float radius;
    vec3 color;
    float reflectivity;
};

struct Cube {
    vec3 center;
    vec3 size;
    vec3 color;
    float reflectivity;
};

struct Light {
    vec3 position;
    vec3 color;
};

bool RaySphereIntersect(vec3 rayOrigin, vec3 rayDir, Sphere sphere, out float t) {
    vec3 oc = rayOrigin - sphere.center;
    float a = dot(rayDir, rayDir);
    float b = 2.0 * dot(oc, rayDir);
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        t = -1.0;
        return false;
    } else {
        t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (t < 0.0) t = (-b + sqrt(discriminant)) / (2.0 * a);
        return t > 0.0;
    }
}

bool RayPlaneIntersect(vec3 rayOrigin, vec3 rayDir, vec3 normal, float d, out float t) {
    float denom = dot(normal, rayDir);
    if (abs(denom) > 0.0001) {
        t = -(dot(rayOrigin, normal) + d) / denom;
        return t > 0.0;
    }
    t = -1.0;
    return false;
}

bool RayCubeIntersect(vec3 rayOrigin, vec3 rayDir, Cube cube, out float t) {
    vec3 invDir = 1.0 / rayDir;
    vec3 tMin = (cube.center - cube.size * 0.5 - rayOrigin) * invDir;
    vec3 tMax = (cube.center + cube.size * 0.5 - rayOrigin) * invDir;

    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);

    float tNear = max(max(t1.x, t1.y), t1.z);
    float tFar = min(min(t2.x, t2.y), t2.z);

    if (tNear > 0.0 && tNear < tFar) {
        t = tNear;
        return true;
    }

    t = -1.0;
    return false;
}

vec3 CalculateLighting(vec3 point, vec3 normal, vec3 viewDir, vec3 color, float reflectivity) {
    vec3 lightDir = normalize(u_lightPosition - point);
    float diffuse = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec3 lightColor = u_lightColor * diffuse + specular;
    return mix(color, lightColor, reflectivity);
}

vec3 TraceRay(vec3 rayOrigin, vec3 rayDir, out float totalDistance) {
    vec3 finalColor = vec3(0.1);
    vec3 attenuation = vec3(1.0);
    totalDistance = 0.0;

    Sphere spheres[10];
    for (int i = 0; i < u_numSpheres; i++) {
        spheres[i] = Sphere(u_sphereCenters[i], u_sphereRadii[i], u_sphereColors[i], u_sphereReflectivities[i]);
    }

    Cube cubes[10];
    for (int i = 0; i < u_numCubes; i++) {
        cubes[i] = Cube(u_cubeCenters[i], u_cubeSizes[i], u_cubeColors[i], u_cubeReflectivities[i]);
    }

    for (int depth = 0; depth < MAX_BOUNCES; depth++) {
        float nearestT = 10000.0;
        vec3 hitColor = vec3(0.0);
        vec3 hitNormal;
        vec3 hitPoint;
        float hitReflectivity = 0.0;

        for (int i = 0; i < u_numSpheres; i++) {
            float t;
            if (RaySphereIntersect(rayOrigin, rayDir, spheres[i], t) && t < nearestT) {
                nearestT = t;
                hitPoint = rayOrigin + rayDir * t;
                hitNormal = normalize(hitPoint - spheres[i].center);
                hitColor = spheres[i].color;
                hitReflectivity = spheres[i].reflectivity;
            }
        }

        for (int i = 0; i < u_numCubes; i++) {
            float t;
            if (RayCubeIntersect(rayOrigin, rayDir, cubes[i], t) && t < nearestT) {
                nearestT = t;
                hitPoint = rayOrigin + rayDir * t;
                vec3 localPoint = hitPoint - cubes[i].center;
                vec3 absLocalPoint = abs(localPoint);
                if (absLocalPoint.x > absLocalPoint.y && absLocalPoint.x > absLocalPoint.z) {
                    hitNormal = vec3(sign(localPoint.x), 0.0, 0.0);
                } else if (absLocalPoint.y > absLocalPoint.x && absLocalPoint.y > absLocalPoint.z) {
                    hitNormal = vec3(0.0, sign(localPoint.y), 0.0);
                } else {
                    hitNormal = vec3(0.0, 0.0, sign(localPoint.z));
                }
                hitColor = cubes[i].color;
                hitReflectivity = cubes[i].reflectivity;
            }
        }

        float tPlane;
        if (RayPlaneIntersect(rayOrigin, rayDir, u_planeNormal, u_planeD, tPlane) && tPlane < nearestT) {
            nearestT = tPlane;
            hitPoint = rayOrigin + rayDir * tPlane;
            hitNormal = u_planeNormal;
            hitColor = u_planeColor;
            hitReflectivity = u_planeReflectivity;
        }

        if (nearestT == 10000.0) {
            break;
        }

        totalDistance += nearestT;

        vec3 viewDir = normalize(-rayDir);
        vec3 localColor = CalculateLighting(hitPoint, hitNormal, viewDir, hitColor, hitReflectivity);
        finalColor += attenuation * localColor;

        rayOrigin = hitPoint + hitNormal * 0.001;
        rayDir = reflect(rayDir, hitNormal);
        attenuation *= hitReflectivity;
    }

    return finalColor;
}

void main() {
    vec3 rayOrigin = u_cameraPosition;
    vec3 rayDir = normalize(vec3(gl_FragCoord.xy / u_resolution * 2.0 - 1.0, -1.0));
    rayDir = (inverse(u_viewMatrix) * vec4(rayDir, 0.0)).xyz;

    float totalDistance;
    vec3 color = TraceRay(rayOrigin, rayDir, totalDistance);

    if (totalDistance == 0.0) 
    {
        totalDistance = 10.0;
    }
    // Volumetric light effect
    float fogFactor = exp(-u_density * totalDistance * u_absorptionFactor);
    color = mix(u_lightColor, color, fogFactor);

    // Light scattering effect
    vec3 lightDir = normalize(u_lightPosition - rayOrigin);
    float scatter = max(dot(rayDir, lightDir), 0.0) * u_scatterFactor;
    color += scatter * u_lightColor;

    vec3 finalColor = color * u_lightColor;

    FragColor = vec4(finalColor, 1.0);
}