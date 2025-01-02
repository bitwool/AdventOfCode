module Day04

open System

let load_input = AocUtil.readTextFromFile "./input/day04.txt"

let textToGrid (text: string) =
    text.Split('\n', StringSplitOptions.RemoveEmptyEntries) |> Array.map Seq.toArray

let directions =
    [ (0, 1) // 右
      (1, 0) // 下
      (1, 1) // 右下
      (-1, 1) // 右上
      (0, -1) // 左
      (-1, 0) // 上
      (-1, -1) // 左上
      (1, -1) ] // 左下

let isValidPosition (grid: char[][]) (row: int) (col: int) =
    row >= 0 && row < grid.Length && col >= 0 && col < grid.[0].Length

let searchPattern (grid: char[][]) (startRow: int) (startCol: int) (dRow: int) (dCol: int) (pattern: string) =
    let mutable matches = true

    for i in 0 .. pattern.Length - 1 do
        let newRow = startRow + i * dRow
        let newCol = startCol + i * dCol

        if
            not (isValidPosition grid newRow newCol)
            || grid.[newRow].[newCol] <> pattern.[i]
        then
            matches <- false

    matches

let findPattern (grid: char[][]) (pattern: string) =
    let mutable count = 0

    for row in 0 .. grid.Length - 1 do
        for col in 0 .. grid.[0].Length - 1 do
            for (dRow, dCol) in directions do
                if searchPattern grid row col dRow dCol pattern then
                    count <- count + 1

    count

let part1 () =
    let text = load_input
    let grid = textToGrid text
    let count = findPattern grid "XMAS"
    printfn "Day04-part1: %d" count

let xdirections = [| [| (-1, -1); (1, 1) |]; [| (1, -1); (-1, 1) |] |]

let findXPattern (grid: char[][]) =
    let mutable count = 0

    for row in 0 .. grid.Length - 1 do
        for col in 0 .. grid.[0].Length - 1 do
            if grid.[row].[col] = 'A' then
                let mutable patterns = []
                let mutable allValid = true

                // 收集两个对角线方向的字符串
                for directionPair in xdirections do
                    let mutable str = ""
                    let mutable isValid = true

                    for (dRow, dCol) in directionPair do
                        let newRow = row + dRow
                        let newCol = col + dCol

                        if not (isValidPosition grid newRow newCol) then
                            isValid <- false
                        else
                            str <- str + (string grid.[newRow].[newCol])

                    if isValid && (str = "MS" || str = "SM") then
                        patterns <- str :: patterns
                    else
                        allValid <- false

                // 只有当收集到两个有效的模式时才计数
                if allValid && List.length patterns = 2 then
                    count <- count + 1

    count

let part2 () =
    let text = load_input
    let grid = textToGrid text
    let count = findXPattern grid
    printfn "Day04-part2: %d" count

let solve () =
    part1 ()
    part2 ()
