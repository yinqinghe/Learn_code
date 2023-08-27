use std::env;
use std::fs::OpenOptions;
use std::io::prelude::*;
use std::path::PathBuf;

fn get_path(){
    match env::current_dir() {
        Ok(exe_path) => println!("Path of this executable is: {}", exe_path.display()),
        Err(e) => println!("Failed to get current exe path: {}", e),
    }
}

fn write_to_file(file_path:&str) -> std::io::Result<()> {
    let mut file = OpenOptions::new()
        .write(true)
        .create(true)
        .append(true)
        .open(file_path)?;

    writeln!(file, "This is a new line")?;

    Ok(())
}
fn main() {
    // get_path();
  
    let mut file_path = String::new();
    match env::current_dir() {
        Ok(exe_path) => {
            file_path = exe_path.display().to_string();
            println!("Path of this executable is: {}", exe_path.display());
        },
        Err(e) => println!("Failed to get current exe path: {}", e),
    }
    let mut path = PathBuf::from(file_path);
    path.push("result");
    path.push("my_file.txt");               //构造保存结果文件的路径

    println!("Path: {}", path.display());

    match write_to_file(&path.display().to_string()) {
        Ok(_) => println!("Successfully wrote to the file."),
        Err(e) => println!("Failed to write to the file: {}", e),
    };
}