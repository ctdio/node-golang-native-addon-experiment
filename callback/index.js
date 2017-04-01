const addon = require('./build/Release/addon')


const testObject = {
  num: 1
}

addon.doSomethingAsync(testObject, function (error, res) {
  console.log(`callback result:\n  error: ${error}\n  result: ${JSON.stringify(res)}`)
})
