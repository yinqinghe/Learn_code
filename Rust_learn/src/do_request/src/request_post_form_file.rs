use reqwest::multipart::{Form, Part};
use std::path::Path;
use tokio::fs::File;
use tokio::io::AsyncReadExt; // 添加这行
use std::time::Duration;
use reqwest::Proxy;

use once_cell::sync::Lazy;

static CLIENT: Lazy<reqwest::Client> = Lazy::new(|| {
    reqwest::Client::builder()
        .timeout(Duration::from_secs(8)) // 设置响应时间为8秒
        .proxy(Proxy::all("http://127.0.0.1:8080").unwrap())// 设置代理
        .danger_accept_invalid_certs(true) // 设置忽略TLS证书验证
        .build()
        .unwrap()
});

#[tokio::main]
pub async fn post_form_file() -> Result<(), Box<dyn std::error::Error>> {

    let path = Path::new(r"D:\Pics\1.jpg");
    let mut file = File::open(&path).await?;
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).await?;       //读取文件内容

    let part = Part::bytes(buffer)          //   设置表单文件上传
        .file_name(path.file_name().unwrap().to_str().unwrap().to_string())
        .mime_str("image/jpeg")?;


    let form = Form::new()     //构造请求表单
        .text("key1", "value1")
        .text("key2", "value2")
        .part("file", part);

    let res = CLIENT.post("https://www.baidu.com")
        .multipart(form)
        .send()
        .await?;

    println!("Response: {:?}", res.text().await?);

    Ok(())
}