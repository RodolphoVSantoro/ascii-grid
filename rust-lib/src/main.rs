use rust_lib::{drop_image, load_image};

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
}
