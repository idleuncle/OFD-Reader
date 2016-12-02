#ifndef OFDVIEW_H
#define OFDVIEW_H
#include <QGraphicsView>

class OfdView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit OfdView(QWidget *parent = 0);

    // 场景
    QGraphicsScene* m_pageScene;

    ~OfdView();

    void test_cairo();

};

#endif // OFDVIEW_H
