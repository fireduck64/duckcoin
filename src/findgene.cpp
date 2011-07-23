#include "headers.h"
#include "db.h"
#include "net.h"
#include "init.h"

using namespace std;

int main(int argc, char* argv[])
{
    const char* pszTimestamp = "2011-07-23 Duckcoin";
   
    CTransaction txNew;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = 50 * COIN;
    txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    CBlock block;
    block.vtx.push_back(txNew);
    block.hashPrevBlock = 0;
    block.hashMerkleRoot = block.BuildMerkleTree();
    block.nVersion = 1;
    block.nTime    = 1311443212;
    block.nBits    = 0x1d00ffff;
    block.nNonce   = 1873153963;

    CBigNum bnTarget;
    bnTarget.SetCompact(block.nBits);
    uint256 target = bnTarget.getuint256();

    unsigned int i=0;
    while(i!=0)
    {

        block.nNonce = i;

        uint256 hash =  block.GetHash();
        if (i % 1000000 == 0)
        {
            printf("nonce %u\n", i);
        }
        // Check proof of work matches claimed amount
        if (hash < target)
        {
            printf("hash %s\n", hash.ToString().c_str());
            printf("merkle root %s\n", block.hashMerkleRoot.ToString().c_str());
            printf("nonce %d\n", i);
            return 0;
        }

        i++;

    }
 
}
