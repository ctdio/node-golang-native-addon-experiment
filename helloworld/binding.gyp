{
  'targets': [
    {
      'target_name': 'go-addon',
      'sources': [
        'lib/libgo.h',
        'addon.cc'
      ],
      # libraries are relative to the 'build' directory
      'libraries': [ '../lib/libgo.a' ]
    }
  ]
}
