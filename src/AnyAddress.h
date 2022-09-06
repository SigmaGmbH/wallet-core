// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Data.h"
#include "PublicKey.h"

#include <TrustWalletCore/TWCoinType.h>
#include <TrustWalletCore/TWPublicKey.h>
#include <TrustWalletCore/TWData.h>
#include <string>

namespace TW {

class AnyAddress {
public:
    std::string address;

    enum TWCoinType coin;

    AnyAddress(std::string address, enum TWCoinType coin);

    Data getData() const;
};

AnyAddress* createAddress(const std::string& address, enum TWCoinType coin);
AnyAddress* createAddress(const PublicKey& publicKey, enum TWCoinType coin);

inline bool operator==(const AnyAddress& lhs, const AnyAddress& rhs) {
    return lhs.address == rhs.address && lhs.coin == rhs.coin;
}

} // namespace TW

/// Wrapper for C interface.
struct TWAnyAddress {
    TW::AnyAddress* impl;
};
