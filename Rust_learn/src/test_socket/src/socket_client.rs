use std::io::{Read, Write};
use std::net::TcpStream;
use std::io;
use std::env;
fn main() {

    let args: Vec<String> = env::args().collect();
    let mut address=String::new();
    // 第一个参数是程序的名称，因此我们从第二个参数开始遍历
    for (_index, arg) in args.iter().enumerate().skip(1) {
        // println!("参数 {}: {}", index, arg);
        address=arg.to_string();
    }
    println!("{}",address);
    let mut stream = TcpStream::connect(address).unwrap();
    println!("连接已成功建立！");

    // let msg = b"whoami";
    // stream.write(msg).unwrap();
    
    // let mut buffer = [0; 1024];
    // stream.read(&mut buffer).unwrap();

    // // 打印从服务器接收到的消息
    // println!("{}", String::from_utf8_lossy(&buffer[..]));
    loop {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();

        let msg = input.trim().as_bytes();
        stream.write(msg).unwrap();

        let mut buffer = Vec::new();
        let mut temp_buffer = [0; 1024];

        loop {
            let bytes_read = stream.read(&mut temp_buffer).unwrap();
            buffer.extend_from_slice(&temp_buffer[..bytes_read]);

            if bytes_read < temp_buffer.len() {
                break;
            }
        }

        // Print the received message from the server
        println!("{}", String::from_utf8_lossy(&buffer[..]));
    }
}