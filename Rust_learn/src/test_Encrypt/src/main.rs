extern crate aes;
extern crate block_modes;
extern crate block_padding;
extern crate rand;
extern crate generic_array;

use aes::Aes128;
use block_modes::{BlockMode, Cbc};
use block_modes::block_padding::Pkcs7;
use rand::Rng;
use generic_array::GenericArray;

type Aes128Cbc = Cbc<Aes128, Pkcs7>;

fn aes_encrypt_decrypt(mode: &str, input_data: &[u8], key: &GenericArray<u8, <Aes128 as block_modes::BlockCipher>::KeySize>, iv: &GenericArray<u8, <Aes128 as block_modes::BlockCipher>::BlockSize>) -> Vec<u8> {
    if mode == "encrypt" {
        let cipher = Aes128Cbc::new(key, iv);
        let cipher_text = cipher.encrypt_vec(input_data);
        return cipher_text;
    } else if mode == "decrypt" {
        let cipher = Aes128Cbc::new(key, iv);
        let plain_text = cipher.decrypt_vec(input_data).unwrap();
        return plain_text;
    }
    vec![]
}

fn main() {
    // 生成一个随机的AES密钥
    let key: [u8; 16] = rand::thread_rng().gen();
    let iv: [u8; 16] = rand::thread_rng().gen();

    let key = GenericArray::from_slice(&key);
    let iv = GenericArray::from_slice(&iv);

    // 加密
    let data = b"This is a test.";
    let encrypted = aes_encrypt_decrypt("encrypt", data, &key, &iv);
    println!("Encrypted: {:?}", encrypted);

    // 解密
    let decrypted = aes_encrypt_decrypt("decrypt", &encrypted, &key, &iv);
    println!("Decrypted: {:?}", String::from_utf8(decrypted).unwrap());
}