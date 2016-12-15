#ifndef DOCUMENTCONTROLLER_H
#define DOCUMENTCONTROLLER_H

#include <QObject>

class libOfdEngine;

class DocumentController : public QObject
{
    Q_OBJECT
public:
    explicit DocumentController(QObject *parent = 0);
    enum ScaleModes { ScaleFactorMode, FitToPageMode, FitToPageWidthMode };
    enum DisplayModes { PagingMode, ScrollingMode, DoublePagingMode, DoubleScrollingMode };

    bool loadFile(const QString &filePath);
    int pageCount() const;
    qreal pageWidth() const;
    qreal pageHeight() const;

    QImage renderPage(const qreal &resolutionX, const qreal &resolutionY) const;
    QImage renderPage(const int &page, const qreal &resolutionX, const qreal &resolutionY) const;

    const QString &filePath() const { return _filePath; }

    const int &page() const { return _page; }
    const ScaleModes &scaleMode() const { return _scaleMode; }
    const DisplayModes &displayMode() const { return _displayMode; }
    const qreal &scaleFactor() const { return _scaleFactor; }



signals:
    void documentChanged(QString filePath);
    void pageChanged(int page);
public slots:
//
    void nextPage();
private:
    QString _filePath;
    int _page;
    DisplayModes _displayMode;
    qreal _scaleFactor;
    ScaleModes _scaleMode;
    libOfdEngine* m_OfdEngine;
};

#endif // DOCUMENTCONTROLLER_H
