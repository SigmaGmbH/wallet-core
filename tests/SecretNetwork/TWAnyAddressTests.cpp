// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWAnyAddress.h>
#include "HexCoding.h"

#include "../interface/TWTestUtilities.h"
#include <gtest/gtest.h>

using namespace TW;

TEST(TWSecretNetworkAnyAddress, IsValid) {
    EXPECT_TRUE(TWAnyAddressIsValid(STRING("secret13remta5qhldf5ust9dsx4ylj7ac0ezuk7l0nyl").get(), TWCoinTypeSecretNetwork));
    EXPECT_TRUE(TWAnyAddressIsValid(STRING("secret1qptyunp43wzleq6etlt3f2rktenlc56g2egp3h").get(), TWCoinTypeSecretNetwork));
    EXPECT_FALSE(TWAnyAddressIsValid(STRING("cosmos1hsk6jryyqjfhp5dhc55tc9jtckygx0eph6dd02").get(), TWCoinTypeSecretNetwork));
}

TEST(TWSecretNetworkAnyAddress, Create) {
    auto string = STRING("secret1kc3629yhu93s8c3gv3sylzdtr4fqzmgqxexc2z");
    auto addr = WRAP(TWAnyAddress, TWAnyAddressCreateWithString(string.get(), TWCoinTypeSecretNetwork));
    auto string2 = WRAPS(TWAnyAddressDescription(addr.get()));
    EXPECT_TRUE(TWStringEqual(string.get(), string2.get()));
    auto keyHash = WRAPD(TWAnyAddressData(addr.get()));
    assertHexEqual(keyHash, "b623a51497e16303e22864604f89ab1d52016d00");
}
