// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Transaction.h"
#include "Address.h"
#include "../proto/FIO.pb.h"

#include "Data.h"
#include "../PrivateKey.h"

#include <string>
#include <vector>

namespace TW::FIO {

/// Represents current parameters of the FIO blockchain
/// @chanId: Constant chainId (32 bytes), obtained from get_info API
/// @headBlockNumber: The last block number, obtained from get_info API
/// @refBlockPrefix: Block prefix of last block, obtained from get_block API
class ChainParams {
public:
    Data chainId;
    uint64_t headBlockNumber;
    uint64_t refBlockPrefix;
};

class TransactionBuilder {
public:
    static constexpr auto ContractAddress = "fio.address";
    static constexpr auto ContractToken = "fio.token";
    static constexpr auto ContractPayRequest = "fio.reqobt";
    static constexpr auto AuthrizationActive = "active";
    static const auto ExpirySeconds = 3600;

    /// Generic transaction signer: Build a signed transaction, in Json, from the specific SigningInput messages.
    static std::string sign(Proto::SigningInput in);

    /// Create a signed RegisterFioAddress transaction, returned as json string (double quote delimited), suitable for register_fio_address RPC call
    /// @address The owners' FIO address. Ex.: "FIO6m1fMdTpRkRBnedvYshXCxLFiC5suRU8KDfx8xxtXp2hntxpnf"
    /// @privateKey The private key matching the address, needed for signing.
    /// @fioName The FIO name to be registered. Ex.: "mario@trust"
    /// @chainParams Current parameters from the FIO chain, must be obtained recently using get_info and get_block calls.
    /// @fee Max fee to spend, can be obtained using get_fee API.
    /// @walletTpId The FIO name of the originating wallet (project-wide constant)
    /// @expiryTime Expiry for this message, can be 0, then it is taken from current time with default expiry
    static std::string createRegisterFioAddress(const Address& address, const PrivateKey& privateKey, 
        const std::string& fioName,
        const ChainParams& chainParams, uint64_t fee, const std::string& walletTpId, uint32_t expiryTime);

    /// Create a signed AddAddress transaction, returned as json string (double quote delimited), suitable for add_pub_address RPC call
    /// @address The owners' FIO address
    /// @privateKey The private key matching the address, needed for signing.
    /// @fioName The FIO name already registered to the owner. Ex.: "dmitry@trust"
    /// @addressess List of public addresses to be registered, ex. {{"BTC", "bc1qv...7v"},{"BNB", "bnb1ts3...9s"}}
    /// @chainParams Current parameters from the FIO chain, must be obtained recently using get_info and get_block calls.
    /// @fee Max fee to spend, can be obtained using get_fee API.
    /// @walletTpId The FIO name of the originating wallet (project-wide constant)
    /// @expiryTime Expiry for this message, can be 0, then it is taken from current time with default expiry
    /// Note: fee is usually 0 for add_pub_address.
    static std::string createAddPubAddress(const Address& address, const PrivateKey& privateKey, const std::string& fioName,
        const std::vector<std::pair<std::string, std::string>>& pubAddresses,
        const ChainParams& chainParams, uint64_t fee, const std::string& walletTpId, uint32_t expiryTime);

    /// Create a signed TransferTokens transaction, returned as json string (double quote delimited), suitable for transfer_tokens_pub_key RPC call
    /// @address The owners' FIO address
    /// @privateKey The private key matching the address, needed for signing.
    /// @payeePublicKey FIO address of the payee. Ex.: "FIO6m1fMdTpRkRBnedvYshXCxLFiC5suRU8KDfx8xxtXp2hntxpnf"
    /// @amount Amount of FIO coins to be transferred.
    /// @chainParams Current parameters from the FIO chain, must be obtained recently using get_info and get_block calls.
    /// @fee Max fee to spend, can be obtained using get_fee API.
    /// @walletTpId The FIO name of the originating wallet (project-wide constant)
    /// @expiryTime Expiry for this message, can be 0, then it is taken from current time with default expiry
    static std::string createTransfer(const Address& address, const PrivateKey& privateKey, 
        const std::string& payeePublicKey, uint64_t amount,
        const ChainParams& chainParams, uint64_t fee, const std::string& walletTpId, uint32_t expiryTime);

    /// Create a signed RenewFioAddress transaction, returned as json string (double quote delimited), suitable for register_fio_address RPC call
    /// @address The owners' FIO address. Ex.: "FIO6m1fMdTpRkRBnedvYshXCxLFiC5suRU8KDfx8xxtXp2hntxpnf"
    /// @privateKey The private key matching the address, needed for signing.
    /// @fioName The FIO name to be renewed. Ex.: "alice@trust"
    /// @chainParams Current parameters from the FIO chain, must be obtained recently using get_info and get_block calls.
    /// @fee Max fee to spend, can be obtained using get_fee API.
    /// @walletTpId The FIO name of the originating wallet (project-wide constant)
    /// @expiryTime Expiry for this message, can be 0, then it is taken from current time with default expiry
    static std::string createRenewFioAddress(const Address& address, const PrivateKey& privateKey, 
        const std::string& fioName,
        const ChainParams& chainParams, uint64_t fee, const std::string& walletTpId, uint32_t expiryTime);

    /// Create a signed NewFundsRequest transaction, returned as json string (double quote delimited), suitable for new_funds_request RPC call
    /// @address The owners' FIO address. Ex.: "FIO6m1fMdTpRkRBnedvYshXCxLFiC5suRU8KDfx8xxtXp2hntxpnf"
    /// @privateKey The private key matching the address, needed for signing.
    /// @payerFioName The FIO name of the requested payer. Ex.: "alice@trust"
    /// @payerFioAddress The FIO address (not name) of the payer, owner of payerFioName.
    /// @payeeFioName Own FIO name.  Ex.: "bob@trust"
    /// @payeePublicAddress Public addressed of the payee, on the mentioned blockchain.
    /// @amount Amount requested (as string)
    /// @coinSymbol Token code of the amount requested
    /// @memo Memo free text.  Optional, may be empty.
    /// @hash Hash.  Optional, may be empty.
    /// @offlineUrl Attached offline URL.  Optional, may be empty.
    /// @chainParams Current parameters from the FIO chain, must be obtained recently using get_info and get_block calls.
    /// @fee Max fee to spend, can be obtained using get_fee API.
    /// @walletTpId The FIO name of the originating wallet (project-wide constant)
    /// @expiryTime Expiry for this message, can be 0, then it is taken from current time with default expiry
    /// @iv Optional initial values for encryption, should be empty.  Can be set for testability (16 bytes).
    /// Note: as of FIO testnet v0.9.0, this transaction is not accepted; see https://github.com/SigmaGmbH/wallet-core/issues/850
    static std::string createNewFundsRequest(const Address& address, const PrivateKey& privateKey,
        const std::string& payerFioName, const std::string& payerFioAddress, const std::string& payeeFioName, const std::string& payeePublicAddress,
        const std::string& amount, const std::string& coinSymbol, const std::string& memo, const std::string& hash, const std::string& offlineUrl,
        const ChainParams& chainParams, uint64_t fee, const std::string& walletTpId, uint32_t expiryTime,
        const Data& iv);

    /// Used internally.  Creates signatures and json with transaction.
    static std::string signAdnBuildTx(const Data& chainId, const Data& packedTx, const PrivateKey& privateKey);

    /// Used internally.  If expiry is 0, fill it based on current time.  Return true if value has been changed.
    static bool expirySetDefaultIfNeeded(uint32_t& expiryTime);
};

} // namespace TW::FIO
