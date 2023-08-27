use std::collections::HashMap;
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
pub async fn post_form() -> Result<(), Box<dyn std::error::Error>> {

    let mut params = HashMap::new();
    params.insert("key1", "value1");
    params.insert("key2", "value2");

    let res = CLIENT.post("https://www.baidu.com")
        .header("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36")
        .form(&params)
        .send()
        .await?;

    println!("Response: {:?}", res.text().await?);

    Ok(())
}