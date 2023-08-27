use reqwest::header::CONTENT_TYPE;
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
pub async fn post_body() -> Result<(), reqwest::Error> {
    // let client = reqwest::Client::new();
    let to_name = "YourVariable"; // 这里替换为你的变量

    let xml = format!(r#"
        <note>
            <to>{}</to>
            <from>Jani</from>
            <heading>Reminder</heading>
            <body>Don't forget me this weekend!</body>
        </note>
    "#, to_name);

    let res = CLIENT.post("https://httpbin.org/post")
        .header(CONTENT_TYPE, "application/xml")
        .body(xml)
        .send()
        .await?;

    println!("Status: {}", res.status());

    Ok(())
}