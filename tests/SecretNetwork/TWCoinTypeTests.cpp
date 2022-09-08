// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
//
// This is a GENERATED FILE, changes made here MAY BE LOST.
// Generated one-time (codegen/bin/cointests)
//

#include "../interface/TWTestUtilities.h"
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <gtest/gtest.h>


TEST(TWSecretNetworkCoinType, TWCoinType) {
    auto symbol = WRAPS(TWCoinTypeConfigurationGetSymbol(TWCoinTypeSecretNetwork));
    auto txId = WRAPS(TWStringCreateWithUTF8Bytes("DBF3D6DEDE5C02D73E9B4671691D7DD2455E2630E515ED64410222C294129BFF"));
    auto txUrl = WRAPS(TWCoinTypeConfigurationGetTransactionURL(TWCoinTypeSecretNetwork, txId.get()));
    auto accId = WRAPS(TWStringCreateWithUTF8Bytes("secret16v9ezaxwu676vvf2j8zr3zkznaxflezrqklwud"));
    auto accUrl = WRAPS(TWCoinTypeConfigurationGetAccountURL(TWCoinTypeSecretNetwork, accId.get()));
    auto id = WRAPS(TWCoinTypeConfigurationGetID(TWCoinTypeSecretNetwork));
    auto name = WRAPS(TWCoinTypeConfigurationGetName(TWCoinTypeSecretNetwork));

    ASSERT_EQ(TWCoinTypeConfigurationGetDecimals(TWCoinTypeSecretNetwork), 6);
    ASSERT_EQ(TWBlockchainCosmos, TWCoinTypeBlockchain(TWCoinTypeSecretNetwork));
    ASSERT_EQ(0x0, TWCoinTypeP2shPrefix(TWCoinTypeSecretNetwork));
    ASSERT_EQ(0x0, TWCoinTypeStaticPrefix(TWCoinTypeSecretNetwork));
    assertStringsEqual(symbol, "SCRT");
    assertStringsEqual(txUrl, "https://secretnodes.com/secret/chains/secret-4/transactions/DBF3D6DEDE5C02D73E9B4671691D7DD2455E2630E515ED64410222C294129BFF");
    assertStringsEqual(accUrl, "https://secretnodes.com/secret/chains/secret-4/accounts/secret16v9ezaxwu676vvf2j8zr3zkznaxflezrqklwud");
    assertStringsEqual(id, "secretnetwork");
    assertStringsEqual(name, "Secret Network");
}
