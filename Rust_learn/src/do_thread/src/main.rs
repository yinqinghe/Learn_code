use std::time::Instant;
// use threadpool::ThreadPool;
// use std::sync::mpsc::channel;
mod do_thread_blocking;
use do_thread_blocking::my_thread;
mod do_thread_async;
use do_thread_async::my_thread_async;

// fn do_func(i: &i32)  {
//     println!("{}", i);
//     // *i
// }

fn main() {
    // 记录开始时间
    let start = Instant::now();

    my_thread();
    // my_thread_async();
    // 记录结束时间
    let end = Instant::now();

    // 计算运行时间（以秒为单位）
    let duration = end - start;
    let seconds = duration.as_secs();
    let nanoseconds = duration.subsec_nanos();
     // 打印运行时间
    println!("程序运行时间: {} 秒 {} 纳秒", seconds, nanoseconds);
}




// // 创建一个具有20个线程的线程池
// let pool = ThreadPool::new(20);
// // 创建一个通道，tx用于发送数据，rx用于接收数据
// let (tx, rx) = channel();

// for i in 0..200 {
//     // 克隆发送端，因为在闭包中我们需要一个移动的所有权
//     let tx = tx.clone();
//     // 在线程池中执行一个任务
//     pool.execute(move|| {
//         // 这里是你的任务代码
//         // let result = "task finished";
//         // do_func(&i);
//         // 将任务的结果发送到通道中
//         tx.send(do_func(&i)).unwrap();
//     });
// }

// // 所有任务都已经发送，我们可以放弃发送端的所有权
// drop(tx);
// // 从接收端接收数据，直到通道关闭（也就是所有任务都完成了）
// for _ in rx {
//     // println!("{}", result);
// }