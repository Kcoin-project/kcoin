// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KCOIN_MINER_H
#define KCOIN_MINER_H

#include "primitives/block.h"

#include <stdint.h>

class CBlockIndex;
class CChainParams;
class CReserveKey;
class CScript;
class CWallet;
namespace Consensus { struct Params; };

struct CBlockTemplate
{
    CBlock block;
    std::vector<CAmount> vTxFees;
    std::vector<int64_t> vTxSigOps;
};

/** Run the miner threads */
void GenerateKcoins(bool fGenerate, int nThreads, const CChainParams& chainparams);
/** Generate a new block, without valid proof-of-work */
CBlockTemplate* CreateNewBlock(const CScript& scriptPubKeyIn);
/** Modify the extranonce in a block */
void IncrementExtraNonce(CBlock* pblock, const CBlockIndex* pindexPrev, unsigned int& nExtraNonce);
void UpdateTime(CBlockHeader* pblock, const Consensus::Params& consensusParams, const CBlockIndex* pindexPrev);
bool ProcessBlockFound(CBlock* pblock, const CChainParams& chainParams);

#endif // KCOIN_MINER_H
