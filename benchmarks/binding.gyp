{
  'targets': [
    {
      'target_name': 'bench-addon',
      'sources': [
        'lib/libgo.h',
        'addon.cc'
      ],
      'libraries': [ '../lib/libgo.a' ]
    }
  ]
}
