open Re

let cal_mul str =
  let s = String.sub str 4 (String.length str - 5) in
  s |> String.split_on_char ',' |> List.map int_of_string |> List.fold_left ( * ) 1
;;

let find_all_matches pattern text =
  let re = Perl.compile_pat pattern in
  Re.all re text |> List.map (fun group -> Re.Group.get group 0)
;;

let part1 () =
  let text = Util.read_file_as_string "./input/day03.txt" in
  text
  |> find_all_matches "mul\\(\\d{1,3},\\d{1,3}\\)"
  |> List.map cal_mul
  |> List.fold_left ( + ) 0
  |> Printf.printf "Part1 %d\n"
;;

let preprocess text =
  let re = Pcre.regexp "(do\\(\\))|(don't\\(\\))" in
  let parts = Re.split_full re text in
  let rec process_parts acc current = function
    | [] -> if current <> "" then List.rev (current :: acc) else List.rev acc
    | `Text t :: rest -> process_parts acc (current ^ t) rest
    | `Delim d :: rest ->
      let delimiter = Group.get d 0 in
      let new_acc = if current = "" then acc else current :: acc in
      process_parts new_acc delimiter rest
  in
  process_parts [] "" parts
;;

let part2 () =
  let text = Util.read_file_as_string "./input/day03.txt" in
  text
  |> preprocess
  |> List.filter (fun x -> not (String.starts_with ~prefix:"don't()" x))
  |> String.concat ""
  |> find_all_matches "mul\\(\\d{1,3},\\d{1,3}\\)"
  |> List.map cal_mul
  |> List.fold_left ( + ) 0
  |> Printf.printf "Part2 %d\n"
;;

let main () =
  part1 ();
  part2 ()
;;
