#ifndef MESHQUICK
#define MESHQUICK

#include <QtQuick/QQuickItem>



class MeshQuick : public QQuickItem {

public:
    MeshQuick();
    ~MeshQuick();




public slots:

    void sync();
    void cleanup();



private:


};



#endif // MESHQUICK

