const addon = require('./build/Release/addon')

addon.doSomethingAsync(function (res) {
  console.log('callback result:', res)
})
