module Day02

open System

let load_input =
    let lines = AocUtil.readLinesFromFile "./input/day02.txt"
    lines

let parseLine (line: string) = line.Split(' ') |> Array.map int

let isMonotonicIncreasing arr =
    arr |> Array.pairwise |> Array.forall (fun (a, b) -> b > a && b - a <= 3)

let isMonotonicDecreasing arr =
    arr |> Array.pairwise |> Array.forall (fun (a, b) -> a > b && a - b <= 3)

let check1 arr =
    isMonotonicDecreasing arr || isMonotonicIncreasing arr

let part1 () =
    let numbers = load_input |> Array.map parseLine

    let countValidArrays numbers =
        numbers |> Array.filter check1 |> Array.length

    let validArrayCount = countValidArrays numbers
    printfn "Day02-part1: %d" validArrayCount

let check2 arr =
    if check1 arr then
        true
    else
        let len = Array.length arr

        [| 0 .. len - 1 |]
        |> Array.map (fun i -> Array.concat [| arr.[0 .. i - 1]; arr.[i + 1 ..] |])
        |> Array.exists check1


let part2 () =
    let numbers = load_input |> Array.map parseLine

    let countValidArrays numbers =
        numbers |> Array.filter check2 |> Array.length

    let validArrayCount = countValidArrays numbers
    printfn "Day02-part2: %d" validArrayCount

let solve () =
    part1 ()
    part2 ()
