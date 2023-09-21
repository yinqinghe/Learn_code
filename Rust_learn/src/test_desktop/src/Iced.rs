use iced::{Align, Column, Container, Element, Length, Row, Sandbox, Settings, Text, TextInput};
use iced::text_input::{State as TextInputState};

#[derive(Default)]
pub struct AppData {
    input1_state: TextInputState,
    input1: String,
    input2_state: TextInputState,
    input2: String,
    output: String,
}

#[derive(Debug, Clone)]
pub enum Message {
    Input1Changed(String),
    Input2Changed(String),
}

impl Sandbox for AppData {
    type Message = Message;

    fn new() -> Self {
        Self::default()
    }

    fn title(&self) -> String {
        String::from("Window Title")
    }

    fn update(&mut self, message: Self::Message) {
        match message {
            Message::Input1Changed(value) => {
                self.input1 = value;
                self.output = self.input1.clone();
            }
            Message::Input2Changed(value) => {
                self.input2 = value;
            }
        }
    }

    fn view(&mut self) -> Element<Message> {
        let input_box1 = TextInput::new(
            &mut self.input1_state,
            "IP地址",
            &self.input1,
            Message::Input1Changed,
        )
        .width(Length::Units(100));

        let input_box2 = TextInput::new(
            &mut self.input2_state,
            "端口号",
            &self.input2,
            Message::Input2Changed,
        )
        .width(Length::Units(100));

        let output_box = Text::new(format!("Output: {}", self.output))
            .width(Length::Fill)
            .size(50);

        let content = Column::new()
            .align_items(Align::Center)
            .push(
                Row::new()
                    .push(input_box1)
                    .push(input_box2)
            )
            .push(output_box);

        Container::new(content)
            .width(Length::Fill)
            .height(Length::Fill)
            .into()
    }
}

fn main() -> iced::Result {
    AppData::run(Settings::default())
}