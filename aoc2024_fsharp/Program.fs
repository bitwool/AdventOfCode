module Program

open System

let args = Environment.GetCommandLineArgs()

if args.Length > 1 then
    let day = args.[1]

    match day with
    | "day01" -> Day01.solve ()
    | "day02" -> Day02.solve ()
    | "day03" -> Day03.solve ()
    | "day04" -> Day04.solve ()
    | _ -> printfn "Day not implemented."
else
    printfn "No command line arguments provided."
