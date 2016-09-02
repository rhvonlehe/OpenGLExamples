#include <thread>
#include <chrono>
#include <QFile>
#include <QPainter>
#include <QKeyEvent>

#include "GLHelpers.h"
#include "AppGLScene.h"

AppGLScene::AppGLScene()
{
    QSurfaceFormat fmt;
    fmt.setSamples(16);
    setFormat(fmt);

    createGradient();

    setFocusPolicy(Qt::StrongFocus);  // Needed to get key presses
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

    makeCurrent();
    m_shader.bind();
    m_shader.setAttributeArray("Vertex", GL_FLOAT, m_data.constData(), 3,
                               sizeof(ScenePoint));
    m_shader.enableAttributeArray("Vertex");
    m_shader.setAttributeArray("Normal", GL_FLOAT, &m_data[0].normal, 3,
                               sizeof(ScenePoint));
    m_shader.enableAttributeArray("Normal");

    update();
}

void AppGLScene::drawScene(const QMatrix4x4 &mvMatrix)
{
    m_shader.bind();

    m_shader.setAttributeArray("Vertex", GL_FLOAT, m_data.constData(), 3,
                               sizeof(ScenePoint));
    m_shader.enableAttributeArray("Vertex");
    m_shader.setAttributeArray("Normal", GL_FLOAT, &m_data[0].normal, 3,
            sizeof(ScenePoint));
    m_shader.enableAttributeArray("Normal");
    m_shader.setUniformValue("projectionMatrix", m_projectionMatrix);
    m_shader.setUniformValue("modelViewMatrix", mvMatrix);
    m_shader.setUniformValue("mvpMatrix", m_projectionMatrix*mvMatrix);
    m_shader.setUniformValue("normalMatrix", mvMatrix.normalMatrix());

    glDrawArrays(GL_TRIANGLES, 0, m_data.size());

    m_shader.disableAttributeArray("Vertex");
    m_shader.disableAttributeArray("Normal");
}

void AppGLScene::viewFront(void)
{
    m_eye = {0, 0, eyeDistance};
    m_up = {0, 1, 0};
    update();
}

void AppGLScene::viewBack(void)
{
    m_eye = {0, 0, -eyeDistance};
    m_up = {0, 1, 0};
    update();
}

void AppGLScene::viewLeft(void)
{
    m_eye = {eyeDistance, 0, 0};
    m_up = {0, 1, 0};
    update();
}

void AppGLScene::viewRight(void)
{
    m_eye = {-eyeDistance, 0, 0};
    m_up = {0, 1, 0};
    update();
}

void AppGLScene::viewTop(void)
{
    m_eye = {0, eyeDistance, 0};
    m_up = {0, 0, -1};
    update();
}

void AppGLScene::viewBottom(void)
{
    m_eye = {0, -eyeDistance, 0};
    m_up = {0, 0, -1};
    update();
}

void AppGLScene::drawPolyline(void)
{
    qDebug() << "Context() gives: " << this->context();
    qDebug() << "Context()->nativeHandle() is:" <<
                this->context()->nativeHandle();

    HMODULE handle = (HMODULE) this->context()->openGLModuleHandle();
    qDebug() << "handle is " << handle;

    m_once = true;

    //makeCurrent();
    WId id = effectiveWinId();
    HWND hWnd = (HWND)winId();
    HDC dc = ::GetDC((HWND)hWnd);
    wglMakeCurrent(dc, (HGLRC)handle);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window()->width(), window()->height());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(15, 0, 0);
    glEnd();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // The above doesn't draw anything, likely because it doesn't
    // send anything to shaders.

//    update();
}


void AppGLScene::resizeGL(int w, int h)
{

}

