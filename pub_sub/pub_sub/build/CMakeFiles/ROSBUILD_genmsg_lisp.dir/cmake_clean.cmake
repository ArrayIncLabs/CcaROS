FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/pub_sub/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/String.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_String.lisp"
  "../msg_gen/lisp/state.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_state.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
