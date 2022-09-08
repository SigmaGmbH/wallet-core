// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

package com.trustwallet.core.app.blockchains.secretnetwork

import android.util.Log
import com.google.protobuf.ByteString
import com.trustwallet.core.app.utils.Numeric
import com.trustwallet.core.app.utils.toHexByteArray
import com.trustwallet.core.app.utils.toHexBytes
import com.trustwallet.core.app.utils.toHexBytesInByteString
import com.trustwallet.core.app.utils.toHex
import org.junit.Assert.assertEquals
import org.junit.Test
import wallet.core.jni.*
import wallet.core.jni.CoinType.SECRETNETWORK
import wallet.core.jni.proto.Cosmos
import wallet.core.jni.proto.Cosmos.SigningOutput
import wallet.core.jni.proto.Cosmos.SigningMode
import wallet.core.java.AnySigner

class TestOsmosisSigner {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    @Test
    fun OsmosisTransactionSigning() {
        val key = PrivateKey("d5be662dff3364eeb69b2bb04be43de2b7bd441871390420882d30fdea122af2".toHexByteArray())
        val publicKey = key.getPublicKeySecp256k1(true)
        val from = AnyAddress(publicKey, SECRETNETWORK).description()

        val txAmount = Cosmos.Amount.newBuilder().apply {
            amount = 100000 - 200
            denom = "uscrt"
        }.build()

        val sendCoinsMsg = Cosmos.Message.Send.newBuilder().apply {
            fromAddress = from
            toAddress = "secret19kp0xcmy8gfs34fczzh4e63gd3u89csptcn78l"
            addAllAmounts(listOf(txAmount))
        }.build()

        val message = Cosmos.Message.newBuilder().apply {
            sendCoinsMessage = sendCoinsMsg
        }.build()

        val feeAmount = Cosmos.Amount.newBuilder().apply {
            amount = 200
            denom = "uscrt"
        }.build()

        val osmosisFee = Cosmos.Fee.newBuilder().apply {
            gas = 200000
            addAllAmounts(listOf(feeAmount))
        }.build()

        val signingInput = Cosmos.SigningInput.newBuilder().apply {
            signingMode = SigningMode.Protobuf
            accountNumber = 124703
            chainId = "secret-4"
            memo = ""
            sequence = 0
            fee = osmosisFee
            privateKey = ByteString.copyFrom(key.data())
            addAllMessages(listOf(message))
        }.build()

        val output = AnySigner.sign(signingInput, SECRETNETWORK, SigningOutput.parser())

        assertEquals(output.serialized, "CpEBCo4BChwvY29zbW9zLmJhbmsudjFiZXRhMS5Nc2dTZW5kEm4KLXNlY3JldDFuY3Y0eDd3MDVrN3RzeDhlOTZhYzZ6ZHo4MGx3dmxod2V1ZGduYxItc2VjcmV0MTlrcDB4Y215OGdmczM0ZmN6emg0ZTYzZ2QzdTg5Y3NwdGNuNzhsGg4KBXVzY3J0EgU5OTgwMBJkCk4KRgofL2Nvc21vcy5jcnlwdG8uc2VjcDI1NmsxLlB1YktleRIjCiEC5ybzmDF8f/3D+nJghFSvhOMVx7wEA0rE1k4mScabRnoSBAoCCAESEgoMCgV1c2NydBIDMjAwEMCaDBpAOIbYTCecUVmuUOsBh1Cx99orfJsM3A0XQBCIzE6F1ixM8fPIycHUBGyCnoMgLGJQtCYj+yo9bokhba89IuQU/Q==")
        assertEquals(output.error, "")
    }
}
