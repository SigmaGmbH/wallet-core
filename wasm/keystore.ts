// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

import { CoinType, PrivateKey } from "./wallet-core";

export namespace KeyStore {
  export enum WalletType {
    Mnemonic = "mnemonic",
    PrivateKey = "privateKey",
    WatchOnly = "watchOnly",
    Hardware = "hardware",
  }

  export enum Error {
    AccountNotFound = "account not found",
    InvalidPassword = "invalid password",
    InvalidMnemonic = "invalid mnemonic",
    InvalidJSON = "invalid JSON",
    InvalidKey = "invalid key",
  }

  export interface ActiveAccount {
    address: string;
    coin: number;
    publicKey: string;
    derivationPath: string;
    extendedPublicKey?: string;
  }

  export interface Wallet {
    id: string;

    type: WalletType;
    name: string;
    version: number;
    activeAccounts: ActiveAccount[];
  }

  export interface IKeyStore {
    // Load a wallet by wallet id
    load(id: string): Promise<Wallet>;

    // Load all wallets
    loadAll(): Promise<Wallet[]>;

    // Import a wallet by mnemonic, name, password and initial active accounts (from coinTypes)
    import(
      mnemonic: string,
      name: string,
      password: string,
      coins: CoinType[]
    ): Promise<Wallet>;

    // Import a wallet by private key, name and password
    import(
      key: Uint8Array,
      name: string,
      password: string,
      coin: CoinType
    ): Promise<Wallet>;

    // Import a Wallet object directly
    import(wallet: Wallet): Promise<boolean>;

    // Add active accounts to a wallet by wallet id, password, coin
    addAccounts(
      id: string,
      password: string,
      coins: CoinType[]
    ): Promise<Wallet>;

    // Get private key of an account by wallet id, password, coin and derivation path
    getKey(
      id: string,
      password: string,
      account: ActiveAccount
    ): Promise<PrivateKey>;

    // Delete a wallet by wallet id and password.
    delete(id: string, password: string): Promise<boolean>;

    // Export a wallet by wallet id and password, returns mnemonic or private key
    export(id: string, password: string): Promise<string | Uint8Array>;

    // Delete a wallet by wallet id and password
    delete(id: string, password: string): Promise<boolean>;
  }
}