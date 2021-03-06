#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QtWidgets/QOpenGLWidget>
#include <mpv/client.h>
#include <mpv/opengl_cb.h>
#include <mpv/qthelper.hpp>

class mpvWidget Q_DECL_FINAL: public QOpenGLWidget
{
    Q_OBJECT
public:
    mpvWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~mpvWidget();
    void command(const QVariant& params);
    void setProperty(const QString& name, const QVariant& value);
    QVariant getProperty(const QString& name) const;
    QSize sizeHint() const { return QSize(480, 270);}
    void loadFile(QString);
    void setLoop(bool looping);
    void stop();
    void setCrop();
Q_SIGNALS:
    void durationChanged(int value);
    void positionChanged(int value);
    void videoOver();
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
private Q_SLOTS:
    void swapped();
    void on_mpv_events();
    void maybeUpdate();
private:
    void handle_mpv_event(mpv_event *event);
    static void on_update(void *ctx);

    mpv::qt::Handle mpv;
    mpv_opengl_cb_context *mpv_gl;
};



#endif // PLAYERWINDOW_H
