use crate::fileutil;

pub fn process() {
    let input = fileutil::read_text("./input/day03.txt");
    part1(&input);
    part2(&input);
}

fn part1(input: &str) {
    let re = regex::Regex::new(r"mul\((\d{1,3}),(\d{1,3})\)").unwrap();

    let mut sum = 0;
    for cap in re.captures_iter(input) {
        let x: u64 = cap[1].parse().unwrap();
        let y: u64 = cap[2].parse().unwrap();
        sum += x * y;
    }

    println!("Day 03 Part 1: {}", sum);
}

fn part2(input: &str) {
    let mul_re = regex::Regex::new(r"mul\((\d{1,3}),(\d{1,3})\)").unwrap();
    let do_re = regex::Regex::new(r"do\(\)").unwrap();
    let dont_re = regex::Regex::new(r"don't\(\)").unwrap();

    // 收集所有指令及其位置
    let mut instructions = Vec::new();

    // 收集所有乘法指令
    for cap in mul_re.captures_iter(input) {
        let mat = cap.get(0).unwrap();
        let x: u64 = cap[1].parse().unwrap();
        let y: u64 = cap[2].parse().unwrap();
        instructions.push((mat.start(), "mul", x * y));
    }

    // 收集所有 do 指令
    for mat in do_re.find_iter(input) {
        instructions.push((mat.start(), "do", 0));
    }

    // 收集所有 don't 指令
    for mat in dont_re.find_iter(input) {
        instructions.push((mat.start(), "dont", 0));
    }

    // 按位置排序指令
    instructions.sort_by_key(|&(pos, _, _)| pos);

    // 计算结果
    let mut sum = 0;
    let mut enabled = true;

    for (_, instr_type, value) in instructions {
        match instr_type {
            "do" => enabled = true,
            "dont" => enabled = false,
            "mul" => {
                if enabled {
                    sum += value;
                }
            }
            _ => (),
        }
    }

    println!("Day 03 Part 2: {}", sum);
}
