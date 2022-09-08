// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

package com.trustwallet.core.app.blockchains.secretnetwork

import com.trustwallet.core.app.utils.toHex
import com.trustwallet.core.app.utils.toHexByteArray
import org.junit.Assert.assertEquals
import org.junit.Test
import wallet.core.jni.*

class TestSecretNetworkAddress {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    @Test
    fun testAddress() {
        val key = PrivateKey("a4b4a0dc4aa458657b7dab2ef8a5990ff9644be928c6d62acb033c8013fd14e7".toHexByteArray())
        val pubkey = key.getPublicKeySecp256k1(true)
        val address = AnyAddress(pubkey, CoinType.SECRETNETWORK)
        val expected = AnyAddress("secret1kc3629yhu93s8c3gv3sylzdtr4fqzmgqxexc2z", CoinType.SECRETNETWORK)

        assertEquals(pubkey.data().toHex(), "032f0c8bd1cf6cdaa754cfa85edc45105a2b0492a465f150fb25e5ab97ff8c709a")
        assertEquals(address.description(), expected.description())
    }
}
