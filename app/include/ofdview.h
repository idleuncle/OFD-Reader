#ifndef OFDVIEW_H
#define OFDVIEW_H
#include <QGraphicsView>
#include <libofdengine.h>

class OfdView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit OfdView(libOfdEngine* engine,QWidget *parent = 0);
    int tmp_x;//=0;
    int tmp_y;// =0;

    // 场景
    QGraphicsScene* m_pageScene;

    ~OfdView();

    void test_cairo();

    libOfdEngine* m_ofdEngine;

    void setofdengine(libOfdEngine* ofdEngine)
    {
        m_ofdEngine = ofdEngine;
    }



};

#endif // OFDVIEW_H
