const addon = require('./build/Release/addon')

const testObject = {
  num: 1.243
}

addon.doSomethingAsync(testObject).then((res) => {
  console.log(`promise result:\n  result: ${JSON.stringify(res)}`)
})
