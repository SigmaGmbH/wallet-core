// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWAnySigner.h>
#include "HexCoding.h"
#include "Cosmos/Address.h"
#include "proto/Cosmos.pb.h"

#include "../interface/TWTestUtilities.h"
#include <gtest/gtest.h>

using namespace TW;
using namespace TW::Cosmos;

TEST(TWAnySignerSecretNetwork, Sign) {
    auto privateKey = parse_hex("d5be662dff3364eeb69b2bb04be43de2b7bd441871390420882d30fdea122af2");
    Proto::SigningInput input;
    input.set_signing_mode(Proto::Protobuf);
    input.set_account_number(124703);
    input.set_chain_id("secret-4");
    input.set_memo("");
    input.set_sequence(0);
    input.set_private_key(privateKey.data(), privateKey.size());

    Address fromAddress;
    Address toAddress;
    EXPECT_TRUE(Address::decode("secret1ncv4x7w05k7tsx8e96ac6zdz80lwvlhweudgnc", fromAddress));
    EXPECT_TRUE(Address::decode("secret19kp0xcmy8gfs34fczzh4e63gd3u89csptcn78l", toAddress));

    auto msg = input.add_messages();
    auto& message = *msg->mutable_send_coins_message();
    message.set_from_address(fromAddress.string());
    message.set_to_address(toAddress.string());
    auto amountOfTx = message.add_amounts();
    amountOfTx->set_denom("uscrt");
    amountOfTx->set_amount(100000 - 200);

    auto& fee = *input.mutable_fee();
    fee.set_gas(200000);
    auto amountOfFee = fee.add_amounts();
    amountOfFee->set_denom("uscrt");
    amountOfFee->set_amount(200);

    Proto::SigningOutput output;
    ANY_SIGN(input, TWCoinTypeSecretNetwork);

    EXPECT_EQ(output.serialized(), "CpEBCo4BChwvY29zbW9zLmJhbmsudjFiZXRhMS5Nc2dTZW5kEm4KLXNlY3JldDFuY3Y0eDd3MDVrN3RzeDhlOTZhYzZ6ZHo4MGx3dmxod2V1ZGduYxItc2VjcmV0MTlrcDB4Y215OGdmczM0ZmN6emg0ZTYzZ2QzdTg5Y3NwdGNuNzhsGg4KBXVzY3J0EgU5OTgwMBJkCk4KRgofL2Nvc21vcy5jcnlwdG8uc2VjcDI1NmsxLlB1YktleRIjCiEC5ybzmDF8f/3D+nJghFSvhOMVx7wEA0rE1k4mScabRnoSBAoCCAESEgoMCgV1c2NydBIDMjAwEMCaDBpAOIbYTCecUVmuUOsBh1Cx99orfJsM3A0XQBCIzE6F1ixM8fPIycHUBGyCnoMgLGJQtCYj+yo9bokhba89IuQU/Q==");
    EXPECT_EQ(hex(output.signature()), "3886d84c279c5159ae50eb018750b1f7da2b7c9b0cdc0d17401088cc4e85d62c4cf1f3c8c9c1d4046c829e83202c6250b42623fb2a3d6e89216daf3d22e414fd");
    EXPECT_EQ(output.json(), "");
    EXPECT_EQ(output.error(), "");
}
