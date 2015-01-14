#include<meshquick.h>




MeshQuick::MeshQuick(): m_renderer(0)
{

    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void MeshQuick::sync()
{
    if (!m_renderer) {
        m_renderer = new MeshRenderer();
        connect(window(), SIGNAL(beforeRendering()), m_renderer, SLOT(paint()), Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());

}

void MeshQuick::cleanup()
{
       if (m_renderer) {
        delete m_renderer;
        m_renderer = 0;
    }

}

void MeshQuick::handleWindowCanged(QQuickWindow *win)
{
        if (win) {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
//! [1]
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
//! [3]
        win->setClearBeforeRendering(false);
    }

}
