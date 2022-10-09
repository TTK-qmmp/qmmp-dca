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

QList<TrackInfo*> DecoderDCAFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);
    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    DCAHelper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "DTS Audio");
        info->setDuration(helper.totalTime());
    }
    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderDCAFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(path);
    Q_UNUSED(readOnly);
    return nullptr;
}

void DecoderDCAFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderDCAFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About DCA Reader Plugin"),
                       tr("Qmmp DCA Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderDCAFactory::translation() const
{
    return QString();
}
