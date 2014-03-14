var crypt = require("./build/Release/crypt");

if (process.argv.length < 5)
    throw new Error("call me with <password> <salt> <password-confirmation>");
var password = process.argv[2],
    salt     = process.argv[3],
    confirm  = process.argv[4];

hash   = crypt(password, salt);
verify = crypt(confirm, hash);
console.log("hash:   " + hash);
console.log("verify: " + verify);
console.log("matching? " + (hash === verify ? 'yes' : 'no'));
