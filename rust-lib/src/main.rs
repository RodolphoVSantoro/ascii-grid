use std::{ffi::c_char, os::raw::c_uchar};

use rust_lib::{load_image, drop_image};

fn main() {
    let path = std::ffi::CString::new("./2k.png").unwrap();
    let path = path.as_ptr();

    // Check for memory leaks
    for _ in 0..100 {
        let image = load_image(path);
        let pixels = image.pixels;
        println!("Hello, world!{:?}", unsafe { (**pixels).red });
        drop_image(image)
    }

    // println!("Hello, world!{:?}", unsafe {(**image).red});
}
