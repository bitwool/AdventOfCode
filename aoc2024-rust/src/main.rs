mod day01;
mod day02;
mod day03;
mod day04;
mod fileutil;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() > 1 {
        match args[1].as_str() {
            "01" => day01::process(),
            "02" => day02::process(),
            "03" => day03::process(),
            "04" => day04::process(),
            _ => println!("未知的日期参数"),
        }
    } else {
        println!("请提供日期参数，例如 '01'");
    }
}
