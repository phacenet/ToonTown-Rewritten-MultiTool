#include <QWebEngineUrlRequestInterceptor>
#include <QSet>
#include <QString>

class AdBlocker : public QWebEngineUrlRequestInterceptor
{
public:
    explicit AdBlocker(QObject* parent = nullptr) : QWebEngineUrlRequestInterceptor(parent)
    {
        m_blocked = {
        // google ads
        "googlesyndication.com",
        "googleadservices.com",
        "google-analytics.com",
        "adservice.google.com",
        "imasdk.googleapis.com",
        "ade.googlesyndication.com",
        // facebook tracking
        "facebook.com/tr",
        "connect.facebook.net",
        "scontent.xx.fbcdn.net",
        // toonhq-specific ad providers
        "btloader.com",
        "media.net",
        "trustedstack.com",
        "p7cloud.net",
        "ddmp97xkodp2z.cloudfront.net",
        "a1645.d.akamai.net",
        // general ad networks
        "doubleclick.net",
        "amazon-adsystem.com",
        "adnxs.com",
        "adsrvr.org",
        "rubiconproject.com",
        "pubmatic.com",
        "casalemedia.com",
        "moatads.com",
        "outbrain.com",
        "taboola.com",
        "criteo.com",
        "scorecardresearch.com"
        };
    }

    void interceptRequest(QWebEngineUrlRequestInfo &info) override
    {
        QString host = info.requestUrl().host();
        for(const auto& blocked : m_blocked)
        {
            if(host.contains(blocked))
            {
                info.block(true);
                return;
            }
        }
    }

private:
    QSet<QString> m_blocked;
};
