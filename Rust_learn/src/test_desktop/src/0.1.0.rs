use druid::widget::{Align,Flex,SizedBox,Label, TextBox,Button,Controller,ControllerHost,Scroll,List};
use druid::{AppLauncher,Color, Size,LocalizedString, PlatformError, Widget, WidgetExt, WindowDesc, Data, Lens};
use druid::{MenuDesc, MenuItem,Selector,EventCtx,Event,Env};
// use druid::FileDialogOptions;
// use druid::commands::SHOW_OPEN_PANEL;
use std::io::{Read, Write};
use std::net::TcpStream;
use std::sync::{Arc, Mutex,Condvar};
use lazy_static::lazy_static;
use std::sync::mpsc;
lazy_static! {
    static ref APP_DATA: Arc<Mutex<AppData>> = Arc::new(Mutex::new(AppData::default()));
    static ref CONDVAR: Condvar = Condvar::new();
}

const UPDATE_OUTPUT: Selector<String> = Selector::new("app.update-output");
// const UPDATE_OUTPUT: Selector<Arc<Vec<String>>> = Selector::new("app.update-output");

#[derive(Clone, Default, Data, Lens)]
struct AppData {
    server_ip: String,
    server_port: String,
    proxy_ip: String,
    proxy_port: String,
    command:String,
    // output: String,
    stream: Option<Arc<Mutex<TcpStream>>>,
    output: Arc<Vec<String>>,
}
const NEW_PROXY_WINDOW: Selector<()> = Selector::new("app.new-proxy-window");
struct ProxyWindowController;

fn client(ip: &str, port: &str) -> Arc<Mutex<TcpStream>> {
    let address = ip.to_owned() + ":" + port;
    println!("{}", address);
    let stream = TcpStream::connect(address).unwrap();
    println!("连接已成功建立！");
    Arc::new(Mutex::new(stream))
}
fn execute_command(input_command: &mut String,stream: Arc<Mutex<TcpStream>>, callback: impl FnOnce(String) + Send + 'static){
    println!("执行命令1");
    {
        let mut stream = stream.lock().unwrap();
        let msg = input_command.trim().as_bytes();
        stream.write(msg).unwrap();
    }
    println!("执行命令2");
    let mut buffer = Vec::new();
    let mut temp_buffer = [0; 1024];
    println!("执行命令3");
    loop {
        println!("执行命令4");
        let bytes_read = {
            let mut stream = stream.lock().unwrap();
            stream.read(&mut temp_buffer).unwrap()
        };
        buffer.extend_from_slice(&temp_buffer[..bytes_read]);
        if bytes_read < temp_buffer.len() {break;}
    }
    // Print the received message from the server
    let received_message = String::from_utf8_lossy(&buffer[..]).to_string();
    println!("{}", received_message);

    callback(received_message.clone());
}
struct OutputController;
impl<W: Widget<AppData>> Controller<AppData, W> for OutputController {
    fn event(&mut self, child: &mut W, ctx: &mut EventCtx, event: &Event, data: &mut AppData, env: &Env) {
        if let Event::Command(cmd) = event {
            if let Some(message) = cmd.get(UPDATE_OUTPUT) {
                // data.output = message.clone();
                let output = Arc::make_mut(&mut data.output);
                output.push(message.clone());
                ctx.request_update();
            }
        }
        child.event(ctx, event, data, env);
    }
}


fn build_proxy_window() -> impl Widget<AppData> {
    let ip_address_box = TextBox::new().lens(AppData::proxy_ip);
    let port_number_box = TextBox::new().lens(AppData::proxy_port);
    let ok_button = Button::new("确定").on_click(|ctx, data: &mut AppData, _env| {
        let output = Arc::make_mut(&mut data.output);
        output.push(data.proxy_ip.clone());
        // data.output = data.proxy_ip.clone();
        ctx.window().close();
    });
    let ip_address_box = Flex::row()
    .with_child(Align::centered(Label::new("代理IP:").with_text_color(Color::rgb8(0, 0, 0))))
    .with_child(Align::centered(ip_address_box));

    let port_number_box = Flex::row()
        .with_child(Align::centered(Label::new("代理端口:").with_text_color(Color::rgb8(0, 0, 0))))
        .with_child(Align::centered(port_number_box));
    Flex::column()
        .with_child(ip_address_box)
        .with_child(port_number_box)
        .with_child(ok_button)
        .background(Color::WHITE)
}