void AppGLScene::paintGL(void)
{
    setProjectionMatrix();

    m_viewMatrix.setToIdentity();
    m_viewMatrix.lookAt(m_eye, m_center, m_up);

    QPainter painter;
    painter.begin(this);
//    drawBackground(painter);
    painter.beginNativePainting();

    if (!m_once)
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    }
    glViewport(0, 0, window()->width(), window()->height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_modelMatrix.setToIdentity();
    m_modelMatrix.scale(m_scale);
    m_modelMatrix.rotate(0, 0, 1, 0);
    m_modelMatrix.rotate(-90, 1, 0, 0);

    QMatrix4x4 modelViewMatrix = m_viewMatrix*m_modelMatrix;

    if (m_data.size())
    {
        drawScene(modelViewMatrix);
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    painter.endNativePainting();
    painter.end();
}

void AppGLScene::initializeGL(void)
{
    initializeOpenGLFunctions();
    m_initialWinWidth = rect().width();
    m_initialWinHeight = rect().height();
    //glClearColor(0, 0, 0, 0);
    QString glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << "OpenGL version:" << glVersion;

    m_shader.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                     fileContent(":/phong.vert"));
    m_shader.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                     fileContent(":/phong.frag"));

    m_shader.link();
    m_shader.bind();

    m_shader.setUniformValue("mat.ka", QVector3D(0.1f, 0.0f, 0.0f));
    m_shader.setUniformValue("mat.kd", QVector3D(0.7f, 0.85f, 0.85f));
    m_shader.setUniformValue("mat.ks", QVector3D(1.0f, 1.0f, 1.0f));
    m_shader.setUniformValue("mat.shininess", 128.0f);

    m_shader.setUniformValue("light.position", QVector3D(eyeDistance, 1, 1));
    m_shader.setUniformValue("light.intensity", QVector3D(1, 1, 1));
}

void AppGLScene::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_O:
        m_proj = PROJ_ORTHO;
        break;
    case Qt::Key_P:
        m_proj = PROJ_PERSP;
        break;
    }

    update();
}

void AppGLScene::keyReleaseEvent(QKeyEvent *event)
{
}

void AppGLScene::mousePressEvent(QMouseEvent *event)
{
    if (event->modifiers() && Qt::AltModifier)
    {
        m_lastPos = event->pos();
    }
}

void AppGLScene::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->modifiers() & Qt::AltModifier)
    {
        if (event->buttons() & Qt::MidButton)
        {
//            // TODO fix scaling factor, it's very crude now
//            //
//            float scaleAdjust = dy;

//            scaleAdjust /= 200;

//            m_scale = m_scale + scaleAdjust;

            dy *= 2;

            float scaleAdjust = (1 + ((float)dy / (float) rect().height()));
            m_scale = m_scale * scaleAdjust;

            update();
            m_lastPos = event->pos();
        }
    }
}

void AppGLScene::createGradient(void)
{
    m_gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_gradient.setCenter(0.45, 0.50);
    m_gradient.setFocalPoint(0.40, 0.45);
    m_gradient.setColorAt(0.0, QColor(70, 110, 142));
    m_gradient.setColorAt(0.4, QColor(46, 78, 110));
    m_gradient.setColorAt(0.8, QColor(0, 41, 101));
}

void AppGLScene::drawBackground(QPainter& painter)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_gradient);
    painter.drawRect(rect());
}

void AppGLScene::setProjectionMatrix(void)
{
    m_projectionMatrix.setToIdentity();
    float windowWidth = rect().width();
    float windowHeight = rect().height();
    float left, right, bottom, top;
    float aratio = (float) windowWidth / (float) windowHeight;
    float orthoConst;
    qDebug() << "win wid, win hei" << windowWidth << windowHeight;

    // I modify the vertical FOV in an attempt to keep the size of the
    // model the same as the vertical size of the window changes.
    //
    float vFov = 90 * ((float)windowHeight / m_initialWinHeight);
    qDebug() << "vFov" << vFov;

    switch (m_proj)
    {
    case PROJ_PERSP:
        m_projectionMatrix.perspective(vFov, qreal(windowWidth)/qreal(windowHeight), 0.5, 40);
        break;
    case PROJ_ORTHO:
    default:
        if (windowWidth > windowHeight)
        {
            orthoConst = windowHeight / 300;
            top = orthoConst; //3.0f;
            bottom = -top;
            right = top * aratio;
            left = -right;
        }
        else
        {
            orthoConst = windowWidth / 300;
            right = orthoConst; //5.0f;
            left = -right;
            top = right / aratio;
            bottom = -top;
        }

        qDebug() << "l r b t = " << left << right << bottom << top;
        m_projectionMatrix.ortho(left, right, bottom, top, 0.5, 40);
        break;
    }
}
