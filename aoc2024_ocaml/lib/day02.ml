let line_to_list line = line |> String.split_on_char ' ' |> List.map int_of_string

let diff_check x y =
  let diff = x - y in
  diff >= 1 && diff <= 3
;;

let rec inc lst =
  match lst with
  | x :: y :: rest -> y > x && diff_check y x && inc (y :: rest)
  | _ -> true
;;

let rec desc lst =
  match lst with
  | x :: y :: rest -> y < x && diff_check x y && desc (y :: rest)
  | _ -> true
;;

let check1 lst = inc lst || desc lst

let part1 () =
  let lines = Util.read_all_lines "./input/day02.txt" in
  lines
  |> List.map line_to_list
  |> List.filter check1
  |> List.length
  |> Printf.printf "Part1 %d\n"
;;

let remove_at_index lst idx =
  List.mapi (fun i x -> i, x) lst |> List.filter (fun (i, _) -> i <> idx) |> List.map snd
;;

let generate_sublists lst =
  let len = List.length lst in
  List.init len (fun i -> remove_at_index lst i)
;;

let check2 lst =
  lst |> generate_sublists |> List.filter check1 |> fun x -> List.length x >= 1
;;

let part2 () =
  let lines = Util.read_all_lines "./input/day02.txt" in
  lines
  |> List.map line_to_list
  |> List.filter check2
  |> List.length
  |> Printf.printf "Part2 %d\n"
;;

let main () =
  part1 ();
  part2 ()
;;
