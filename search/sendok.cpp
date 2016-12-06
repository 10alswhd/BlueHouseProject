...

void Sendok::share(QString title, QString url)
{

#ifndef Q_WS_SIMULATOR
    MDataUri dataUri;
    dataUri.setMimeType("text/x-url");
    dataUri.setTextData(url);
    dataUri.setAttribute("title", title);
    dataUri.setAttribute("description", "SendokGarpu: Search for Best Restaurants and Nigthlife!");

    QStringList items;
    items << dataUri.toString();
    ShareUiInterface shareIf("com.nokia.ShareUi");
    if (shareIf.isValid()) {
        shareIf.share(items);
    } else {
        qCritical() << "Invalid interface";
    }
#endif
}

...
