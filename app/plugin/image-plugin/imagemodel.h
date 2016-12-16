/*

Copyright 2015 Adam Reichold

This file is part of ofdreader.

ofdreader is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

ofdreader is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ofdreader.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QCoreApplication>
#include <QImage>
#include "model.h"

namespace ofdreader
{

class ImagePlugin;

namespace Model
{
    class ImagePage : public IPage
    {
        friend class ImageDocument;

    public:
        QSizeF size() const;

        QImage render(qreal horizontalResolution, qreal verticalResolution, Rotation rotation, const QRect& boundingRect) const;

    private:
        Q_DISABLE_COPY(ImagePage)

        ImagePage(QImage image);

        QImage m_image;

    };

    class ImageDocument : public IDocument
    {
        Q_DECLARE_TR_FUNCTIONS(Model::ImageDocument)

        friend class ofdreader::ImagePlugin;

    public:
        int numberOfPages() const;

        IPage* page(int index) const;

        QStringList saveFilter() const;

        bool canSave() const;
        bool save(const QString& filePath, bool withChanges) const;

//        Properties loadProperties() const;

    private:
        Q_DISABLE_COPY(ImageDocument)

        ImageDocument(QImage image);

        QImage m_image;

    };
}

class ImagePlugin : public QObject, Plugin
{
    Q_OBJECT
    Q_INTERFACES(ofdreader::Plugin)

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)

    Q_PLUGIN_METADATA(IID "local.ofdreader.Plugin")

#endif // QT_VERSION

public:
    ImagePlugin(QObject* parent = 0);

    Model::IDocument* loadDocument(const QString& filePath) const;

private:
    Q_DISABLE_COPY(ImagePlugin)

};

} // ofdreader

#endif // IMAGEMODEL_H
