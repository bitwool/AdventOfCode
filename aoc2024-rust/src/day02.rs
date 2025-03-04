use crate::fileutil;

pub fn process() {
    let lines = fileutil::read_lines("./input/day02.txt");
    part1(&lines);
    part2(&lines);
}

fn part1(lines: &[String]) {
    let count = lines.iter().filter(|line| is_safe_line1(line)).count();

    println!("Day 02 Part 1: {}", count);
}

fn is_safe_line1(line: &str) -> bool {
    let numbers: Vec<i32> = line
        .split_whitespace()
        .filter_map(|s| s.parse().ok())
        .collect();

    is_valid_sequence(&numbers)
}

fn part2(lines: &[String]) {
    let count = lines.iter().filter(|line| is_safe_line2(line)).count();

    println!("Day 02 Part 1: {}", count);
}

fn is_safe_line2(line: &str) -> bool {
    let numbers: Vec<i32> = line
        .split_whitespace()
        .filter_map(|s| s.parse().ok())
        .collect();

    if is_valid_sequence(&numbers) {
        return true;
    }

    // 检查删除任意一个元素后是否符合条件
    for skip_index in 0..numbers.len() {
        let filtered_numbers: Vec<i32> = numbers
            .iter()
            .enumerate()
            .filter_map(|(i, &num)| if i != skip_index { Some(num) } else { None })
            .collect();

        if is_valid_sequence(&filtered_numbers) {
            return true;
        }
    }

    false
}

fn is_valid_sequence(numbers: &[i32]) -> bool {
    check_sequence(numbers, |a, b| a < b) || check_sequence(numbers, |a, b| a > b)
}

fn check_sequence<F>(numbers: &[i32], compare: F) -> bool
where
    F: Fn(i32, i32) -> bool,
{
    numbers.windows(2).all(|pair| {
        let diff = (pair[1] - pair[0]).abs();
        compare(pair[0], pair[1]) && diff > 0 && diff <= 3
    })
}
