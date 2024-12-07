open Aoc2024_ocaml

let () =
  let args = Sys.argv in
  if Array.length args <> 2
  then Printf.printf "Usage: %s day\n" args.(0)
  else (
    match args.(1) with
    | "01" -> Day01.main ()
    | "02" -> Day02.main ()
    | _ -> Printf.printf "Invalid argument: %s. Use 01 or 02.\n" args.(1))
;;
