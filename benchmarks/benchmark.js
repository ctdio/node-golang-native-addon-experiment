const { Suite } = require('benchmark')
const {
  cppAdd,
  cppIncrement,
  goAdd,
  goIncrement
} = require('./build/Release/bench-addon')

function jsAdd (a, b) {
  return a + b;
}

function jsIncrement () {
  let startDate = Date.now();
  let v = 0

  for (let i = 0; i < 2147483600; i++) {
    v = i
  }

  console.log(`js: Time in ms to complete loop ${Date.now() - startDate} ms`);
  return v
}


const valA = 123456
const valB = 654321

function logCycle (event) {
  console.log(String(event.target));
}

function onComplete () {
  console.log('Fastest is ' + this.filter('fastest').map('name'))
}

const additionSuite = new Suite()
  .add('js add', () => {
    jsAdd(valA, valB)
  })
  .add('cpp add', () => {
    cppAdd(valA, valB)
  })
  .add('go add', () => {
    goAdd(valA, valB)
  })
  .on('cycle', logCycle)
  .on('complete', onComplete)
  .run()

const incrementSuite = new Suite()
  .add('js increment', () => {
    jsIncrement(valA, valB)
  })
  .add('cpp increment', () => {
    cppIncrement(valA, valB)
  })
  .add('go increment', () => {
    goIncrement(valA, valB)
  })
  .on('cycle', logCycle)
  .on('complete', onComplete)
  .run()
