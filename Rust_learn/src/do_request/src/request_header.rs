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
pub async fn mainss() -> Result<(), reqwest::Error> {
    // let client = reqwest::Client::builder()
    // .timeout(Duration::from_secs(8)) // 设置响应时间为8秒
    // .proxy(Proxy::all("http://127.0.0.1:8080")?) // 设置代理
    // .danger_accept_invalid_certs(true) // 设置忽略TLS证书验证
    // .build()?;

    let res = CLIENT.get("https://www.baidu.com/hello,friend")
        .header("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36")
        .header("User-Agent", "你个大宝贝*************")
        .send()
        .await?;

    println!("Status: {}", res.status());

    let body = res.text().await?;

    // println!("Body:\n\n{}", body);
    println!("Body length in bytes: {}", body.len());          //获取字符串的长度
    println!("Body length in characters: {}", body.chars().count());   //使用.chars().count()来获取字符数。


    Ok(())
}