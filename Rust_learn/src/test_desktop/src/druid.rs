use druid::widget::{Align,Flex,SizedBox, Container,Label, TextBox};
use druid::{AppLauncher,Color, Size,LocalizedString, PlatformError, Widget, WidgetExt, WindowDesc, Data, Lens};

#[derive(Clone, Default, Data, Lens)]
struct AppData {
    input1: String,
    input2: String,
    output: String,
}

fn build_ui() -> impl Widget<AppData> {
    // 创建两个输入框
    let input_box1 = SizedBox::new(
        TextBox::new().lens(AppData::input1)
    )
    .width(100.0)
    .height(30.0);
    let input_box2 = TextBox::new().lens(AppData::input2);


    // 创建一个输出框
    let output_box = SizedBox::new(
        Container::new(
            Label::new(|data: &AppData, _env: &_| format!("Output: {}", data.input1))
        )
        .background(Color::rgb8(40, 240, 240))
    )
    .width(400.0)
    .height(250.0);

    // 使用Flex布局将输入框和输出框放在一起
    // Flex::column()
    // .with_child(
    //     Flex::row()
    //     .must_fill_main_axis(true)
    //     .with_flex_child(
    //         Align::centered(Label::new("IP地址:").with_text_color(Color::rgb8(0, 0, 0))), 0.01
    //     )
    //     .with_flex_child(
    //         Align::centered(input_box1), 0.15
    //     )
    //     .with_flex_spacer(0.01)
    //     .with_flex_child(
    //         Align::centered(Label::new("端口号:").with_text_color(Color::rgb8(0, 0, 0))), 0.01
    //     )
    //     .with_flex_child(
    //         Align::centered(input_box2), 0.15
    //     )
    // )
    // .with_child(
    //     Align::centered(output_box)
    // )
    // .background(Color::WHITE)



    let ip_address_box = Flex::row()
    .with_child(
        Align::centered(Label::new("IP地址:").with_text_color(Color::rgb8(0, 0, 0)))
    )
    .with_child(
        Align::centered(input_box1)
    );

    let port_number_box = Flex::row()
        .with_child(
            Align::centered(Label::new("端口号:").with_text_color(Color::rgb8(0, 0, 0)))
        )
        .with_child(
            Align::centered(input_box2)
        );

    Flex::column()
        .with_child(
            Align::centered(   Flex::row()
            .must_fill_main_axis(true)
            .with_flex_child(ip_address_box,0.004)       
            .with_flex_spacer(0.0007)
            .with_flex_child(port_number_box,0.004))
         
        )
        .with_child(
            Align::centered(output_box)
        )
        .background(Color::WHITE)
}

fn main() -> Result<(), PlatformError> {
    // 创建窗口描述
    let main_window = WindowDesc::new(build_ui)
        .title(LocalizedString::new("Window Title"))
        .window_size(Size::new(600.0, 400.0));  //(宽度，高度)

    // 创建应用程序启动器
    AppLauncher::with_window(main_window)
        .launch(AppData::default())?;

    Ok(())
}