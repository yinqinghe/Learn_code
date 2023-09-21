use std::io::{Read, Write};
use std::net::TcpStream;
use std::io;
pub fn client(ip:&str,port:&str,input_command:&mut String) {

    let address=ip.to_owned()+":"+port;
    println!("{}",address);
    let mut stream = TcpStream::connect(address).unwrap();
    println!("连接已成功建立！");
    loop {
        io::stdin().read_line(input_command).unwrap();

        let msg = input_command.trim().as_bytes();
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