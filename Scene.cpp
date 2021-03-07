#include "Scene.h"
#define STB_IMAGE_IMPLEMENTATION

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

Scene::Scene() : ourShader("Shaders/1.model_loading.vs", "Shaders/1.model_loading.fs"), light(glm::vec3(0.0f, 10.5f, 0.0f)),
                 armchair1("Resources/armchair/Alfinosa.obj"), armchair2("Resources/armchair/Alfinosa.obj"), sofa("Resources/sofa/Alfinosa.obj"),
                 table("Resources/table/Ilaria_Table.obj"), bureau("Resources/bureau/7007.obj"), statue("Resources/statue/6.obj"), guitar("Resources/guitar/uploads_files_2032730_AcousticOBJ.obj"),
                /* chandelier("Resources/light/Chandelier ALICANTE SATIN SHADE L8.obj"),*/
                 floor("Textures/floor_diffuse.jpg", "Textures/floor_specular.jpg", 25.0f, 25.0f), 
                 wall1("Textures/wall_diffuse.jpg", "Textures/11.jpg", 10.0f, 25.0f), wall2("Textures/wall_diffuse.jpg", "Textures/11.jpg", 10.0f, 25.0f),
                 wall3("Textures/wall_diffuse.jpg", "Textures/11.jpg", 10.0f, 25.0f), wall4("Textures/wall_diffuse.jpg", "Textures/11.jpg", 10.0f, 25.0f),
                 roof("Textures/white.jpg", "Textures/11.jpg", 25.0f, 25.0f)
{
    /*Floor wall1;
    Floor wall2;
    Floor wall3;
    Floor wall4;
    Floor roof;*/
}
Scene::~Scene()
{

}

