package kcoin

import java.math.BigInteger
import java.security.Key
import java.security.MessageDigest
import java.security.PrivateKey
import java.security.PublicKey
import java.security.Signature
import java.time.Instant
import java.util.Base64

fun String.hash(algorithm: String = "SHA-256"): String {
    val messageDigest = MessageDigest.getInstance(algorithm)
    messageDigest.update(this.toByteArray())
    return String.format("%064x", BigInteger(1, messageDigest.digest()))
}

fun String.sign(privateKey: PrivateKey, algorithm: String = "SHA256withRSA"): ByteArray {
    val rsa = Signature.getInstance(algorithm)
    rsa.initSign(privateKey)
    rsa.update(this.toByteArray())
    return rsa.sign()
}

fun String.verifySignature(publicKey: PublicKey, signature: ByteArray, algorithm: String = "SHA256withRSA") : Boolean {
    val rsa = Signature.getInstance(algorithm)
    rsa.initVerify(publicKey)
    rsa.update(this.toByteArray())
    return rsa.verify(signature)
}

fun Key.encodeToString() : String {
    return Base64.getEncoder().encodeToString(this.encoded)
}

class BlockChain() {
    private var blocks: MutableList<Block> = ArrayList()

    fun add(block: Block) : Block {
        val minedBlock = if (isMined(block)) block else mine(block)
        blocks.add(minedBlock)
        return minedBlock
    }

    private val difficulty = 5
    private val validPrefix = "0".repeat(difficulty)

    private fun isMined(block: Block) : Boolean {
        return block.hash.startsWith(validPrefix)
    }

    private fun mine(block: Block) : Block {

        println("Mining: $block")

        var minedBlock = block.copy()
        while (!isMined(minedBlock)) {
            minedBlock = minedBlock.copy(nonce = minedBlock.nonce + 1)
        }

        println("Mined : $minedBlock")

        return minedBlock
    }

    fun isValid(): Boolean {
        when {
            blocks.isEmpty() -> return true
            blocks.size == 1 -> return blocks[0].hash == blocks[0].calculateHash() && isMined(blocks[0])
            else -> {
                for (i in 1 until blocks.size) {
                    val lastBlock = blocks[i - 1]
                    val currentBlock = blocks[i]

                    when {
                        !(isMined(currentBlock) && isMined(lastBlock)) -> return false
                        currentBlock.hash == currentBlock.calculateHash() -> return false
                        currentBlock.previousHash != lastBlock.calculateHash() -> return false
                    }
                }
            }
        }
        return true
    }
}

data class Block(val previousHash: String,
                 val data: String,
                 val timestamp: Long = Instant.now().toEpochMilli(),
                 var nonce: Long = 0,
                 var hash: String = "") {

    init {
        hash = calculateHash()
    }

    fun calculateHash(): String {
        return "$previousHash$data$timestamp$nonce".hash()
    }

}