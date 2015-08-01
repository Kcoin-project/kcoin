// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KCOIN_QT_KCOINADDRESSVALIDATOR_H
#define KCOIN_QT_KCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class KcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Kcoin address widget validator, checks for a valid kcoin address.
 */
class KcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // KCOIN_QT_KCOINADDRESSVALIDATOR_H
