module Day03


open System
open System.Text.RegularExpressions

let load_input = AocUtil.readTextFromFile "./input/day03.txt"


let mul_sum text =

    let matches = Regex.Matches(text, @"mul\((\d+),(\d+)\)")

    matches
    |> Seq.cast<Match>
    |> Seq.map (fun m -> (int m.Groups.[1].Value, int m.Groups.[2].Value))
    |> Seq.sumBy (fun (a, b) -> a * b)

let part1 () =
    let text = load_input

    printfn "Day03-part1: %d" (mul_sum text)

let splitString (input: string) =
    let pattern = @"(?=(don't\(\)|do\(\)))"
    Regex.Split(input, pattern) |> Array.filter (not << String.IsNullOrEmpty)

let part2 () =
    let text = load_input

    text
    |> splitString
    |> Array.filter (fun x -> not (x.StartsWith("don't")))
    |> Array.map mul_sum
    |> Array.sum
    |> printfn "Day03-part2: %d"

let solve () =
    part1 ()
    part2 ()
