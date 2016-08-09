#include <QOpenGLTexture>
#include <QOpenGLWindow>
#include "CubeGLScene.h"
#include "SceneGLWindow.h"

CubeGLScene::CubeGLScene(SceneGLWindow *wnd)
    : AbstractGLScene(wnd)
{
    initializeCubeData();
}

CubeGLScene::~CubeGLScene(void)
{
    delete m_texture;
}

void CubeGLScene::initialize(void)
{
    AbstractGLScene::initialize();
    m_initialized = true;
    if (!m_tex.isNull())
    {
        initializeTexture();
    }
    glClearColor(1, 1, 1, 0);
    glShadeModel(GL_SMOOTH);
}

void CubeGLScene::paint(void)
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window()->width(), window()->height());
    glLoadIdentity();

    glRotatef( 45, 1.0, 0.0, 0.0 );
    glRotatef( m_angle, 0.0, 1.0, 0.0 );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    paintCube();
}

void CubeGLScene::setTexture(const QImage &img)
{
    m_tex = img;
    if (m_initialized)
    {
        initializeTexture();
    }
}

void CubeGLScene::initializeTexture(void)
{
    m_texture = new QOpenGLTexture(m_tex.mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void CubeGLScene::initializeCubeData(void)
{
    m_data ={
        // FRONT FACE
        {{-0.5, -0.5,  0.5}, {0, 0}},        {{ 0.5, -0.5,  0.5}, {1, 0}},
        {{ 0.5,  0.5,  0.5}, {1, 1}},        {{-0.5,  0.5,  0.5}, {0, 1}},

        // TOP FACE
        {{-0.5,  0.5,  0.5}, {0, 0}},        {{ 0.5,  0.5,  0.5}, {1, 0}},
        {{ 0.5,  0.5, -0.5}, {1, 1}},        {{-0.5,  0.5, -0.5}, {0, 1}},

        // BACK FACE
        {{-0.5,  0.5, -0.5}, {0, 0}},        {{ 0.5,  0.5, -0.5}, {1, 0}},
        {{ 0.5, -0.5, -0.5}, {1, 1}},        {{-0.5, -0.5, -0.5}, {0, 1}},

         // BOTTOM FACE
        {{-0.5, -0.5, -0.5}, {0, 0}},        {{ 0.5, -0.5, -0.5}, {1, 0}},
        {{ 0.5, -0.5,  0.5}, {1, 1}},        {{-0.5, -0.5,  0.5}, {0, 1}},

        // LEFT FACE
        {{-0.5, -0.5, -0.5}, {0, 0}},        {{-0.5, -0.5,  0.5}, {1, 0}},
        {{-0.5,  0.5,  0.5}, {1, 1}},        {{-0.5,  0.5, -0.5}, {0, 1}},

        // RIGHT FACE
        {{ 0.5, -0.5,  0.5}, {0, 0}},        {{ 0.5, -0.5, -0.5}, {1, 0}},
        {{ 0.5,  0.5, -0.5}, {1, 1}},        {{ 0.5,  0.5,  0.5}, {0, 1}},
    };
}

void CubeGLScene::paintCube()
{
    if (m_texture)
    {
        m_texture->bind();
    }
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    for(int i=0;i < m_data.size(); ++i)
    {
        const TexturedPoint &pt = m_data.at(i);
        glTexCoord2d(pt.uv.x(), pt.uv.y());
        glVertex3f(pt.coord.x(), pt.coord.y(), pt.coord.z());
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
