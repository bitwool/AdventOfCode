let read_all_lines file_name =
  let in_channel = open_in file_name in
  
  let rec read_recursive lines =
    try
      let line = input_line in_channel in
      read_recursive (line :: lines)
    with
      End_of_file -> lines in
      
  let lines = read_recursive [] in
  let _ = close_in_noerr in_channel in
  List.rev lines