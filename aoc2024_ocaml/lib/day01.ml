let line_to_tuple line =
  match line |> String.split_on_char ' ' |> List.filter (fun s -> s <> "") with
  | [ x; y ] -> int_of_string x, int_of_string y
  | _ -> failwith "Invalid input: expected exactly two non-empty strings"
;;

let input () =
  let lines = Util.read_all_lines "./input/day01.txt" in
  lines |> List.map line_to_tuple |> List.split
;;

let part1 () =
  let data = input () in
  data
  |> fun (l1, l2) ->
  (List.sort compare l1, List.sort compare l2)
  |> fun (l1, l2) ->
  let diffs = List.map2 (fun x y -> abs (x - y)) l1 l2 in
  List.fold_left ( + ) 0 diffs |> Printf.printf "part1 result: %d\n"
;;

let count l e = l |> List.find_all (fun x -> x = e) |> List.length

let part2 () =
  let left, right = input () in
  let uniq_left = List.sort_uniq compare left in
  uniq_left
  |> List.map (fun x -> x * count right x)
  |> List.fold_left ( + ) 0
  |> Printf.printf "part2 result: %d\n"
;;

let main () =
  part1 ();
  part2 ()
;;
