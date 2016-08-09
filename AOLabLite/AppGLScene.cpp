#include <QFile>

#include "GLHelpers.h"
#include "AppGLScene.h"

AppGLScene::AppGLScene()
{

}

AppGLScene::~AppGLScene()
{
    setMinimumSize(300, 250);
}

void AppGLScene::addScenePoints(QVector<ScenePoint>& data)
{
    // If m_data has nothing in it, we can just 'move' the
    // contents of data into it.  Else append.
    //
    if (!m_data.length())
    {
        m_data = std::move(data);
    }
    else
    {
        m_data << data;
    }

    m_shader.setAttributeArray("Vertex", GL_FLOAT, m_data.constData(), 3,
                               sizeof(ScenePoint));
    m_shader.enableAttributeArray("Vertex");
    m_shader.setAttributeArray("Normal", GL_FLOAT, &m_data[0].normal, 3,
                               sizeof(ScenePoint));

}

void AppGLScene::paintScene(const QMatrix4x4 &mvMatrix)
{
    m_shader.setUniformValue("projectionMatrix", m_projectionMatrix);
    m_shader.setUniformValue("modelViewMatrix", mvMatrix);
    m_shader.setUniformValue("mvpMatrix", m_projectionMatrix*mvMatrix);
    m_shader.setUniformValue("normalMatrix", mvMatrix.normalMatrix());

    glDrawArrays(GL_TRIANGLES, 0, m_data.size());
}


void AppGLScene::resizeGL(int w, int h)
{

}

void AppGLScene::paintGL(void)
{
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(90, qreal(window()->width())/qreal(window()->height()), 0.5, 40);

    m_viewMatrix.setToIdentity();
    m_viewMatrix.lookAt({0,0,2}, {0,0,0}, {0, 1, 0});

    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window()->width(), window()->height());


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_modelMatrix.setToIdentity();
    m_modelMatrix.scale(0.05);
    m_modelMatrix.rotate(m_angle, 0, 1, 0);
    m_modelMatrix.rotate(-90, 1, 0, 0);

    QMatrix4x4 modelViewMatrix = m_viewMatrix*m_modelMatrix;

    paintScene(modelViewMatrix);
}

void AppGLScene::initializeGL(void)
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 0);

    m_shader.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                     fileContent(":/phong.vert"));
    m_shader.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                     fileContent(":/phont.frag"));

    m_shader.link();
    m_shader.bind();
    m_shader.setUniformValue("mat.ka", QVector3D(0.1, 0, 0.0));
    m_shader.setUniformValue("mat.kd", QVector3D(0.7, 0.0, 0.0));
    m_shader.setUniformValue("mat.ks", QVector3D(1.0, 1.0, 1.0));
    m_shader.setUniformValue("mat.shininess", 128.0f);

    m_shader.setUniformValue("light.position", QVector3D(2, 1, 1));
    m_shader.setUniformValue("light.intensity", QVector3D(1,1,1));
}

