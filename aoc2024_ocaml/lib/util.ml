let read_all_lines file_name =
  let in_channel = open_in file_name in
  let rec read_recursive lines =
    try
      let line = input_line in_channel in
      read_recursive (line :: lines)
    with
    | End_of_file -> lines
  in
  let lines = read_recursive [] in
  let _ = close_in_noerr in_channel in
  List.rev lines
;;

(* 读取整个文件内容为字符串 *)
let read_file_as_string filename =
  let ic = open_in filename in
  try
    (* 获取文件长度 *)
    let len = in_channel_length ic in
    (* 创建缓冲区 *)
    let buf = Bytes.create len in
    (* 读取文件内容到缓冲区 *)
    really_input ic buf 0 len;
    (* 关闭文件 *)
    close_in ic;
    (* 转换为字符串 *)
    Bytes.to_string buf
  with
  | e ->
    (* 出错时确保关闭文件 *)
    close_in_noerr ic;
    raise e
;;
