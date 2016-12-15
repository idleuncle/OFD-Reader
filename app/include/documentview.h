#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H
#include <QGraphicsView>


class DocumentView : public  QGraphicsView
{
    Q_OBJECT
public:
    explicit DocumentView(QWidget *parent = 0);
};

#endif // DOCUMENTVIEW_H