impl<W: Widget<AppData>> Controller<AppData, W> for ProxyWindowController {
    fn event(&mut self, child: &mut W, ctx: &mut EventCtx, event: &Event, data: &mut AppData, env: &Env) {
        match event {
            Event::Command(cmd) if cmd.is(NEW_PROXY_WINDOW) => {
                let new_window = WindowDesc::new(|| build_proxy_window())
                    .title(LocalizedString::new("代理设置"))
                    .window_size(Size::new(200.0, 100.0));
                ctx.new_window(new_window);
            }
            _ => child.event(ctx, event, data, env),
        }
    }
}
fn build_ui() -> impl Widget<AppData> {

    // 创建三个输入框
    let input_ip = SizedBox::new(TextBox::new().lens(AppData::server_ip))
    .width(130.0);
    // .height(30.0);
    let input_port = TextBox::new().lens(AppData::server_port);
    let input_command = SizedBox::new(TextBox::new().lens(AppData::command)).width(180.0);


    // // 创建一个输出框
    // let output_box = SizedBox::new(
    //     Container::new(Label::new(|data: &AppData, _env: &_| format!("Output: {}  {}", data.server_ip,data.output)).with_text_color(Color::rgb8(0, 0, 0)))
    //     .background(Color::rgb8(40, 240, 240)))
    // .width(550.0)
    // .height(300.0)
    // .controller(OutputController);


    // 创建一个输出列表
    let output_list = Scroll::new(List::new(|| {
        Label::new(|item: &String, _env: &Env| format!("Output:  {}", item))
            .with_text_color(Color::rgb8(255, 255, 255))  
            .padding(10.0)
            .expand_width()
    })).lens(AppData::output)
    .controller(OutputController);
    
    let output_list = SizedBox::new(output_list)
        .width(500.0)  // 设置宽度
        .height(300.0)  // 设置高度
        .background(Color::rgb8(0, 0, 0));  // 设置背景颜色

    //创建一个连接按钮
    let button_proxy = Button::new("连接")
    .on_click(|_ctx, data: &mut AppData,_| {
        // println!("Button clicked!");
        // let options = FileDialogOptions::new().select_directories();
        // ctx.submit_command(SHOW_OPEN_PANEL.with(options));
        let server_ip = data.server_ip.clone();
        let server_port = data.server_port.clone();
        // let command = data.command.clone();
        std::thread::spawn(move || {
            let stream = client(&server_ip, &server_port);
            let mut data = APP_DATA.lock().unwrap();
            data.stream = Some(stream);
            CONDVAR.notify_all();  // 通知所有等待的线程
        });
        let output = Arc::make_mut(&mut data.output);
        output.push("连接已成功建立！".to_string());
        // data.output="连接已成功建立！".to_string();
    });
    let button_exec = Button::new("确定")
    .on_click(|ctx, data: &mut AppData,_| {
        let command = data.command.clone();
        let mut data = APP_DATA.lock().unwrap();
        while data.stream.is_none() {
            data = CONDVAR.wait(data).unwrap();  // 等待直到stream被创建
        }
        // data.output="stream被创建".to_string();
        let output = Arc::make_mut(&mut data.output);
        output.push("stream被创建".to_string());
        if let Some(stream) = data.stream.as_ref() {
            let stream = Arc::clone(stream);
            // 创建一个通道
            let (tx, rx) = mpsc::channel();
            let tx1 = Arc::new(Mutex::new(tx.clone()));
            std::thread::spawn(move || {
                execute_command(&mut command.clone(), stream,move |message| {
                    // 在新线程中发送消息
                    let tx1 = Arc::clone(&tx1);
                    let tx1 = tx1.lock().unwrap();
                    tx1.send(message).unwrap();
                });
            });
            // 在主线程中接收消息
            let received = rx.recv().unwrap();
            // 将接收到的消息赋给data.output
            // let output = Arc::make_mut(&mut data.output);
            // output.push(received);
            println!("stream   {:?}", received);
            // 发送UPDATE_OUTPUT命令
            ctx.submit_command(UPDATE_OUTPUT.with(received));

        } else {
            // data.output="未建立连接！".to_string();
            let output = Arc::make_mut(&mut data.output);
            output.push("未建立连接！".to_string());
        }
    });


    // 使用Flex布局将输入框和输出框放在一起
    let ip_address_box = Flex::row()
        .with_child(Align::centered(Label::new("IP地址:").with_text_color(Color::rgb8(0, 0, 0))))
        .with_child(Align::centered(input_ip));

    let port_number_box = Flex::row()
        .with_child( Align::centered(Label::new("端口号:").with_text_color(Color::rgb8(0, 0, 0))))
        .with_child(Align::centered(input_port));
    //上面的输入功能
    let input_boxes = Flex::row()
        .with_child(Align::centered(ip_address_box))
        .with_spacer(1.0)
        .with_child(Align::centered(port_number_box))
        .with_child(button_proxy);

    let input_commands = Flex::row()
        .with_child(Align::centered(Label::new("命令执行").with_text_color(Color::rgb8(0, 0, 0))))
        .with_child(Align::centered(input_command))
        .with_child(button_exec);
    let ui=Flex::column()
        .with_child(input_boxes)
        .with_child(input_commands)
        .with_flex_child(Align::centered(output_list),0.5)
        .background(Color::WHITE);
    // 创建Controller
    let controller = ControllerHost::new(ui, ProxyWindowController);

    controller
}

fn make_menu<T: Data>() -> MenuDesc<T> {
    MenuDesc::empty().append(
        MenuItem::new(
            LocalizedString::new("代理"),
            NEW_PROXY_WINDOW,))
}
fn main() -> Result<(), PlatformError> {
    // 创建窗口描述
    let main_window = WindowDesc::new(build_ui)
        .title(LocalizedString::new("Window Title"))
        .window_size(Size::new(600.0, 400.0))  //(宽度，高度)
        .menu(make_menu::<AppData>());  // 添加菜单

    // 创建应用程序启动器
    AppLauncher::with_window(main_window)
        .launch(AppData::default())?;

    Ok(())
}