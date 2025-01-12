#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOffscreenSurface>
#include <QList>
#include <QVector3D>
#include <QVector>
#include <QWidget>
#include <QPoint>
#include <QPointF>
#include <QAction>
#include "pointdatarecords.h"
#include "camera.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    public:
        OpenGLWidget(QWidget* parent);
        ~OpenGLWidget() override;
        QList<PointDataRecords*> points();
        void setPointsByOpenGL(QList<PointDataRecords*> points);
        QPoint cutPosBegin();
        QPoint cutPosEnd();
        void deletePoints();
    protected:
        void initializeGL() override;
        void paintGL() override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;
    private:
        QList<PointDataRecords*> _points;
        QOpenGLBuffer _vbo;
        QOpenGLBuffer _vboLineLoop;
        QOpenGLShaderProgram* _shaderProgramm;
        QVector<int> _maxPoint; //[0] - X, [1] - Y, [2] - Z
        QVector<int> _minPoint; //[0] - X, [1] - Y, [2] - Z
        Camera* _camera;
        bool _debug;
        bool _pressed = false;
        QPoint _lastPos;
        QPointF _lastPosF;
        int _zoom;
        bool _isContrePress;
        QPoint _cutPosBegin, _cutPosEnd;
        float _kMoveX, _kMoveY;
        bool _isDeletePoints;
        QAction cutAction;
        void initCamera(QVector3D position);
        void initShader();
        void initVBO();
        void createVboLineLoop(QOpenGLBuffer* buffer, float x, float y, float w, float h);
        void createVboLineLoop(QOpenGLBuffer* buffer, QPointF point1, QPointF point2);
        void drawLineLoop(QOpenGLBuffer* buffer, QOpenGLShaderProgram* programm);
        void drawVbo();
        QPointF currentOpenGLPosition(QPoint mousePosition);
};

#endif // OPENGLWIDGET_H
