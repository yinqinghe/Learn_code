package main

import (
	"bytes"
	"crypto/cipher"
	"crypto/des"
	"fmt"
)

func main() {
	// 3DES加密密钥，长度必须为24字节
	key := []byte("0123456789abcdef01234567")

	// 待加密的数据
	plaintext := []byte("Hello, world!")

	// 创建3DES加密算法实例
	block, err := des.NewTripleDESCipher(key)
	if err != nil {
		panic(err)
	}

	// 补全明文数据
	plaintext = pkcs5Padding(plaintext, block.BlockSize())

	// 创建CBC分组模式实例
	iv := []byte("12345678")
	mode := cipher.NewCBCEncrypter(block, iv)

	// 加密数据
	ciphertext := make([]byte, len(plaintext))
	mode.CryptBlocks(ciphertext, plaintext)

	fmt.Printf("加密后的数据：%x\n", ciphertext)

	// 创建CBC分组模式实例
	mode = cipher.NewCBCDecrypter(block, iv)

	// 解密数据
	plaintext = make([]byte, len(ciphertext))
	mode.CryptBlocks(plaintext, ciphertext)

	// 去除填充数据
	plaintext = pkcs5UnPadding(plaintext)

	fmt.Printf("解密后的数据：%s\n", plaintext)
}

// PKCS5填充算法
func pkcs5Padding(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}

// PKCS5去除填充算法
func pkcs5UnPadding(data []byte) []byte {
	length := len(data)
	unpadding := int(data[length-1])
	return data[:(length - unpadding)]
}
