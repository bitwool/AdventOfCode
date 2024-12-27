module Day01

open System

let load_input =
    let lines = AocUtil.readLinesFromFile "./input/day01.txt"
    lines

let parseLine (line: string) =
    line.Split(' ')
    |> Array.filter (not << String.IsNullOrWhiteSpace)
    |> fun parts -> (int parts.[0], int parts.[1])

let calculateDifference (left: int, right) = abs (left - right)


let part1 () =
    let numbers = load_input |> Array.map parseLine
    let leftNumbers = numbers |> Array.map fst |> Array.sort
    let rightNumbers = numbers |> Array.map snd |> Array.sort

    let result =
        Array.zip leftNumbers rightNumbers |> Array.map calculateDifference |> Array.sum

    printfn "Day01-part1: %d" result

let part2 () =
    let numbers = load_input |> Array.map parseLine
    let leftNumbers = numbers |> Array.map fst
    let rightNumbers = numbers |> Array.map snd

    let result =
        leftNumbers
        |> Array.sumBy (fun x -> x * (rightNumbers |> Array.filter ((=) x) |> Array.length))

    printfn "Day01-part2: %d" result

let solve () =
    part1 ()
    part2 ()
