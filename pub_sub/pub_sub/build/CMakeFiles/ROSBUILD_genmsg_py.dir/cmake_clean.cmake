FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/pub_sub/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/pub_sub/msg/__init__.py"
  "../src/pub_sub/msg/_String.py"
  "../src/pub_sub/msg/_state.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
