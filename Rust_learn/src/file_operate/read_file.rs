use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() -> io::Result<()> {
    let path = Path::new(r"D:\Downloads\tmp\LoginSSO.txt");
    let file = File::open(&path)?;
    let reader = io::BufReader::new(file);

    for (index, line) in reader.lines().enumerate() {
        if index > 10 && index < 100 {
            let line = line?;
            println!("index {}: {}", index, line);
        }
        let line = line?;
        println!("inde {}: {}", index, line);
    }

    Ok(())
//     在Rust中，Ok(())是Result枚举的一个变体，表示一个操作成功完成并且没有返回任何有意义的值。

// Result枚举有两个变体：Ok(T)和Err(E)。Ok(T)表示操作成功，并包含结果值T。Err(E)表示操作失败，并包含错误信息E。

// 当你看到Ok(())时，这表示一个操作成功完成，但没有返回任何有意义的值。在这种情况下，()是Rust中的单元类型，类似于其他语言中的void。

}