// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

import WalletCore
import XCTest

class SecretNetworkTests: XCTestCase {
    func testAddress() {
        let key = PrivateKey(data: Data(hexString: "a4b4a0dc4aa458657b7dab2ef8a5990ff9644be928c6d62acb033c8013fd14e7")!)!
        let pubkey = key.getPublicKeySecp256k1(compressed: true)
        let address = AnyAddress(publicKey: pubkey, coin: .secretNetwork)
        let addressFromString = AnyAddress(string: "secret1kc3629yhu93s8c3gv3sylzdtr4fqzmgqxexc2z", coin: .secretNetwork)!

        XCTAssertEqual(pubkey.data.hexString, "032f0c8bd1cf6cdaa754cfa85edc45105a2b0492a465f150fb25e5ab97ff8c709a")
        XCTAssertEqual(address.description, addressFromString.description)
    }

    func testSigningTransaction() {
        let privateKey = PrivateKey(data: Data(hexString: "d5be662dff3364eeb69b2bb04be43de2b7bd441871390420882d30fdea122af2")!)!
        let publicKey = privateKey.getPublicKeySecp256k1(compressed: true)
        let fromAddress = AnyAddress(publicKey: publicKey, coin: .secretNetwork)

        let sendCoinsMessage = CosmosMessage.Send.with {
            $0.fromAddress = fromAddress.description
            $0.toAddress = "secret19kp0xcmy8gfs34fczzh4e63gd3u89csptcn78l"
            $0.amounts = [CosmosAmount.with {
                $0.amount = 100000 - 200
                $0.denom = "uscrt"
            }]
        }

        let message = CosmosMessage.with {
            $0.sendCoinsMessage = sendCoinsMessage
        }

        let fee = CosmosFee.with {
            $0.gas = 200000
            $0.amounts = [CosmosAmount.with {
                $0.amount = 200
                $0.denom = "uscrt"
            }]
        }

        let input = CosmosSigningInput.with {
            $0.signingMode = .protobuf;
            $0.accountNumber = 124703
            $0.chainID = "secret-4"
            $0.memo = ""
            $0.sequence = 0
            $0.messages = [message]
            $0.fee = fee
            $0.privateKey = privateKey.data
        }

        let output: CosmosSigningOutput = AnySigner.sign(input: input, coin: .secretNetwork)

        XCTAssertEqual(output.serialized, "CpEBCo4BChwvY29zbW9zLmJhbmsudjFiZXRhMS5Nc2dTZW5kEm4KLXNlY3JldDFuY3Y0eDd3MDVrN3RzeDhlOTZhYzZ6ZHo4MGx3dmxod2V1ZGduYxItc2VjcmV0MTlrcDB4Y215OGdmczM0ZmN6emg0ZTYzZ2QzdTg5Y3NwdGNuNzhsGg4KBXVzY3J0EgU5OTgwMBJkCk4KRgofL2Nvc21vcy5jcnlwdG8uc2VjcDI1NmsxLlB1YktleRIjCiEC5ybzmDF8f/3D+nJghFSvhOMVx7wEA0rE1k4mScabRnoSBAoCCAESEgoMCgV1c2NydBIDMjAwEMCaDBpAOIbYTCecUVmuUOsBh1Cx99orfJsM3A0XQBCIzE6F1ixM8fPIycHUBGyCnoMgLGJQtCYj+yo9bokhba89IuQU/Q==")
        XCTAssertEqual(output.error, "")
    }
}
