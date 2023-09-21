extern crate gtk;

use gtk::prelude::*;
use gtk::{Button, Label, Window, WindowType};

fn main() {
    // 初始化 GTK 库
    gtk::init().expect("Failed to initialize GTK.");

    // 创建主窗口
    let window = Window::new(WindowType::Toplevel);
    window.set_title("Hello, GTK!");
    window.set_default_size(250, 100);
    window.set_border_width(10);

    // 创建标签并设置文本
    let label = Label::new(Some("Hello, World!"));

    // 创建按钮并设置点击事件处理函数
    let button = Button::new_with_label("Click Me!");
    button.connect_clicked(move |_| {
        label.set_text("Button Clicked!");
    });

    // 创建垂直布局容器，并将标签和按钮添加进去
    let vbox = gtk::Box::new(gtk::Orientation::Vertical, 5);
    vbox.pack_start(&label, true, true, 0);
    vbox.pack_start(&button, false, false, 0);

    // 将布局容器添加到窗口中
    window.add(&vbox);

    // 设置窗口关闭事件处理函数
    window.connect_delete_event(|_, _| {
        gtk::main_quit();
        Inhibit(false)
    });

    // 显示窗口及其内容
    window.show_all();

    // 开始 GTK 主循环
    gtk::main();
}