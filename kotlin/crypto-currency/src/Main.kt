import kcoin.Block
import kcoin.BlockChain

fun main() {
    var blockChain = BlockChain()

    val genesisBlock: Block = Block("0", "I'm the first")
    blockChain.add(genesisBlock)

    println(genesisBlock)

}