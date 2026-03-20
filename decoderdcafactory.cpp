#include "decoderdcafactory.h"
#include "dcahelper.h"
#include "decoder_dca.h"

#include <QMessageBox>

bool DecoderDCAFactory::canDecode(QIODevice *input) const
{
    const QFile * const file = qobject_cast<QFile*>(input);
    if(!file)
    {
        return false;
    }

    DCAHelper helper(file->fileName());
    return helper.initialize();
}

DecoderProperties DecoderDCAFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("DTS Plugin");
    properties.shortName = "dca";
    properties.filters << "*.dts" << "*.cpt";
    properties.description = "DTS Coherent Acoustics Audio File";
    properties.protocols << "file";
    properties.noInput = true;
    properties.hasAbout = true;
    return properties;
}

Decoder *DecoderDCAFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderDCA(path);
}

TrackInfoList DecoderDCAFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
#if QMMP_VERSION_INT < 0x20400
    TrackInfo *raw(new TrackInfo(path)), *info = raw;
#else
    TrackInfo raw(path), *info = &raw;
#endif
    if(parts == TrackInfo::Parts())
    {
        return {raw};
    }

    DCAHelper helper(path);
    if(!helper.initialize())
    {
#if QMMP_VERSION_INT < 0x20400
        delete info;
#endif
        return {};
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "DTS");
        info->setDuration(helper.totalTime());
    }

    return {raw};
}

MetaDataModel* DecoderDCAFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(path);
    Q_UNUSED(readOnly);
    return nullptr;
}

#if (QMMP_VERSION_INT < 0x10700) || (0x20000 <= QMMP_VERSION_INT && QMMP_VERSION_INT < 0x20200)
void DecoderDCAFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}
#else
QDialog *DecoderDCAFactory::createSettings(QWidget *parent)
{
    Q_UNUSED(parent);
    return nullptr;
}
#endif

void DecoderDCAFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About DCA Reader Plugin"),
                       tr("Qmmp DCA Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>") + "\n" +
                       tr("Based on the source code from the DTS"));
}

QString DecoderDCAFactory::translation() const
{
    return QString();
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QtPlugin>
Q_EXPORT_PLUGIN2(dca, DecoderDCAFactory)
#endif
