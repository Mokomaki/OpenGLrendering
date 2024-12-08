#include "Scene.h"

#include "AssetManager.h"

void Scene::Initialize()
{
    m_camera = new Camera(glm::vec3(0.0f, 1.8f, 3.0f));

    m_assets["lit_textureshader"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Lit_texture.shader", true);
    m_assets["lit_solidcolorshader"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Lit_solidcolor.shader", true);
    m_assets["unlit_texture"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Unlit_texture.shader", false);
    m_assets["UVcube"] = new Mesh("D:/Documents/cube.obj");
    m_assets["suzannemesh"] = new Mesh("D:/Documents/suzannesmooth.obj");
    m_assets["planemesh"] = new Mesh("D:/Documents/plane.obj");
    m_assets["moonbaboon"] = new Texture("D:/Pictures/MOONBABOON.png");
    m_assets["rgbaimage"] = new Texture("D:/Pictures/rgbasmile.png");
    const char* containertexturepaths[] = { "D:/Pictures/paneldiff.tga", "D:/Pictures/panelspec.tga" };
    m_assets["containertextures"] = new Texture(containertexturepaths, 2);
    PbrProperties testboxprops = { glm::vec3(0.1f,0.1f,0.12f),glm::vec3(1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f),128.0f };
    m_uniformdata["testmaterial"] = new UniformData("testmaterial", testboxprops);
    PbrProperties groundprops = { glm::vec3(0.1f,0.1f,0.1f),glm::vec3(0.137,0.141f,0.169f),glm::vec3(0.1f,0.1f,0.1f),16.0f };
    m_uniformdata["groundmaterial"] = new UniformData("groundmaterial", groundprops);

    CreateLightDirectional(glm::vec3(3.0f, -1.0f, -3.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    CreateLightDirectional(glm::vec3(-3.0f, 1.0f, 3.5f), glm::vec3(0.3f, 0.0f, 0.35f));
    CreateLightPoint(glm::vec3(-5.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 100);
    CreateLightPoint(glm::vec3(5.0f, 2.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 200);
    //CreateLightPoint(glm::vec3(0.0f, 1.0f, -15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 600);

    WorldObject& groundplane = CreateWorldObect("ground");
    groundplane.Scale(glm::vec3(15.0f, 1.0f, 15.0f)).Translate(glm::vec3(0.0f, -1.5f, 0.0f));
    groundplane.AssociateWithAsset("lit_solidcolorshader");
    groundplane.AssociateWithAsset("planemesh");
    groundplane.AssociateWithUniform("groundmaterial");

    WorldObject& testcube = CreateWorldObect("testcube");
    testcube.Translate(glm::vec3(8.0f, 0.0f, 0.0f));
    testcube.AssociateWithAsset("lit_textureshader");
    testcube.AssociateWithAsset("UVcube");
    m_uniformdata["testcubeambient"] = new UniformData("u_ambient", glm::vec3(0.1, 0.1, 0.15));
    testcube.AssociateWithUniform("testcubeambient");
    m_uniformdata["testcubesmoothness"] = new UniformData("u_smoothness", 32.0f);
    testcube.AssociateWithUniform("testcubesmoothness");
    testcube.AssociateWithAsset("containertextures");
    m_uniformdata["testcubediffuseindex"] = new UniformData("u_diffuse", 0);
    testcube.AssociateWithUniform("testcubediffuseindex");
    m_uniformdata["testcubespecularindex"] = new UniformData("u_specular", 1);
    testcube.AssociateWithUniform("testcubespecularindex");

    WorldObject& rgbaobj = CreateWorldObect("rgbaobj");
    rgbaobj.Translate(glm::vec3(-10.0f, 2.0f, 0.0f)).Rotate(glm::vec3(1.0f,0.0f, 0.0f),90.0f).Rotate(glm::vec3(0.0f, 0.0f, -1.0f), 90.0f);
    rgbaobj.AssociateWithAsset("planemesh");
    rgbaobj.AssociateWithAsset("unlit_texture");
    rgbaobj.AssociateWithAsset("rgbaimage");


    for (int i = 0; i < 10; i++)
    {
        WorldObject& cube = CreateWorldObect("cube");
        cube.AssociateWithAsset("lit_solidcolorshader");
        cube.AssociateWithAsset("UVcube");
        cube.AssociateWithUniform("testmaterial");
        cube.Translate(glm::vec3(((i-5) * 3), 0.0f, -10.0f));
    }

    WorldObject& suzanne = CreateWorldObect("suzanne");
    suzanne.AssociateWithAsset("lit_solidcolorshader");
    suzanne.AssociateWithAsset("suzannemesh");
    suzanne.AssociateWithUniform("testmaterial");
}

WorldObject* Scene::GetWorldObjectByName(const char* name)
{
    for (auto& object : m_objects)
    {
        if (strcmp(object.m_name, name) == 0)
            return &object;
    }
}
std::vector<WorldObject*> Scene::GetWorldObjectsWithName(const char* name)
{
    std::vector<WorldObject*> out;
    for (auto& object : m_objects)
    {
        if (strcmp(object.m_name, name) == 0)
            out.push_back(&object);
    }
    return out;
}
WorldObject& Scene::CreateWorldObect(const char* name)
{
    m_objects.emplace_back(name);
    return m_objects.back();
}
DirectionalLight& Scene::CreateLightDirectional(glm::vec3 direction, glm::vec3 color)
{
    m_directionalLights.emplace_back(direction, color);
    return m_directionalLights.back();
}
PointLight& Scene::CreateLightPoint(glm::vec3 position, glm::vec3 color, float range)
{
    m_pointLights.emplace_back(position, color, range);
    return m_pointLights.back();
}