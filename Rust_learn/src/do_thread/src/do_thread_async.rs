use threadpool::ThreadPool;
use std::sync::mpsc::channel;
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
pub async fn do_func(_i: i32) -> Result<(), reqwest::Error> {
    let res = CLIENT.get("https://www.baidu.com/hello,friend")
        .header("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36")
        .header("User-Agent", "你个大宝贝*************")
        .send()
        .await?;

    println!("Status: {}", res.status());

    let body = res.text().await?;

    // println!("Body:\n\n{}", body);
    println!("Body length in bytes: {}", body.len());          //获取字符串的长度
    // println!("Body length in characters: {}", body.chars().count());   //使用.chars().count()来获取字符数。
    Ok(())
}
// #[tokio::main]
pub fn my_thread_async() {
    // 创建一个具有20个线程的线程池
    let pool = ThreadPool::new(20);
    // 创建一个通道，tx用于发送数据，rx用于接收数据
    let (tx, rx) = channel();

    for i in 0..200 {
        // 克隆发送端，因为在闭包中我们需要一个移动的所有权
        let tx = tx.clone();
        // 在线程池中执行一个任务
        pool.execute(move|| {
            // 这里是你的任务代码
            // let result = "task finished";
            // do_func(&i);
            // 将任务的结果发送到通道中
            tx.send(do_func(i)).unwrap();
        });
    }

    // 所有任务都已经发送，我们可以放弃发送端的所有权
    drop(tx);
    // 从接收端接收数据，直到通道关闭（也就是所有任务都完成了）
    for _ in rx {
        // println!("{}", result);
    }
}