void Scene::drawScene(glm::mat4 projection, glm::mat4 viev, glm::vec3 cameraPos, float _xpos, float _zpos, float _rotate)
{
    ourShader.UseProgram();

    ourShader.Set_Matrix4fv_Uniform("projection", 1, GL_FALSE, &projection[0][0]);
    ourShader.Set_Matrix4fv_Uniform("view", 1, GL_FALSE, &viev[0][0]);
    ourShader.Set_Float3v_Uniform("viewPos", 1, &cameraPos[0]);

    light.setLight(ourShader);
    ourShader.Set_Float1_Uniform("shininess", 64.0f);

    glm::mat4 roomModel = glm::mat4(1.0f);
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &roomModel[0][0]);
    floor.Draw(ourShader);

    glm::mat4 wall1Model = glm::mat4(1.0f);
    wall1Model = glm::translate(wall1Model, glm::vec3(0.0f, 5.0f, -12.5f));
    wall1Model = glm::rotate(wall1Model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &wall1Model[0][0]);
    wall1.Draw(ourShader);

    glm::mat4 wall2Model = glm::mat4(1.0f);
    wall2Model = glm::translate(wall2Model, glm::vec3(0.0f, 5.0f, 12.5f));
    wall2Model = glm::rotate(wall2Model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &wall2Model[0][0]);
    wall2.Draw(ourShader);

    glm::mat4 wall3Model = glm::mat4(1.0f);
    wall3Model = glm::translate(wall3Model, glm::vec3(-12.5f, 5.0f, 0.0f));
    wall3Model = glm::rotate(wall3Model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wall3Model = glm::rotate(wall3Model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &wall3Model[0][0]);
    wall3.Draw(ourShader);

    glm::mat4 wall4Model = glm::mat4(1.0f);
    wall4Model = glm::translate(wall4Model, glm::vec3(12.5f, 5.0f, 0.0f));
    wall4Model = glm::rotate(wall4Model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wall4Model = glm::rotate(wall4Model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &wall4Model[0][0]);
    wall4.Draw(ourShader);

    glm::mat4 roofModel = glm::mat4(1.0f);
    roofModel = glm::translate(roofModel, glm::vec3(0.0f, 10.0f, 0.0f));
    //roofModel = glm::rotate(roofModel, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //roofModel = glm::rotate(roofModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &roofModel[0][0]);
    roof.Draw(ourShader);

    // Рендеринг загруженной модели
    glm::mat4 modelSofa = glm::mat4(1.0f);
    modelSofa = glm::translate(modelSofa, glm::vec3(0.0f, 0.0f, -2.0f));
    modelSofa = glm::scale(modelSofa, glm::vec3(0.025f, 0.025f, 0.025f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &modelSofa[0][0]);
    sofa.Draw(ourShader);

    glm::mat4 modelArmchair1 = glm::mat4(1.0f);
    modelArmchair1 = glm::translate(modelArmchair1, glm::vec3(-4.5f, 0.0f, -0.5f));
    modelArmchair1 = glm::rotate(modelArmchair1, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelArmchair1 = glm::scale(modelArmchair1, glm::vec3(0.0025f, 0.0025f, 0.0025f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &modelArmchair1[0][0]);
    armchair1.Draw(ourShader);

    glm::mat4 modelArmchair2 = glm::mat4(1.0f);
    modelArmchair2 = glm::translate(modelArmchair2, glm::vec3(4.5f, 0.0f, -0.5f));
    modelArmchair2 = glm::rotate(modelArmchair2, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelArmchair2 = glm::scale(modelArmchair2, glm::vec3(0.0025f, 0.0025f, 0.0025f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &modelArmchair2[0][0]);
    armchair2.Draw(ourShader);

    glm::mat4 tableModel = glm::mat4(1.0f);
    tableModel = glm::translate(tableModel, glm::vec3(0.0f, 0.0f, 2.5f));
    tableModel = glm::scale(tableModel, glm::vec3(0.04f, 0.04f, 0.04f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &tableModel[0][0]);
    table.Draw(ourShader);

    glm::mat4 bureauModel = glm::mat4(1.0f);
    bureauModel = glm::translate(bureauModel, glm::vec3(8.5f, 0.0f, 8.5f));
    bureauModel = glm::rotate(bureauModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    bureauModel = glm::rotate(bureauModel, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    bureauModel = glm::scale(bureauModel, glm::vec3(0.005f, 0.005f, 0.005f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &bureauModel[0][0]);
    bureau.Draw(ourShader);

    glm::mat4 statueModel = glm::mat4(1.0f);
    statueModel = glm::translate(statueModel, glm::vec3(0.0f, 1.2f, 2.4f));
    //statueModel = glm::rotate(statueModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //ureauModel = glm::rotate(bureauModel, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    statueModel = glm::scale(statueModel, glm::vec3(0.005f, 0.005f, 0.005f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &statueModel[0][0]);
    statue.Draw(ourShader);
    ///////////////////////////////////////////////// , float _xpos, float _zpos, float _rotate
    glm::mat4 guitarModel = glm::mat4(1.0f);
    guitarModel = glm::translate(guitarModel, glm::vec3(_xpos, 0.0f, _zpos));
    guitarModel = glm::rotate(guitarModel, glm::radians(_rotate), glm::vec3(0.0f, 1.0f, 0.0f));
    //ureauModel = glm::rotate(bureauModel, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    guitarModel = glm::scale(guitarModel, glm::vec3(0.05f, 0.05f, 0.05f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &guitarModel[0][0]);
    guitar.Draw(ourShader);

    /*glm::mat4 chandelierModel = glm::mat4(1.0f);
    chandelierModel = glm::translate(chandelierModel, glm::vec3(0.0f, 10.0f, 0.0f));
    //chandelierModel = glm::rotate(chandelierModel, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //ureauModel = glm::rotate(bureauModel, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    chandelierModel = glm::scale(chandelierModel, glm::vec3(0.005f, 0.005f, 0.005f));
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &chandelierModel[0][0]);
    chandelier.Draw(ourShader);*/

    /*glm::mat4 modelc = glm::mat4(1.0f);
    modelc = glm::translate(modelc, glm::vec3(0.0f, 0.0f, -10.0f)); // смещаем вниз чтобы быть в центре сцены
    //modelc = glm::scale(modelc, glm::vec3(1.0f, 1.0f, 1.0f));	// объект слишком большой для нашей сцены, поэтому немного уменьшим его
    modelc = glm::scale(modelc, glm::vec3(0.0025f, 0.0025f, 0.0025f));	// объект слишком большой для нашей сцены, поэтому немного уменьшим его
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &modelc[0][0]);
    chair.Draw(ourShader);

    glm::mat4 modelk = glm::mat4(1.0f);
    modelk = glm::translate(modelk, glm::vec3(0.0f, 0.0f, -5.0f)); // смещаем вниз чтобы быть в центре сцены
    //modelk = glm::rotate(modelk, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    modelk = glm::scale(modelk, glm::vec3(0.025f, 0.025f, 0.025f));

    //modelk
    ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &modelk[0][0]);
    armchair.Draw(ourShader);*/
}
