// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/test/uritests.h>

#include <qt/guiutil.h>
#include <qt/walletmodel.h>

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;

    // Current AZURE URI scheme is accepted.
    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));

    // Legacy Bloodstone URI scheme remains accepted for compatibility.
    uri.setUrl(QString("bloodstone:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));

    // Older unrelated SpaceXpanse scheme is not accepted.
    uri.setUrl(QString("spacexpanse:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("azure:CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    SendCoinsRecipient formatted;
    formatted.address = QString("CJDPZBVLi6tx2mST1Z4BSANNeztHunz9LT");
    const QString formatted_uri = GUIUtil::formatBitcoinURI(formatted);
    QVERIFY(formatted_uri.startsWith(QString("azure:")));
}
