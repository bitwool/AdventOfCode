module AocUtil

open System.IO

let readLinesFromFile path =
    if File.Exists(path) then File.ReadAllLines(path) else [||] // Return an empty array if the file does not exist
