// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Cosmos/Address.h"
#include "HexCoding.h"
#include "PublicKey.h"
#include "PrivateKey.h"
#include <gtest/gtest.h>
#include <vector>

using namespace TW;
using namespace TW::Cosmos;

TEST(SecretNetworkAddress, Valid) {
    EXPECT_TRUE(Address::isValid(TWCoinTypeSecretNetwork, "secret19y0n2ru9dae9w6vt7fwgfptp5nxq3hwtsz4u75"));
    EXPECT_TRUE(Address::isValid(TWCoinTypeSecretNetwork, "secret1k0jntykt7e4g3y88ltc60czgjuqdy4c9e8fzek"));
}

TEST(SecretNetworkAddress, Invalid) {
    EXPECT_FALSE(Address::isValid(TWCoinTypeSecretNetwork, "secret16s4tmczllc5zj6hxnjhdackmhe8wu4es6a7wrn"));
    EXPECT_FALSE(Address::isValid(TWCoinTypeSecretNetwork, "cosmos1hsk6jryyqjfhp5dhc55tc9jtckygx0eph6dd02")); // valid cosmos
}

TEST(SecretNetworkAddress, FromPrivateKey) {
    auto privateKey = PrivateKey(parse_hex("a4b4a0dc4aa458657b7dab2ef8a5990ff9644be928c6d62acb033c8013fd14e7"));
    auto publicKey = privateKey.getPublicKey(TWPublicKeyTypeSECP256k1);
    auto address = Address(TWCoinTypeSecretNetwork, publicKey);
    ASSERT_EQ(address.string(), "secret1kc3629yhu93s8c3gv3sylzdtr4fqzmgqxexc2z");
}

TEST(SecretNetworkAddress, FromPublicKey) {
    auto publicKey = PublicKey(parse_hex("032f0c8bd1cf6cdaa754cfa85edc45105a2b0492a465f150fb25e5ab97ff8c709a"), TWPublicKeyTypeSECP256k1);
    auto address = Address(TWCoinTypeSecretNetwork, publicKey);
    ASSERT_EQ(address.string(), "secret1kc3629yhu93s8c3gv3sylzdtr4fqzmgqxexc2z");
}

TEST(SecretNetworkAddress, FromString) {
    Address address;
    EXPECT_TRUE(Address::decode("secret1kc3629yhu93s8c3gv3sylzdtr4fqzmgqxexc2z", address));
    EXPECT_EQ(address.string(), "secret1kc3629yhu93s8c3gv3sylzdtr4fqzmgqxexc2z");
    EXPECT_EQ(hex(address.getKeyHash()), "b623a51497e16303e22864604f89ab1d52016d00");
}
