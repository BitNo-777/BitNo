// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2022 The BitNo developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, const char* pszTimestamp)
{
    uint32_t nBits = 0x1e0ffff0;
    int32_t nVersion = 1;
    const CAmount& genesisReward = 0.00000050 * COIN;
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256S("000006a6a033adca8f3beaaedcae5f47c0f83b581c3dea6ec1d55521ebb5e01a"))/*
	(1000, uint256S("0x0000006b43065fdf445f07adca57fe5fd888902cb79c16fa48302cf1c0ab88ce"))
	(10000, uint256S("0xa2fd284213d913463d827c166ed0220b30de857794956b9dfbaaa5395891ef32"))
	(20000, uint256S("0x85acbdc4e8b609ddb3584c15f94248cc08d85c337736c12422f3e84a5bc51c4a"))*/;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1611351525, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256S("0x001"))
 ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1610066000,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1610068000,
    0,
    100};


class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1662663000, 1890419, "QUEEN ELIZABETH DEAD AT 96");
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256("000005a6e8de5b1f1b01256029e386027d1ec7c3d9657f8dc9afbf1e9b9fc552"));
        assert(genesis.hashMerkleRoot == uint256("b2358243415f26c4e1c3972324d5d4a008d87d18b3c06a810ab1d4b8ff9fdd1a"));
 
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // bitno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 90;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 21000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "BITNOdisabledXXXXXXXXXXXXXXXXXXXXXX";
				
        // spork key
        consensus.strSporkPubKey = "04eccfe86649b3f5445662738f19f04961d7c23203703285cc26ca3cc524518090ecee2574977191f14c4170444b0fe2389fb7538fabb8478d832e40727c8603f9";

        // height-based activations
        consensus.height_last_PoW = 1000;
        consensus.height_start_BIP65 = 1003;
        consensus.height_start_MessSignaturesV2 = 1030;  // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 1;
        consensus.height_start_StakeModifierV2 = 1001;
        consensus.height_start_TimeProtoV2 = 1030;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb3;
        pchMessageStart[1] = 0xa1;
        pchMessageStart[2] = 0x2c;
        pchMessageStart[3] = 0x1f;
        nDefaultPort = 53330;

        vSeeds.push_back(CDNSSeedData("193.149.129.80", "193.149.129.80"));
        vSeeds.push_back(CDNSSeedData("193.149.180.54", "193.149.180.54"));
        vSeeds.push_back(CDNSSeedData("45.61.136.151", "45.61.136.151"));
        vSeeds.push_back(CDNSSeedData("168.100.9.55", "168.100.9.55"));
        vSeeds.push_back(CDNSSeedData("162.33.177.119", "162.33.177.119"));

        // Note that of those with the service bits flag, most only support a subset of possible options

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);		// BITNO addresses start with 'B'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 30);		// BITNO script addresses start with 'D'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 28);	// BITNO private keys start with 'C'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        // BITNO BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // BITNO BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
/*
//! Modify the TESTNET genesis block so the timestamp is valid for a later start.
*/
        genesis = CreateGenesisBlock(1610066000, 0, "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
        consensus.hashGenesisBlock = genesis.GetHash();
	//assert(consensus.hashGenesisBlock == uint256S("0x001"));
        //assert(genesis.hashMerkleRoot == uint256S("0x001"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 14;   // bitno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 60;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 99000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "RSGQZGPGzxMNQkNB5KPPbEDuEPaJytMY6q";

        // spork key
        consensus.strSporkPubKey = "0467f57258fe0ca208206e9dfbb4ecdb9b2ba9ea1f049ec76932c7df1eaccb3f465de8205a4782d560a4d3a7f2a270402367c26978115615f8c88feff4b4711f20";

        // height based activations
        consensus.height_last_PoW = 1000;
        consensus.height_start_BIP65 = 851019;                  // Block v5: d1ec8838ba8f644e78dd4f8e861d31e75457dfe607b31deade30e806b5f46c1c
        consensus.height_start_MessSignaturesV2 = 1347000;      // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 51197;
        consensus.height_start_StakeModifierV2 = 1214000;       // Block v6: 1822577176173752aea33d1f60607cefe9e0b1c54ebaa77eb40201a385506199
        consensus.height_start_TimeProtoV2 = 1347000;           // Block v7: 30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        
        pchMessageStart[0] = 0xf3;
        pchMessageStart[1] = 0x24;
        pchMessageStart[2] = 0x9a;
        pchMessageStart[3] = 0x5f;
        nDefaultPort = 8452;

        vFixedSeeds.clear();
        vSeeds.clear();
        
        // nodes with support for servicebits filtering should be at the top

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 75); // BITNO addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 4); // BITNO script addresses start with '3'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 80); // BITNO private keys start with 'Z'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        // BITNO BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
	base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
	// BITNO BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
	base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
	// BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
	base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
/*
//! Modify the REGTEST genesis block so the timestamp is valid for a later start.
*/
        genesis = CreateGenesisBlock(1610066000, 0, "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
        consensus.hashGenesisBlock = genesis.GetHash();
	//assert(consensus.hashGenesisBlock == uint256S("0x001"));
        //assert(genesis.hashMerkleRoot == uint256S("0x001"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 14;   // bitno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 30;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 99000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "RSGQZGPGzxMNQkNB5KPPbEDuEPaJytMY6q";

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "046f781df141e6ab82ca37ddb745803e2d4744137dcfdccd4e8f1e308e2001738e450e35a92828e85b99e18d88f4b78f7fe4eaf1072d91a06b82e44f02a4e425b2";

        // height based activations
        consensus.height_last_PoW = 350;
        consensus.height_start_BIP65 = 851019;              // Not defined for regtest. Inherit TestNet value.
        consensus.height_start_MessSignaturesV2 = 1;
        consensus.height_start_StakeModifierNewSelection = 0;
        consensus.height_start_StakeModifierV2 = 251;       // start with modifier V2 on regtest
        consensus.height_start_TimeProtoV2 = 999999999;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xcb;
        pchMessageStart[2] = 0x7c;
        pchMessageStart[3] = 0xad;
        nDefaultPort = 8552;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
