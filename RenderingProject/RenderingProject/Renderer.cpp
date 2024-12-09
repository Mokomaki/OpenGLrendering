#include "Renderer.h"

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_clearColor = glm::vec4(0.17254901f, 0.17254901f, 0.17254901f, 1.0f);
    m_currentScene = nullptr;
    
    InitShadowFramebuffer();
}

void Renderer::Render(Scene* scene)
{
    m_currentScene = scene;
    ShadowPass();

    OpaquePass();
}

void Renderer::ShadowPass()
{
    glViewport(0, 0, m_shadowFBwidth, m_shadowFBheight);
    glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
    glDisable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    Clear(GL_DEPTH_BUFFER_BIT);
    //light projection
    float near_plane = 0.5f, far_plane = 50.0f;
    glm::mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(-m_currentScene->m_directionalLights[0].m_direction,glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
    m_currentLightSpaceMatrix = lightProjection * lightView;

    m_shadowObjectShader->Bind();
    for (int object = 0; object < m_currentScene->m_objects.size(); object++)
    {
        Mesh* meshAsset = nullptr;
        for (const char* assetname : m_currentScene->m_objects[object].m_assets)
        {
            Asset* currentAsset = m_currentScene->m_assets[assetname];
            if(currentAsset->GetAssetType() == ASSETTYPE::MESH)
            {
                meshAsset = (Mesh*)currentAsset;
                break;
            }
        }
        //TODO: Check if mesh should cast shadow here and 'continue;' if not
        m_shadowObjectShader->SetUniform("model",m_currentScene->m_objects[object].m_transform);
        m_shadowObjectShader->SetUniform("lightspacematrix", m_currentLightSpaceMatrix);
        meshAsset->Bind();
        DrawElements(meshAsset->GetIndexCount());
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    /*
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_debugshader->Bind();
    glBindVertexArray(quadVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, m_shadowDepthMapID);
    glDrawArrays(GL_TRIANGLES, 0, 6);*/
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::OpaquePass()
{
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int object = 0; object < m_currentScene->m_objects.size(); object++)
    {
        Mesh* meshAsset = nullptr;
        Shader* shaderAsset = nullptr;

        for (const char* assetname : m_currentScene->m_objects[object].m_assets)
        {
            Asset* currentAsset = m_currentScene->m_assets[assetname];
            currentAsset->Bind();
            switch (currentAsset->GetAssetType())
            {
            case ASSETTYPE::SHADER:
                shaderAsset = (Shader*)currentAsset;
                break;
            case ASSETTYPE::MESH:
                meshAsset = (Mesh*)currentAsset;
                break;
            }
        }

        if (shaderAsset == nullptr)
        {
            std::cout << "ERROR: Attempted to draw object without a shader!" << std::endl;
            continue;
        }

        ApplyUniforms(m_currentScene->m_objects[object], *m_currentScene, *shaderAsset);
        DrawElements(meshAsset->GetIndexCount());
    }
}

void Renderer::InitShadowFramebuffer()
{
    m_shadowObjectShader = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/shadowobject.shader", false);
    m_debugshader = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Framebuffer_debug.shader", false);
    
    m_shadowFBheight = 1024;
    m_shadowFBwidth = 1024;

    glGenFramebuffers(1, &m_shadowFBO);
    glGenTextures(1, &m_shadowDepthMapID);
    glBindTexture(GL_TEXTURE_2D, m_shadowDepthMapID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowFBwidth, m_shadowFBheight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowDepthMapID, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    float quadVertices[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}

void Renderer::SetViewportSize( int width,  int height)
{
    m_screenHeight = height;
    m_screenWidth = width;
}

void Renderer::DrawElements(unsigned int indexCount)
{
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Renderer::Clear(GLenum flags)
{
    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    glClear(flags);
}

void Renderer::ApplyUniforms(WorldObject& object, Scene& scene, Shader& shader)
{

    //TRANSFORMATION
    glm::mat4 viewMatrix = scene.m_camera->GetViewMatrix();
    shader.SetUniformTransfrom(object.m_transform, viewMatrix, scene.m_camera->m_Projection);

    //LIGHT SPECIFIC
    if (shader.IsLitShader())
    {
        //Shadowuniforms
        glActiveTexture(GL_TEXTURE10);
        glBindTexture(GL_TEXTURE_2D, m_shadowDepthMapID);
        shader.SetUniform("shadowmap", 10);
        shader.SetUniform("lightspacematrix", m_currentLightSpaceMatrix);

        //Inversetransposition for normal vectors
        glm::mat3 inverseTransposedModel;
        inverseTransposedModel = glm::inverse(object.m_transform);
        inverseTransposedModel = glm::transpose(inverseTransposedModel);
        shader.SetUniform("modelinversetransposed", inverseTransposedModel);

        int countDirs = scene.m_directionalLights.size();
        int countPoints = scene.m_pointLights.size();

        //Light uniforms
        shader.SetUniform("directionallightcount",countDirs);
        shader.SetUniform("pointlightcount",countPoints);
        shader.SetUniform("cameraposition", scene.m_camera->Position);
        for (int i = 0; i < scene.m_directionalLights.size();i++) 
        {
            std::string uniformname = "directionallights[" + std::to_string(i) + "]";
            shader.SetUniform(uniformname+".lightdirection", scene.m_directionalLights[i].m_direction);
            shader.SetUniform(uniformname + ".lightcolor", scene.m_directionalLights[i].m_color);
        }

        for (int i = 0; i < scene.m_pointLights.size(); i++)
        {
            std::string uniformname = "pointlights[" + std::to_string(i) + "]";
            shader.SetUniform(uniformname + ".position", scene.m_pointLights[i].m_position);
            shader.SetUniform(uniformname + ".color", scene.m_pointLights[i].m_color);
            shader.SetUniform(uniformname + ".constantterm", scene.m_pointLights[i].m_constantAttennuationTerm);
            shader.SetUniform(uniformname + ".linearterm", scene.m_pointLights[i].m_linearAttennuationTerm);
            shader.SetUniform(uniformname + ".quadraticterm", scene.m_pointLights[i].m_quadraticAttennuationTerm);
        }
    }
    //OBJECT SPECIFIC
    for (const char* uniformscenename : object.m_uniformData)
    {
        UniformData* uniformptr = scene.m_uniformdata[uniformscenename];
        switch (uniformptr->GetUniformType())
        {
        case UNIFORMDATATYPE::BOOL:
            bool bvalue;
            uniformptr->GetUniformValue(bvalue);
            shader.SetUniform(uniformptr->GetUniformName(), bvalue);
            break;
        case UNIFORMDATATYPE::INT:
            int ivalue;
            uniformptr->GetUniformValue(ivalue);
            shader.SetUniform(uniformptr->GetUniformName(), ivalue);
            break;
        case UNIFORMDATATYPE::FLOAT:
            float fvalue;
            uniformptr->GetUniformValue(fvalue);
            shader.SetUniform(uniformptr->GetUniformName(), fvalue);
            break;
        case UNIFORMDATATYPE::VEC3:
            glm::vec3 v3value;
            uniformptr->GetUniformValue(v3value);
            shader.SetUniform(uniformptr->GetUniformName(), v3value);
            break;
        case UNIFORMDATATYPE::MAT4:
            glm::mat4 m4value;
            uniformptr->GetUniformValue(m4value);
            shader.SetUniform(uniformptr->GetUniformName(), m4value);
            break;
        case UNIFORMDATATYPE::PbrProperty:
            PbrProperties pbrvalue;
            uniformptr->GetUniformValue(pbrvalue);
            shader.SetUniform(pbrvalue);
            break;
        default:
            break;
        }
    }
}