use std::fs::{self, File};
use std::io::{self, BufRead};
use std::path::Path;

pub fn read_lines(file_path: &str) -> Vec<String> {
    let path = Path::new(file_path);
    let file = match File::open(path) {
        Ok(file) => file,
        Err(error) => {
            eprintln!("无法打开文件 {}: {}", file_path, error);
            return Vec::new();
        }
    };

    let reader = io::BufReader::new(file);
    let mut lines = Vec::new();

    for line in reader.lines() {
        match line {
            Ok(line_content) => lines.push(line_content),
            Err(error) => {
                eprintln!("读取行时出错: {}", error);
                // 继续处理其他行
            }
        }
    }

    lines
}
pub fn read_text(file_path: &str) -> String {
    match fs::read_to_string(file_path) {
        Ok(content) => content,
        Err(error) => {
            eprintln!("无法读取文件 {}: {}", file_path, error);
            String::new() // 返回空字符串以表示出错
        }
    }
}
