use std::env;
use std::fs;

fn main() {
    let manifest_path = concat!(env!("CARGO_MANIFEST_DIR"), "/my_program.exe.manifest");
    let output_dir = env::var("OUT_DIR").expect("Failed to get output directory");
    let output_path = format!("{}/my_program.exe.manifest", output_dir);
    fs::copy(manifest_path, output_path).expect("Failed to copy manifest file");
}