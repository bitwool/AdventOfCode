// 导入我们的文件工具模块
use crate::fileutil;

pub fn process() {
    let lines = fileutil::read_lines("./input/day01.txt");
    part1(&lines);
    part2(&lines);
}

fn part1(lines: &Vec<String>) {
    let (mut left_numbers, mut right_numbers) = split_to_array(lines);

    left_numbers.sort();
    right_numbers.sort();
    println!("{:?}", left_numbers.len());

    let mut sum = 0;
    for i in 0..left_numbers.len() {
        sum += (left_numbers[i] - right_numbers[i]).abs();
    }
    println!("Day 01 Part 1: {}", sum);
}

fn part2(lines: &Vec<String>) {
    let (left_numbers, right_numbers) = split_to_array(lines);
    //对right_numbier计数 保存为hashmap
    let mut right_count = std::collections::HashMap::new();
    for num in right_numbers {
        let count = right_count.entry(num).or_insert(0);
        *count += 1;
    }
    let mut sum = 0;
    for num in left_numbers {
        let count = right_count.entry(num).or_insert(0);
        sum += num * *count;
    }

    println!("Day 01 Part 2: {}", sum);
}

fn split_to_array(lines: &Vec<String>) -> (Vec<i32>, Vec<i32>) {
    let mut left_numbers = Vec::with_capacity(lines.len());
    let mut right_numbers = Vec::with_capacity(lines.len());

    for line in lines {
        if let Some((left, right)) = line.split_once(' ') {
            if let (Ok(left_num), Ok(right_num)) =
                (left.trim().parse::<i32>(), right.trim().parse::<i32>())
            {
                left_numbers.push(left_num);
                right_numbers.push(right_num);
            }
        }
    }
    (left_numbers, right_numbers)
}
