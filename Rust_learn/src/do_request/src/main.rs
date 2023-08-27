// mod request_post_body;
// use request_post_body::post_body;
// mod request_header;
// use request_header::mainss;
// mod request_post_form_file;
// use request_post_form_file::post_form_file;
mod request_post_form;
use request_post_form::post_form;

fn main() {
    // mainss();
    // let _ = mainss();
    // let _ = post_form_file();
    // let _ = post_body();
    let _ = post_form();


}



// post   发送数据类型
// application/x-www-form-urlencoded
// multipart/form-data
// application/json
// text/xml
// text/plain