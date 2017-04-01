{
  'targets': [
    {
      'target_name': 'addon',
      'sources': [
        'lib/types.h',
        'lib/libgo.h',
        'addon.cc'
      ],
      'include_dirs': [ '<!(node -e \'require("nan")\')' ],
      # libraries are relative to the 'build' directory
      'libraries': [ '../lib/libgo.a' ]
    }
  ]
}
