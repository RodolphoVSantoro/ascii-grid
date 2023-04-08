use image::GenericImageView;
use std::{
    ffi::{c_uchar, c_uint},
    mem,
    os::raw::c_char,
};
#[repr(C)]
pub struct RGB {
    pub red: c_uchar,
    pub green: c_uchar,
    pub blue: c_uchar,
}

#[repr(C)]
pub struct Image {
    pub pixels: *mut *mut RGB,
    pub width: c_uint,
    pub height: c_uint,
}

#[no_mangle]
pub extern "C" fn load_image(path: *const c_char) -> Image {
    let path = unsafe { std::ffi::CStr::from_ptr(path) };
    let path = path.to_str().expect("Invalid path");

    let image = image::open(path).unwrap();

    let dimensions = image.dimensions();

    let mut pixels = Vec::new();

    for y in 0..dimensions.1 {
        let mut row = Vec::new();
        for x in 0..dimensions.0 {
            let pixel = image.get_pixel(x, y);
            let rgb = RGB {
                red: pixel[0],
                green: pixel[1],
                blue: pixel[2],
            };
            row.push(rgb);
        }
        pixels.push(row);
    }

    for row in pixels.iter_mut() {
        row.shrink_to_fit();
    }
    pixels.shrink_to_fit();

    let mut pixels = mem::ManuallyDrop::new(
        pixels
            .into_iter()
            .map(|row| {
                let mut row = mem::ManuallyDrop::new(row.into_boxed_slice());
                let ptr = row.as_mut_ptr();
                ptr
            })
            .collect::<Vec<_>>(),
    );

    let ptr = pixels.as_mut_ptr();

    Image {
        pixels: ptr,
        width: dimensions.0,
        height: dimensions.1,
    }
}

#[no_mangle]
pub extern "C" fn drop_image(image: Image) {
    let pixels: *mut *mut RGB = image.pixels;
    let height = image.height as usize;
    let width = image.width as usize;

    let rows = unsafe { Vec::from_raw_parts(pixels, height, height) };

    for row in rows {
        unsafe {
            let vec = Vec::from_raw_parts(row, width, width);

            std::mem::drop(vec);
        }
    }
}

// #[cfg(test)]
// mod tests {
//     use super::*;

//     #[test]
//     fn it_works() {
//         let result = add(2, 2);
//         assert_eq!(result, 4);
//     }
// }
